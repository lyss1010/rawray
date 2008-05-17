/////////////////////////////////////////////////////////////////////////////
// scene.cpp
//
/////////////////////////////////////////////////////////////////////////////
#include "scene.h"
#include "light.h"
#include "material.h"
#include "triangle_mesh.h"

namespace rawray {

Scene::~Scene() {
    for( size_t i=0; i<lights_.size(); ++i )
		delete lights_[i];
	lights_.clear();

	// NOTE: We can not use the 'delete' call because some objects are created memory aligned
	for( size_t i=0; i<objects_.size(); ++i )
		objects_[i]->deleteObject();
	objects_.clear();

	for( size_t i=0; i<materials_.size(); ++i )
		delete materials_[i];
	materials_.clear();

	for( size_t i=0; i<meshes_.size(); ++i )
		delete meshes_[i];
	meshes_.clear();
}

void Scene::RenderGL() {
    for (size_t i=0; i<objects_.size(); ++i )
        objects_[i]->RenderGL();

    for( size_t i=0; i<lights_.size(); ++i )
        lights_[i]->RenderGL();

	bvh_.RenderGL();
}

void Scene::PreCalc() {
    std::vector<Object*>::iterator obj_it;
	for (obj_it = objects_.begin(); obj_it != objects_.end(); ++obj_it) {
		Object* obj = (*obj_it);
        obj->PreCalc();
	}

    std::vector<Light*>::iterator light_it;
    for (light_it = lights_.begin(); light_it != lights_.end(); ++light_it)
        (*light_it)->PreCalc();

    bvh_.PreCalc();
}

void Scene::IntersectPack(HitPack& hitpack, float minDistance, float maxDistance) {
    bvh_.IntersectPack(hitpack, minDistance, maxDistance);
}

bool Scene::Intersect(HitInfo& hit, float minDistance, float maxDistance) {
    return bvh_.Intersect(hit, minDistance, maxDistance );
}

bool Scene::Hit(const Ray& ray, float minDistance, float maxDistance) const {
	return bvh_.Hit(ray, minDistance, maxDistance);
}

void Scene::Raytrace(Image& image, RayCaster& caster, float& progress ) {
	HitPack* hitpacks = caster.GetHitPacks();
	const int numpacks = caster.GetNumPacks();
	const float increment = caster.GetIncrement();
	const float deltaProgress = 1.0f / numpacks;

	for( int i=0; i<numpacks; ++i ) {
		HitPack& pack = *hitpacks++;

		IntersectPack( pack );
        ShadePack( pack, image, increment );

		progress += deltaProgress;
	}
}

void Scene::ShadePack( const HitPack& hitpack, Image& image, float increment ) {
    for( int pack=0; pack<4; ++pack ) {
		Vector3& pixel = image.GetPixel(hitpack.hits[pack].imgCoord.x, hitpack.hits[pack].imgCoord.y );

        if( hitpack.hit_result[pack] != 0.0f )
			pixel += increment * hitpack.hits[pack].material->Shade(hitpack.hits[pack], *this);
        else
            pixel += increment * background_.GetColor(hitpack.hits[pack].eyeRay.direction);
    }
}


void Scene::PostProcess(Image& img) {
	UNREFERENCED_PARAMETER(img);
}

} // namespace rawray
