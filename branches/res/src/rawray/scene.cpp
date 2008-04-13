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

	for( size_t i=0; i<objects_.size(); ++i )
		delete objects_[i];
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
}

void Scene::PreCalc() {
    std::vector<Object*>::iterator obj_it;
    for (obj_it = objects_.begin(); obj_it != objects_.end(); ++obj_it)
        (*obj_it)->PreCalc();

    std::vector<Light*>::iterator light_it;
    for (light_it = lights_.begin(); light_it != lights_.end(); ++light_it)
        (*light_it)->PreCalc();

    bvh_.PreCalc();
}

bool Scene::Intersect(HitInfo& hit, const Ray& ray, float minDistance, float maxDistance) {
    return bvh_.Intersect(hit, ray, minDistance, maxDistance );
}

void Scene::Raytrace(const Camera& cam, Image& image, uint32 xStart, uint32 yStart, uint32 width, uint32 height)
{
    Ray eyeRay;
    HitInfo hit;
    Vector3 shadedColor;
    
    const uint32 imgWidth = image.GetWidth();
    const uint32 imgHeight = image.GetHeight();

    // clip to the image so we don't go out of bounds
    width = std::min( xStart+width, imgWidth );
    height = std::min( yStart+height, imgHeight );

    // For all defined pixels in rectangle
    for (uint32 y=yStart; y<height; ++y) {
        for (uint32 x=xStart; x<width; ++x) {
            eyeRay = cam.EyeRay(x, y, 0.5f, 0.5f, imgWidth, imgHeight);

			if ( Intersect( hit, eyeRay ) && hit.material != NULL )
                shadedColor = hit.material->Shade(eyeRay, hit, *this);
			else
                shadedColor = options::global::img_bg_color;

			image.SetPixel( x, y, shadedColor );
        }
    }
}

void Scene::Raytrace(const Camera& cam, Image& image) {
    Raytrace(cam, image, 0, 0, image.GetWidth(), image.GetHeight());

    PostProcess(image);
}

void Scene::PostProcess(Image& img) {
	UNREFERENCED_PARAMETER(img);
}

} // namespace rawray