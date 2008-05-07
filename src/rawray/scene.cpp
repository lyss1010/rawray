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

void Scene::Raytrace(const Camera& cam, Image& image, int xStart, int yStart, int width, int height)
{
    Vector3 shadedColor;
    
    const int imgWidth = image.GetWidth();
    const int imgHeight = image.GetHeight();

    // clip to the image so we don't go out of bounds
    width = std::min( xStart+width, imgWidth );
    height = std::min( yStart+height, imgHeight );

    // NOTE: we will ignore unfull packs =(
    HitPack hitpack;
    int packsize = 0;
    for( int y=yStart; y<height; ++y ) {
        for( int x=xStart; x<width; ++x ) {
            // Add new item to pack
            hitpack.hits[packsize].eyeRay = cam.EyeRay( x, y, 0.5f, 0.5f, imgWidth, imgHeight );
            hitpack.hits[packsize].distance = MAX_DISTANCE;
            hitpack.hits[packsize].imgCoord.x = x;
            hitpack.hits[packsize].imgCoord.y = y;
            ++packsize;
            
            if( packsize == 4 ) {
                // Compute pre-compacted data for SIMD instructions
                hitpack.PackData();
                memset( hitpack.hit_result, 0, sizeof(hitpack.hit_result) );
                packsize = 0;
                
                // Shoot off pack if it is full
                IntersectPack( hitpack );
                ShadePack( hitpack, image );
            }
        }
    }
}

void Scene::ShadePack( const HitPack& hitpack, Image& image ) {
    for( int pack=0; pack<4; ++pack ) {
        if( hitpack.hit_result[pack] != 0.0f ) {
            // NOTE: It's the users's fault if the material is null
            if( hitpack.hits[pack].material ) {
                image.SetPixel( hitpack.hits[pack].imgCoord.x, 
                                hitpack.hits[pack].imgCoord.y, 
                                hitpack.hits[pack].material->Shade(hitpack.hits[pack], *this) );
            } else
                image.SetPixel( hitpack.hits[pack].imgCoord.x,
                                hitpack.hits[pack].imgCoord.y,
                                options::global::img_fg_color );
        } else {
            image.SetPixel( hitpack.hits[pack].imgCoord.x,
                            hitpack.hits[pack].imgCoord.y,
                            options::global::img_bg_color );
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
