/////////////////////////////////////////////////////////////////////////////
// ray_caster.cpp
//
/////////////////////////////////////////////////////////////////////////////
#include "ray_caster.h"
#include "hit_info.h"

namespace rawray {

void RayCaster::GenerateRays(const Camera& cam, int xmin, int xmax, int ymin, int ymax, int imgWidth, int imgHeight) {
    int numPixels = (xmax-xmin) * (ymax-ymin);
    numpacks_ = numPixels * aax_ * aay_ / 4;
    if( numpacks_ < 1 ) return;

    SAFE_DELETE_ARRAY( hitpacks_ );
    hitpacks_ = new HitPack[ numpacks_ ];

    float deltaX = 1.0f / (1+aax_);
    float deltaY = 1.0f / (1+aay_);

    // Loop over all pixels and shoot multiple rays for each one
	int x = xmin;
	int y = ymin;
    int packsize, packnum;
    packnum = packsize = 0;

    while( packnum < numpacks_ ) {
        HitPack* pack = hitpacks_ + packnum;

        // Cast multiple rays per pixel in a uniform grid
        float ypos = deltaY;
        for( int dy=0; dy<aay_; ++dy ) {
            
            float xpos = deltaX;
            for( int dx=0; dx<aax_; ++dx ) {
                assert( packnum < numpacks_ );

                pack->hits[packsize].eyeRay = cam.EyeRay( x, y, xpos, ypos, imgWidth, imgHeight );
                pack->hits[packsize].distance = MAX_DISTANCE;
                pack->hits[packsize].imgCoord.x = x;
                pack->hits[packsize].imgCoord.y = y;
                ++packsize;
                xpos += deltaX;

                if( packsize == 4 ) {
                    // Precompute data for this full pack
                    pack->PackData();
                    packsize = 0;
                    ++packnum;

                    pack = hitpacks_ + packnum ;
                }
            }

            ypos += deltaY;
        }

        // Move forward to next pixel
        if( ++x >= xmax ) {
            x = xmin;
			++y;
        }
    }
}

} // namespace rawray
