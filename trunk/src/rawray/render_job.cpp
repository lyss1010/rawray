/////////////////////////////////////////////////////////////////////////////
// render_job.cpp
//
/////////////////////////////////////////////////////////////////////////////
#include "render_job.h"

namespace rawray {

/////////////////////////////////////////////////////////////////////////////
bool RenderTask::Run(Scene& scene, const Camera& cam, Image& img) {
    scene.Raytrace(cam, img, x_, y_, width_, height_);
    return true;
}


/////////////////////////////////////////////////////////////////////////////
RenderThread::RenderThread(Scene& scene, const Camera& cam, Image& img) :
        scene_(scene), cam_(cam), img_(img), currentTask_(NULL),
        threadID_(NULL), threadHandle_(NULL), abort_(false) {

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
    const uint32 sleepDuration = options::render_spin_lock_sleep;
    abort_ = true;

    // Block here waiting for controller thread to finish
    while( !IsDone() )
        Sleep( sleepDuration );

    if( threadHandle_ != NULL )
        CloseHandle(threadHandle_);
}

DWORD RenderThread::ThreadRoutine() {
    const uint32 sleepDuration = options::render_thread_sleep;

    while( !abort_ ) {
        Sleep( sleepDuration );

        if( currentTask_ != NULL ) {
            currentTask_->Run( scene_, cam_, img_ );
            currentTask_ = NULL;
        }
    }

    return 0;
}

/////////////////////////////////////////////////////////////////////////////
RenderJob::~RenderJob() {
    const uint32 sleepDuration = options::render_spin_lock_sleep;
    abort_ = true;

    // Block here waiting for controller thread to finish
    while( !IsDone() )
        Sleep( sleepDuration );

    Cleanup();
}

void RenderJob::Cleanup() {
    assert( threads_.empty() );
 
    // Clean up any unprocessed tasks
    while( !tasks_.empty() ) {
        RenderTask* task = tasks_.top();
        tasks_.pop();
        //delete task;
    }

    // Clean up processed tasks
    while( !assignedTasks_.empty() ) {
        RenderTask* task = assignedTasks_.top();
        assignedTasks_.pop();
        //delete task;
    }
}

bool RenderJob::IsDone() {
    return threads_.empty();
}

bool RenderJob::Run() {
    if( numThreads_ < 1 )
        return false;

    // Create a list of tasks we need done
    const uint32 imgHeight = img_.GetHeight();
    const uint32 imgWidth = img_.GetWidth();

    const uint32 xChunk = options::render_x_block;
    const uint32 yChunk = options::render_y_block;
    
    for( uint32 y=0; y<imgHeight; y+=yChunk ) {
        for( uint32 x=0; x<imgWidth; x+=xChunk ) {
            tasks_.push( new RenderTask(x, y, xChunk, yChunk) );
        }
    }

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

DWORD RenderJob::ThreadRoutine() {
    std::list<RenderThread*>::iterator threadIter;
    std::list<RenderThread*>::iterator toDelete;
    const uint32 sleepDuration = options::render_handler_sleep;

    while( !IsDone() ) {
        Sleep( sleepDuration );

        // Loop through all running threads 
        threadIter = threads_.begin();
        while( threadIter != threads_.end() ) {
            RenderThread* thread = *threadIter;

            // If this thread has no work, give it work
            if( thread->IsDone() ) {
                if( tasks_.empty() || abort_ ) {
                    // Delete this thread if there is no work to give it
                    toDelete = threadIter++;
                    threads_.erase( toDelete );
                    //delete thread;
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

    scene_.PostProcess(img_);
    img_.WritePPM( "autosave.ppm" );
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
