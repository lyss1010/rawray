/////////////////////////////////////////////////////////////////////////////
// scene.cpp
//
/////////////////////////////////////////////////////////////////////////////
#include "scene.h"
#include "light.h"

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

} // namespace rawray
