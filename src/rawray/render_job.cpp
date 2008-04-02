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
bool RenderThread::Run() {
    if( currentTask_ == NULL )
        return true;

    bool success = currentTask_->Run(scene_, cam_, img_);
    delete currentTask_;
    currentTask_ = NULL;

    // WARNING: At this point there could be a race condition
    // If the RenderJob tries to delete this and we try to delete this at the same time
    // We should not need deleteSelf_ if our threads properly execute to completion anyway
    // This is only for aborting mid-render
    if( deleteSelf_ )
        delete this;

    return success;
}

/////////////////////////////////////////////////////////////////////////////
RenderJob::~RenderJob() {
    // Indicate to controller thread to clean up as soon as it can
    isRunning_ = false;
    
    // Block here waiting for controller thread to finish
    while( !IsDone() )
        ;//Sleep( 0 );

    // NOTE: There is a possible race condition in cleanup
    // We avoid this by blocking above and waiting for running threads to finish
    // This means deletion of RenderJob is blocking, but safe
    Cleanup();
}

void RenderJob::Cleanup() {
    // Clean up any unprocessed tasks
    for( std::list<RenderTask*>::iterator task=tasks_.begin(); task != tasks_.end(); ++task )
        delete *task;

    // Delete threads which are completed but still sitting on our running list
    // This list *should* be empty by the time we call cleanup!!!
    // There should not be any running threads left at this point
    // But if there are, tell running threads to delete themselves once done
    std::list<RenderThread*>::iterator thread=threads_.begin();
    while( thread != threads_.end() )
    {
        RenderThread* toDelete = *thread++;

        // WARNING: Possible race condition when deleting object
        // If we block in ~RenderJob waiting for IsDone()==true
        // We can avoid this completely
        if( toDelete->IsDone() )
            delete toDelete;
        else
            toDelete->SetSelfDeletion(true);
    }
}

bool RenderJob::IsDone() {
    return tasks_.empty() && threads_.empty();
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
        threads_.push_back( new RenderThread(scene_, cam_, img_) );

    // Create the master controller thread (paused)
    

    // Begin all threads
    

    return true;
}

} // namespace rawray



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
