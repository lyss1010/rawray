/////////////////////////////////////////////////////////////////////////////
// Class : camera.h
//
/////////////////////////////////////////////////////////////////////////////
#ifndef RAWRAY_RAWRAY_CAMERA_H
#define RAWRAY_RAWRAY_CAMERA_H
#include "stdafx.h"
#include "math/vector3.h"
#include "ray.h"
#include "hit_info.h"
#include "image.h"

/////////////////////////////////////////////////////////////////////////////
namespace rawray {

class DllExport Camera
{
public:
    Camera();
    ~Camera() { }

    inline void SetEye(const Vector3& eye) { eye_=eye; }
    inline void SetUp(const Vector3& up) { up_=up; }
    inline void SetViewDir(const Vector3& viewDir) { viewDir_=viewDir; }
    inline void SetLookAt(const Vector3& lookAt) { lookAt_=lookAt; }
    inline void SetFOV(float fov) { fov_=fov; }
    inline void SetAspect(float aspect) { aspect_=aspect; }
    inline void SetMinDraw(float minDraw) { minDraw_=minDraw; }
    inline void SetMaxDraw(float maxDraw) { maxDraw_=maxDraw; }

    inline const Vector3& GetEye() const { return eye_; }
    inline const Vector3& GetUp() const { return up_; }
    inline const Vector3& GetViewDir() const { return viewDir_; }
    inline const Vector3& GetLookAt() const { return lookAt_; }
    inline float GetFOV() const { return fov_; }
    inline float GetAspect() const { return aspect_; }
    inline float GetMinDraw() const { return minDraw_; }
    inline float GetMaxDraw() const { return maxDraw_; }

    Ray EyeRay(int x, int y, float xOffset, float yOffset, int width, int height) const;

	void Resize(int x, int y);
    void RenderGL();
    void RenderImage();

private:
    void CalcLookAt();

    Vector3 eye_;
    Vector3 up_;
    Vector3 viewDir_;
    Vector3 lookAt_;

    float fov_;
    float aspect_;
    float minDraw_;
    float maxDraw_;

    bool redrawImage_;

    DISALLOW_COPY_CONSTRUCTORS(Camera);

}; // class Camera

} // namespace rawray
/////////////////////////////////////////////////////////////////////////////


#endif // RAWRAY_RAWRAY_CAMERA_H
