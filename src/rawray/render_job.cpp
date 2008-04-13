/////////////////////////////////////////////////////////////////////////////
// render_job.cpp
//
/////////////////////////////////////////////////////////////////////////////
#include "render_job.h"
#include "time.h"

namespace rawray {

/////////////////////////////////////////////////////////////////////////////
bool RenderTask::Run(Scene& scene, const Camera& cam, Image& img, float* progress) {
    if( height_ == 0 || width_ == 0 )
        return false;

    const float delta = 100.0f / height_;
    for( uint32 row=y_; row<y_+height_; ++row ) {
        *progress = float(row) * delta;
        scene.Raytrace(cam, img, x_, row, width_, 1);
    }
    
    *progress = 100.0f;
    return true;
}


/////////////////////////////////////////////////////////////////////////////
RenderThread::RenderThread(Scene& scene, const Camera& cam, Image& img) :
        scene_(scene), cam_(cam), img_(img), currentTask_(NULL),
        threadID_(NULL), threadHandle_(NULL), abort_(false), isDone_(false), progress_(0.0f) {

    threadHandle_ = CreateThread(
                    0,                              // No security params
                    0,                              // Default stack size
                    RawRay_RenderThread_Handler,    // Start routine
                    this,                           // Start routine param
                    0,                              // No extra options (start immediately)
                    &threadID_ );                   // Save threadID_

    SetThreadPriority( threadHandle_, THREAD_PRIORITY_LOWEST );
}

RenderThread::~RenderThread() {
    Abort();
}

void RenderThread::Abort() {
    const uint32 sleepDuration = options::global::render_spinlock_sleep;

    // Block here waiting for controller thread to finish
    abort_ = true;
    while( !IsDone() )
        Sleep( sleepDuration );

    if( threadHandle_ != NULL )
        CloseHandle(threadHandle_);

    threadHandle_ = NULL;
    threadID_ = NULL;
}

DWORD RenderThread::ThreadRoutine() {
    const uint32 sleepDuration = options::global::render_thread_sleep;

    while( !abort_ ) {
        Sleep( sleepDuration );

        if( currentTask_ != NULL ) {
            progress_ = 0.0f;
            currentTask_->Run( scene_, cam_, img_, &progress_ );
            currentTask_ = NULL;
        }
    }

    isDone_ = true;
    return 0;
}

/////////////////////////////////////////////////////////////////////////////
RenderJob::~RenderJob() {
    Abort();
    Cleanup();
}

void RenderJob::Cleanup() {
    assert( threads_.empty() );
 
    // Clean up any unprocessed tasks
    while( !tasks_.empty() ) {
        RenderTask* task = tasks_.top();
        tasks_.pop();
        delete task;
    }

    // Clean up processed tasks
    while( !assignedTasks_.empty() ) {
        RenderTask* task = assignedTasks_.top();
        assignedTasks_.pop();
        delete task;
    }
}

float RenderJob::Progress() {
    if( IsDone() )
        return 100.0f;

    const uint32 num_assigned = assignedTasks_.size();
    const uint32 num_remaining = tasks_.size();
    const uint32 num_total = num_assigned + num_remaining;
    
    if( num_total == 0 || num_assigned <= numThreads_ )
        return 0.0f;

    // Progress of completed tasks
    const float delta = 1.0f / num_total;
    float progress = 100.0f * float(num_assigned - numThreads_) * delta;

    // Progress of running tasks
    //for( std::list<RenderThread*>::iterator thread = threads_.begin(); thread != threads_.end(); ++thread )
    //    progress += delta * (*thread)->Progress();

    return progress;
}

bool RenderJob::Run() {
    if( numThreads_ < 1 )
        return false;

    // Clean enviornment if a previous job was running
    Cleanup();

    // Create a list of tasks we need done
    const uint32 imgHeight = img_.GetHeight();
    const uint32 imgWidth = img_.GetWidth();

    const uint32 xChunk = options::global::render_x_block;
    const uint32 yChunk = options::global::render_y_block;
    
	// Create the rendering tasks in a temporary vector
	std::vector<RenderTask*> unshuffled_tasks;
    for( uint32 y=0; y<imgHeight; y+=yChunk )
        for( uint32 x=0; x<imgWidth; x+=xChunk )
            unshuffled_tasks.push_back( new RenderTask(x, y, xChunk, yChunk) );

	// Randomize the rendering tasks :)
	std::random_shuffle( unshuffled_tasks.begin(), unshuffled_tasks.end() );
	for( size_t i=0; i<unshuffled_tasks.size(); ++i )
		tasks_.push( unshuffled_tasks[i] );

    // Create the user specified number of threads
    for( uint32 thread=0; thread<numThreads_; ++thread )
        threads_.push_back( new RenderThread(scene_, cam_, img_) );

    // Create the master controller thread
    threadHandle_ = CreateThread(
                    0,                          // No security params
                    0,                          // Default stack size
                    RawRay_RenderJob_Handler,   // Start routine
                    this,                       // Start routine param
                    0,                          // No extra options, start immediately
                    &threadID_ );               // Save threadID_
    SetThreadPriority( threadHandle_, THREAD_PRIORITY_BELOW_NORMAL );

    return true;
}

void RenderJob::Abort() {
    const uint32 sleepDuration = options::global::render_spinlock_sleep;
    abort_ = true;

    // Block here waiting for controller thread to finish
    while( !IsDone() )
        Sleep( sleepDuration );

    if( threadHandle_ )
        CloseHandle( threadHandle_ );

    threadHandle_ = NULL;
    threadID_ = NULL;
}

DWORD RenderJob::ThreadRoutine() {
    std::list<RenderThread*>::iterator threadIter;
    std::list<RenderThread*>::iterator toDelete;
    const uint32 sleepDuration = options::global::render_handler_sleep;

    clock_t startTime = clock();
    while( !threads_.empty() ) {
        Sleep( sleepDuration );

        // Loop through all running threads 
        threadIter = threads_.begin();
        while( threadIter != threads_.end() ) {
            RenderThread* thread = *threadIter;

            // If this thread has no work, give it work
            if( thread->IsIdle() ) {
                if( tasks_.empty() || abort_ ) {
                    // Delete this thread if there is no work to give it
                    toDelete = threadIter++;
                    threads_.erase( toDelete );
                    delete thread;
                } else {
                    RenderTask* task = tasks_.top();
                    tasks_.pop();
                    assignedTasks_.push( task );

                    thread->SetCurrentTask( task );
                    threadIter++;
                }
            } else
                threadIter++;
        }
    }

    if( !abort_ ) {
        scene_.PostProcess(img_);
        clock_t endTime = clock();
        img_.WritePPM(endTime-startTime);

        std::cout << "Raytrace job of " << img_.GetWidth() << "x" << img_.GetHeight();
        std::cout << " done in " << float(endTime-startTime)/CLOCKS_PER_SEC << " seconds" << std::endl;
    }

    isDone_ = true;
    return 0;
}

} // namespace rawray



/////////////////////////////////////////////////////////////////////////////
DWORD WINAPI RawRay_RenderJob_Handler(LPVOID lpParameter)
{
	assert(lpParameter);
    rawray::RenderJob* job = static_cast<rawray::RenderJob*>(lpParameter);

    job->ThreadRoutine();
    return 0;
    
}

/////////////////////////////////////////////////////////////////////////////
DWORD WINAPI RawRay_RenderThread_Handler(LPVOID lpParameter)
{
	assert(lpParameter);
    rawray::RenderThread* thread = static_cast<rawray::RenderThread*>(lpParameter);

    thread->ThreadRoutine();
    return 0;
}
