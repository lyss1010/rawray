/////////////////////////////////////////////////////////////////////////////
// render_job.cpp
//
/////////////////////////////////////////////////////////////////////////////
#include "render_job.h"
#include "time.h"
#include "stats.h"
#include "ray_caster.h"

namespace rawray {

/////////////////////////////////////////////////////////////////////////////
bool RenderTask::Run(Scene& scene, const Camera& cam, Image& img, const RayCaster& caster, float& progress) {
	
	// Make a local copy of the caster to use so it's all thread safe
	RayCaster myCaster = RayCaster(caster);
	myCaster.GenerateRays( cam, x_, x_+width_, y_, y_+height_, img.GetWidth(), img.GetHeight() );

	scene.Raytrace(img, myCaster, progress);
	progress = 100.0f;
    return true;
}


/////////////////////////////////////////////////////////////////////////////
RenderThread::RenderThread(Scene& scene, const Camera& cam, Image& img, RayCaster& caster) :
        scene_(scene), cam_(cam), img_(img), currentTask_(NULL), caster_(caster),
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
    const int sleepDuration = options::global::render_spinlock_sleep;

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
    const int sleepDuration = options::global::render_thread_sleep;

    while( !abort_ ) {
        Sleep( sleepDuration );

        if( currentTask_ != NULL ) {
            progress_ = 0.0f;
			currentTask_->Run( scene_, cam_, img_, caster_, progress_ );
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

    const size_t num_assigned = assignedTasks_.size();
    const size_t num_remaining = tasks_.size();
    const size_t num_total = num_assigned + num_remaining;
    
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

    const int imgHeight = img_.GetHeight();
    const int imgWidth = img_.GetWidth();

    // Create the tasks which we will distribute
    const int sizex = options::global::thread_job_size_x;
	const int sizey = options::global::thread_job_size_y;

    // Create tasks based on chunks of scanlines
	int x, y, width, height;
	for( x=0; x<imgWidth; x+=sizex ) {
		width = sizex;
		if( x+width > imgWidth )
			width = imgWidth - x;
		
		for( y=0; y<imgHeight; y+=sizey ) {
			height = sizey;
			if( y+height > imgHeight )
				height = imgHeight - y;

			tasks_.push( new RenderTask( x, y, width, height ) );
		}
	}
	
    // Create the user specified number of threads
    for( uint32 thread=0; thread<numThreads_; ++thread )
        threads_.push_back( new RenderThread(scene_, cam_, img_, caster_) );

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
    const int sleepDuration = options::global::render_spinlock_sleep;
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
    const int sleepDuration = options::global::render_handler_sleep;

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

        DisplayStats();
    }

    isDone_ = true;
    return 0;
}

void RenderJob::DisplayStats() {
		std::cout << "Number of BVH Leaves: " << rawray::stats::bvhLeaves << "(" << (int)(100.0*rawray::stats::bvhLeaves/(rawray::stats::bvhLeaves+rawray::stats::bvhSplits)) << "%)" << std::endl;
		std::cout << "Number of BVH Splits: " << rawray::stats::bvhSplits << "(" << (int)(100.0*rawray::stats::bvhSplits/(rawray::stats::bvhLeaves+rawray::stats::bvhSplits)) << "%)" << std::endl;
		std::cout << "Average Objects per Leaf: " << float(scene_.GetNumObjects())/(rawray::stats::bvhLeaves) << std::endl;
		
		std::cout << "Number of Box Intersections: " << rawray::stats::boxIntersections << "(" << (int)(100.0*rawray::stats::boxIntersections/(rawray::stats::boxIntersections+rawray::stats::triangleIntersections)) << "%)" << std::endl;
		std::cout << "Number of Triangle Intersections: " << rawray::stats::triangleIntersections << "(" << (int)(100.0*rawray::stats::triangleIntersections/(rawray::stats::boxIntersections+rawray::stats::triangleIntersections)) << "%)" << std::endl;

		std::cout << "Number of Primary Rays: " << rawray::stats::primaryRays << "(" << (int)(100.0*rawray::stats::primaryRays/(rawray::stats::primaryRays+rawray::stats::shadowRays)) << "%)" << std::endl;
		std::cout << "Number of Shadow Rays: " << rawray::stats::shadowRays << "(" << (int)(100.0*rawray::stats::shadowRays/(rawray::stats::primaryRays+rawray::stats::shadowRays)) << "%)" << std::endl;

        std::cout << "Average intersections/ray: " << float(rawray::stats::triangleIntersections)/(rawray::stats::primaryRays + rawray::stats::shadowRays) << std::endl;
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
