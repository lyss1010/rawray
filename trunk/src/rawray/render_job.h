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
#include "ray_caster.h"

/////////////////////////////////////////////////////////////////////////////
namespace rawray {

class DllExport RenderTask
{
public:
    RenderTask(HitPack* packs, int numpacks) : packs_(packs), numpacks_(numpacks) { }
    ~RenderTask() { }

    bool Run( Scene& scene, const Camera& cam, Image& img, float* progress );

private:
    HitPack* packs_;
    int numpacks_;

    DISALLOW_IMPLICIT_CONSTRUCTORS(RenderTask);
};


/////////////////////////////////////////////////////////////////////////////
class DllExport RenderThread
{
public:
    RenderThread(Scene& scene, const Camera& cam, Image& img);
    ~RenderThread();

    bool IsIdle() { return currentTask_==NULL; }
    bool IsDone() { return isDone_; }
    float Progress() { return progress_; }
    void SetCurrentTask(RenderTask* task) { if( !abort_ ) currentTask_ = task; }
    void Abort();

    DWORD ThreadRoutine();

private:
    Scene& scene_;
    const Camera& cam_;
    Image& img_;
    RenderTask* currentTask_;
    HANDLE threadHandle_;
    DWORD threadID_;
    bool abort_;
    bool isDone_;
    float progress_;

    DISALLOW_IMPLICIT_CONSTRUCTORS(RenderThread);
};


/////////////////////////////////////////////////////////////////////////////
class DllExport RenderJob
{
public:
    RenderJob(int numThreads, Scene& scene, const Camera& cam, Image& img, int aax, int aay) :
            numThreads_(numThreads), scene_(scene), cam_(cam), img_(img), caster_(cam_, aax, aay),
            threadID_(NULL), threadHandle_(NULL), abort_(false), isDone_(false) { }

    ~RenderJob();

    float Progress();
    bool Run(int aax, int aay);
    bool IsDone() { return isDone_; }
    void Abort();
    void DisplayStats();

    DWORD ThreadRoutine();

private:
    void Cleanup();

    uint32 numThreads_;
    Scene& scene_;
    const Camera& cam_;
    RayCaster caster_;
    Image& img_;
    HANDLE threadHandle_;
    DWORD threadID_;
    bool abort_;
    bool isDone_;
    
    std::stack<RenderTask*> assignedTasks_;
    std::stack<RenderTask*> tasks_;
    std::list<RenderThread*> threads_;

    DISALLOW_IMPLICIT_CONSTRUCTORS(RenderJob);
};

} // namespace rawray

// Public Global functions for CreateThread
DWORD WINAPI RawRay_RenderJob_Handler(LPVOID lpParameter);
DWORD WINAPI RawRay_RenderThread_Handler(LPVOID lpParameter);

#endif // RAWRAY_RAWRAY_RENDER_JOB_H
