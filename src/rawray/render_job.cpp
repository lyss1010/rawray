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
RenderJob::~RenderJob() {
    // Indicate to controller thread to clean up as soon as it can
    running_ = false;
    
    // Block here waiting for controller thread to finish
    while( !IsDone() )
        Sleep( 0 );
}

RenderJob::Cleanup() {
    // Clean up any unprocessed tasks
    for( std::list<RenderTask*>::iterator task=tasks_.begin(); task != tasks_.end(); ++task )
        delete *task;

    // Kill all running threads
    for( std::list<RenderThread*>::iterator thread=threads_.begin(); thread != threads_.end(); ++thread ) {
        
    }
    
}

bool RenderJob::IsDone() {
    return availableTasks_.empty() && runningThreads_.empty();
}

// NOTE: Total threads will be numThreads + 1 because there is one "job controller" thread
bool RenderJob::Run() {
    if( numThreads_ < 1 )
        return false;

    // Create a list of tasks we need done
    const uint32 imgHeight = img_.GetHeight();
    for( uint32 y=0; y<imgHeight; ++y )
        tasks_.push_back( new RenderTask(y) );

    // Create the user specified number of threads
    for( uint32 thread=0; thread<numThreads_; ++thread )
        threads_.push_back( new RenderThread(

    // Create the master controller thread (paused)

    // Begin all threads

    return true;
}

} // namespace rawray


//
///////////////////////////////////////////////////////////////////////////////
//DWORD WINAPI RawRay_RenderJob_Handler_Thread(LPVOID lpParameter)
//{
//	assert(lpParameter);
//	RenderJob* job = static_cast<RenderJob*>(lpParameter);
//
//    while( !job->IsDone() ) {
//        
//    }
//}
//
///////////////////////////////////////////////////////////////////////////////
//DWORD WINAPI RawRay_RenderThread_Handler_Thread(LPVOID lpParameter)
//{
//	assert(lpParameter);
//	RenderThread* thread = static_cast<RenderThread*>(lpParameter);
//
//    while( true )  {
//        
//    }
//}
