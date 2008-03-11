/////////////////////////////////////////////////////////////////////////////
// scene.cpp
//
/////////////////////////////////////////////////////////////////////////////
#include "scene.h"
#include "light.h"
#include "material.h"

namespace rawray {

void Scene::RenderGL() {
    for (size_t i=0; i<objects_.size(); ++i )
        objects_[i]->RenderGL();
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

void Scene::Raytrace(const Camera& cam, Image& image) {
    Ray eyeRay;
    HitInfo hit;
    Vector3 shadedColor;
    uint32 width = image.GetWidth();
    uint32 height = image.GetHeight();

    // For all pixels in the image
    for (uint32 y=0; y<height; ++y) {
        for (uint32 x=0; x<width; ++x) {
            eyeRay = cam.EyeRay(x, y, 0.5f, 0.5f, width, height);

            if (Intersect( hit, eyeRay )) {
                shadedColor = hit.material == NULL ? 
                    options::bg_color : 
                    hit.material->Shade(eyeRay, hit, *this);
            }
        }
    }

    PostProcess(image);
}

void Scene::PostProcess(Image& img) {
	UNREFERENCED_PARAMETER(img);
}

} // namespace rawray
