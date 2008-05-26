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
#include "background.h"
#include "ray_caster.h"


/////////////////////////////////////////////////////////////////////////////
namespace rawray {

class Light;
class Material;
class TriangleMesh;

class DllExport Scene : public Object
{
public:
    Scene() : Object(NULL), bvh_(&objects_) { }
    ~Scene();

    const std::vector<Object*>& GetObjects() const { return objects_; }
    const std::vector<Light*>& GetLights() const { return lights_; }
	const std::vector<Material*>& GetMaterials() const { return materials_; }

	// TODO: Add lights as objects in the world so we can intersect directly w/ them and get their color + bloom
    Object* AddObject(Object* object) { objects_.push_back(object); return object; }
    Light* AddLight(Light* light) { lights_.push_back(light); return light; }
	Material* AddMaterial(Material* mat) { materials_.push_back(mat); return mat; }
	TriangleMesh* AddMesh(TriangleMesh* mesh) { meshes_.push_back(mesh); return mesh; }

    virtual void RenderGL();
    virtual void PreCalc();
    virtual Vector3 GetMin() { return Vector3(-MAX_DISTANCE); }
    virtual Vector3 GetMax() { return Vector3( MAX_DISTANCE); }

	virtual bool Hit(const Ray& ray, float minDistance = MIN_DISTANCE, float maxDistance = MAX_DISTANCE) const;
    virtual bool Intersect(HitInfo& hit, float minDistance = MIN_DISTANCE, float maxDistance = MAX_DISTANCE );
    virtual void IntersectPack(HitPack& hitpack, float minDistance = MIN_DISTANCE, float maxDistance = MAX_DISTANCE );

    void Raytrace(Image& image, RayCaster& caster, float& progress);
	float GetLightIntensity(const Light& light, const HitInfo& hit );

    void PostProcess(Image& img);
	size_t GetNumObjects() { return objects_.size(); }
	Background& GetBackground() { return background_; }

	Vector4 Shade(HitInfo& hit);

private:
	std::vector<Material*> materials_;
    std::vector<Object*> objects_;
    std::vector<Light*> lights_;
	std::vector<TriangleMesh*> meshes_;
    BVH bvh_;
	Background background_;

    void ShadePack( HitPack& hitpack, Image& image, float increment );

    DISALLOW_COPY_CONSTRUCTORS(Scene);

}; // class Scene

} // namespace rawray
/////////////////////////////////////////////////////////////////////////////


#endif // RAWRAY_RAWRAY_SCENE_H
