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
    RenderThread(Scene& scene, const Camera& cam, Image& img);
    ~RenderThread();

    bool IsDone() { return currentTask_==NULL; }
    void SetCurrentTask(RenderTask* task) { currentTask_ = task; }
    DWORD ThreadRoutine();

private:
    Scene& scene_;
    const Camera& cam_;
    Image& img_;
    RenderTask* currentTask_;
    HANDLE threadHandle_;
    DWORD threadID_;
    bool abort_;

    DISALLOW_IMPLICIT_CONSTRUCTORS(RenderThread);
};


/////////////////////////////////////////////////////////////////////////////
class DllExport RenderJob
{
public:
    RenderJob(uint32 numThreads, Scene& scene, const Camera& cam, Image& img) :
            numThreads_(numThreads), scene_(scene), cam_(cam), img_(img),
            threadID_(NULL), threadHandle_(NULL), abort_(false) { }

    ~RenderJob();

    bool Run();
    bool IsDone();
    DWORD ThreadRoutine();

private:
    void Cleanup();

    uint32 numThreads_;
    Scene& scene_;
    const Camera& cam_;
    Image& img_;
    HANDLE threadHandle_;
    DWORD threadID_;
    bool abort_;
    
    std::stack<RenderTask*> tasks_;
    std::list<RenderThread*> threads_;

    DISALLOW_IMPLICIT_CONSTRUCTORS(RenderJob);
};

} // namespace rawray

// Public Global functions for CreateThread
DWORD WINAPI RawRay_RenderJob_Handler(LPVOID lpParameter);
DWORD WINAPI RawRay_RenderThread_Handler(LPVOID lpParameter);

#endif // RAWRAY_RAWRAY_RENDER_JOB_H
