/////////////////////////////////////////////////////////////////////////////
// render_job.cpp
//
/////////////////////////////////////////////////////////////////////////////
#include "render_job.h"

namespace rawray {

/////////////////////////////////////////////////////////////////////////////
bool RenderTask::Run(Scene& scene, const Camera& cam, Image& img) {
    scene.Raytrace(cam, img, 0, scanline_, img.GetWidth(), 1);
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
}

RenderThread::~RenderThread() {
    // Block here waiting for controller thread to finish
    abort_ = true;
    while( !IsDone() )
        Sleep( 0 );

    if( threadHandle_ != NULL )
        CloseHandle(threadHandle_);
}

DWORD RenderThread::ThreadRoutine() {
    while( !abort_ ) {
        if( currentTask_ == NULL )
            Sleep( 0 );
        else {
            currentTask_->Run( scene_, cam_, img_ );
            delete currentTask_;
            currentTask_ = NULL;
        }
    }

    return 0;
}

/////////////////////////////////////////////////////////////////////////////
RenderJob::~RenderJob() {
    // Block here waiting for controller thread to finish
    abort_ = true;
    while( !IsDone() )
        Sleep( 0 );

    Cleanup();
}

void RenderJob::Cleanup() {
    // Clean up any unprocessed tasks
    while( !tasks_.empty() )
    {
        RenderTask* task = tasks_.top();
        tasks_.pop();
        delete task;
    }

    assert( threads_.empty() );
}

bool RenderJob::IsDone() {
    return tasks_.empty() && threads_.empty();
}

bool RenderJob::Run() {
    if( numThreads_ < 1 )
        return false;

    // Create a list of tasks we need done
    const uint32 imgHeight = img_.GetHeight();
    for( uint32 y=0; y<imgHeight; ++y )
        tasks_.push( new RenderTask(y) );

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

    return true;
}

DWORD RenderJob::ThreadRoutine() {
    std::list<RenderThread*>::iterator threadIter;
    std::list<RenderThread*>::iterator toDelete;

    while( !IsDone() ) {
        // Loop through all running threads 
        threadIter = threads_.begin();
        while( threadIter != threads_.end() ) {
            RenderThread* thread = *threadIter;

            // If this thread has no work, give it work
            if( thread->IsDone() ) {
                if( tasks_.empty() || abort_ ) {
                    // Delete this thread if there is no work to give it
                    toDelete = threadIter;
                    threadIter++;
                    threads_.erase( toDelete );

                    delete thread;
                } else {
                    thread->SetCurrentTask( tasks_.top() );
                    tasks_.pop();
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
