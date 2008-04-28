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

    Object* AddObject(Object* object) { objects_.push_back(object); return object; }
    Light* AddLight(Light* light) { lights_.push_back(light); return light; }
	Material* AddMaterial(Material* mat) { materials_.push_back(mat); return mat; }
	TriangleMesh* AddMesh(TriangleMesh* mesh) { meshes_.push_back(mesh); return mesh; }

    virtual void RenderGL();
    virtual void PreCalc();

    virtual bool Intersect(HitInfo& hit, float minDistance = MIN_DISTANCE, float maxDistance = MAX_DISTANCE );
    virtual void IntersectPack(HitPack& hitpack, float minDistance = MIN_DISTANCE, float maxDistance = MAX_DISTANCE );

    void Raytrace(const Camera& cam, Image& image, int xStart, int yStart, int width, int height);
    void Raytrace(const Camera& cam, Image& image);

    void PostProcess(Image& img);

private:
	std::vector<Material*> materials_;
    std::vector<Object*> objects_;
    std::vector<Light*> lights_;
	std::vector<TriangleMesh*> meshes_;
    BVH bvh_;

    void ShadePack( const HitPack& hitpack, Image& image );

    DISALLOW_COPY_CONSTRUCTORS(Scene);

}; // class Scene

} // namespace rawray
/////////////////////////////////////////////////////////////////////////////


#endif // RAWRAY_RAWRAY_SCENE_H
