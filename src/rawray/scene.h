/////////////////////////////////////////////////////////////////////////////
// Class : scene.h
//
/////////////////////////////////////////////////////////////////////////////
#ifndef RAWRAY_RAWRAY_SCENE_H
#define RAWRAY_RAWRAY_SCENE_H
#include "stdafx.h"
#include "bvh.h"
#include "object.h"
#include "camera.h"
#include "image.h"

/////////////////////////////////////////////////////////////////////////////
namespace rawray {

class Light;

class DllExport Scene : Object
{
public:
    Scene() : Object(NULL), bvh_(&objects_) { }
    virtual ~Scene() { }

    const std::vector<Object*>& GetObjects() const { return objects_; }
    const std::vector<Light*>& GetLights() const { return lights_; }

    void AddObject(Object* object) { objects_.push_back(object); }
    void AddLight(Light* light) { lights_.push_back(light); }

    virtual void RenderGL();
    virtual void PreCalc();

    virtual bool Intersect(HitInfo& hit, const Ray& ray, float minDistance = 0.0f, float maxDistance = MAX_DISTANCE);

    void Raytrace(const Camera& cam, Image& image, uint32 xStart, uint32 yStart, uint32 width, uint32 height);
    void Raytrace(const Camera& cam, Image& image);

private:
    void PostProcess(Image& img);

    std::vector<Object*> objects_;
    std::vector<Light*> lights_;
    BVH bvh_;
    
    DISALLOW_COPY_CONSTRUCTORS(Scene);

}; // class Scene

} // namespace rawray
/////////////////////////////////////////////////////////////////////////////


#endif // RAWRAY_RAWRAY_SCENE_H
