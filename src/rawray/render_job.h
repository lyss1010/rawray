/////////////////////////////////////////////////////////////////////////////
// Class : render_job.h
//
/////////////////////////////////////////////////////////////////////////////
#ifndef RAWRAY_RAWRAY_RENDER_JOB_H
#define RAWRAY_RAWRAY_RENDER_JOB_H
#include "stdafx.h"
#include "camera.h"
#include "scene.h"
#include "image.h"

/////////////////////////////////////////////////////////////////////////////
namespace rawray {

class DllExport RenderTask
{
public:
    RenderTask(uint32 scanline) : scanline_(scanline) { }
    ~RenderTask() { }

    bool Run( Scene& scene, const Camera& cam, Image& img );

private:
    uint32 scanline_;

    DISALLOW_IMPLICIT_CONSTRUCTORS(RenderTask);
};


/////////////////////////////////////////////////////////////////////////////
class DllExport RenderThread
{
public:
    RenderThread(Scene& scene, const Camera& cam, Image& img) :
            scene_(scene), cam_(cam), img_(img), currentTask_(NULL) { }

    ~RenderThread() { }

    bool Run();
    bool IsDone() { return currentTask_==NULL; }
    void SetSelfDeletion(bool deleteSelf) { deleteSelf_ = deleteSelf; }

private:
    Scene& scene_;
    const Camera& cam_;
    Image& img_;
    RenderTask* currentTask_;
    bool deleteSelf_;
    uint32 threadID_;

    DISALLOW_IMPLICIT_CONSTRUCTORS(RenderThread);
};


/////////////////////////////////////////////////////////////////////////////
class DllExport RenderJob
{
public:
    RenderJob(uint32 numThreads, Scene& scene, const Camera& cam, Image& img) :
            numThreads_(numThreads), scene_(scene), cam_(cam), img_(img) { }

    ~RenderJob();

    bool Run();
    bool IsDone();

private:
    void Cleanup();

    uint32 numThreads_;
    Scene& scene_;
    const Camera& cam_;
    Image& img_;
    bool isRunning_;
    uint32 threadID_;
    
    std::list<RenderTask*> tasks_;
    std::list<RenderThread*> threads_;

    DISALLOW_IMPLICIT_CONSTRUCTORS(RenderJob);
};

} // namespace rawray

#endif // RAWRAY_RAWRAY_RENDER_JOB_H
