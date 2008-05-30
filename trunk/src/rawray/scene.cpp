/////////////////////////////////////////////////////////////////////////////
// scene.cpp
//
/////////////////////////////////////////////////////////////////////////////
#include "scene.h"
#include "light.h"
#include "sphere_light.h"
#include "square_light.h"
#include "material.h"
#include "emitter.h"
#include "triangle_mesh.h"
#include "triangle_factory.h"
#include "bloom.h"
#include "sphere.h"

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
	const float deltaProgress = 1.0f / numpacks;

	for( int i=0; i<numpacks; ++i ) {
		HitPack& pack = *hitpacks++;

		IntersectPack( pack );
        ShadePack( pack, image );

		progress += deltaProgress;
	}
}

void Scene::ShadePack( HitPack& hitpack, Image& image ) {
    for( int pack=0; pack<4; ++pack ) {
		Vector4& pixel = image.GetPixel(hitpack.hits[pack].imgCoord.x, hitpack.hits[pack].imgCoord.y );

        if( hitpack.hit_result[pack] != 0.0f )
			pixel += hitpack.hits[pack].weight * hitpack.hits[pack].material->Shade(hitpack.hits[pack], *this);
        else
            pixel += hitpack.hits[pack].weight * background_.GetColor(hitpack.hits[pack].eyeRay.direction);
    }
}

void Scene::PostProcess(Image& img) {
	std::cout << std::endl << "\nPerforming post processing...";

	std::cout << " Bloom...";
	Bloom::Process(img);

	std::cout << std::endl;
}

float Scene::GetLightIntensity(const Light& light, const HitInfo& hit ) {
	float numLit = 0.0f;
	HitInfo tempHit = hit;

	for( int i=0; i<light.GetNumSamples(); ++i ) {
		tempHit.eyeRay.direction = light.GetRandPosition() - hit.point;
		const float length = tempHit.eyeRay.direction.NormalizeGetLength();

		// See if we are in shadow or not
		if( !Intersect( tempHit, MIN_DISTANCE, length ) )
			numLit += 1.0f;
		else // If we hit something, see what it was and see how much we can see through it
			numLit += tempHit.material->GetTranslucency();
	}

	// Get the one direction we will use for falloff calculations
	Vector3 direction = light.GetPosition() - hit.point;
	const float distance2 = direction.Length2();
	const float falloff = light.Falloff(distance2);

	const float litPercent = numLit / light.GetNumSamples();

	// 1/4PI is because of the sphere falloff of light
	return litPercent * falloff * light.GetWattage() * math::INV_QUARTER_PI;
}

// This should not be here
void Scene::AddSphereLightAsObject(Light* light) {
	Material* mat = new Emitter( light->GetColor() );
	AddMaterial( mat );

	SphereLight* slight = dynamic_cast<SphereLight*>(light);
	AddObject( new Sphere(light->GetPosition(), slight->GetRadius(), mat) );
}

// This should not be here
void Scene::AddSquareLightAsObject(Light* light) {
	Material* mat = new Emitter( light->GetColor() );
	AddMaterial( mat );
	
	SquareLight* slight = dynamic_cast<SquareLight*>(light);
	const Vector3 p0 = slight->GetPosition();
	const Vector3 p1 = p0 + slight->GetD1();
	const Vector3 p2 = p0 + slight->GetD2();
	const Vector3 p3 = p0 + slight->GetD1() + slight->GetD2();

	Vector3 normal; math::Cross( slight->GetD1(), slight->GetD2(), normal );

	TriangleMesh* triA = new TriangleMesh();
	TriangleMesh* triB = new TriangleMesh();
	AddMesh( triA );
	AddMesh( triB );

	triA->CreateSingleTriangle();
	triA->SetV1( p2 ); triA->SetN1( normal );
	triA->SetV2( p1 ); triA->SetN2( normal );
	triA->SetV3( p0 ); triA->SetN3( normal );
	AddObject( TriangleFactory::NewTriangle( triB, 0, mat ) );

	triB->CreateSingleTriangle();
	triB->SetV1( p3 ); triB->SetN1( normal );
	triB->SetV2( p1 ); triB->SetN2( normal );
	triB->SetV3( p2 ); triB->SetN3( normal );
	AddObject( TriangleFactory::NewTriangle( triA, 0, mat ) );
}

void Scene::AddLightAsObject(Light* light) {
	switch( light->ThisFunctionShouldNotBeHere() ) {
		case 0: // point light
			break;

		case 1: // square light
			AddSphereLightAsObject( light );
			break;

		case 2: // sphere light
			AddSquareLightAsObject( light );
			break;
	}
}

} // namespace rawray
