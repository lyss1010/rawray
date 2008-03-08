/////////////////////////////////////////////////////////////////////////////
// image.cpp
//
/////////////////////////////////////////////////////////////////////////////
#include "image.h"
#include "conversions.h"

namespace rawray {

    Image::Image() : pixels_(NULL), width_(0), height_(0) { }

    Image::Image(const Image& i) {
        register uint32 numPixels = Resize(i.width_, i.height_);

        if( numPixels > 0 ) {
            memcpy( static_cast<void*>(pixels_), 
                    static_cast<void*>(i.pixels_), 
                    numPixels*sizeof( *pixels_ ) );
        } else {
            pixels_ = NULL;
            width_ = height_ = 0;
        }
    }

    Image::~Image() {
        SAFE_DELETE_ARRAY( pixels_ );
    }

    int Image::Resize(uint32 width, uint32 height) {
        if( width < 0 || height < 0 )
            return 0;

        SAFE_DELETE_ARRAY( pixels_ );
        width_ = width;
        height_ = height;

        register uint32 numPixels = width_*height_;
        pixels_ = new Pixel[ numPixels ];

        return numPixels;
    }

    void Image::SetPixel(uint32 x, uint32 y, const math::Vector3& color) {
        if( x < width_ && y < height_ ) {
            Pixel* pixel = pixels_ + y*width_ + x;
            pixel->x = base::FloatToByte(color.x);
            pixel->y = base::FloatToByte(color.y);
            pixel->z = base::FloatToByte(color.z);
        }
    }

    void Image::SetPixel(uint32 x, uint32 y, const Pixel& color) {
        if( x < width_ && y < height_ )
            pixels_[ y*width_ + x ] = color;
    }

    void Image::Clear(const math::Vector3 &color) {
        for(uint32 y=0; y<height_; y++)
            for(uint32 x=0; x<width_; x++)
                SetPixel( x, y, color );
    }

    void Image::Clear(const Pixel &color) {
        for(uint32 y=0; y<height_; y++)
            for(uint32 x=0; x<width_; x++)
                SetPixel( x, y, color );
    }

    void Image::RenderGL() {
        for(uint32 y=0; y<height_; ++y)
            RenderScanlineGL(y);
    }

    void Image::RenderScanlineGL(uint32 y) {
        register float divisor_height = 1.0f / height_;

        for(uint32 x=0; x<width_; ++x)
        {
            //glRasterPos2f(-1, -1 + 2*y * divisor_height);
            //glDrawPixels(width_, 1, GL_RGB, GL_UNSIGNED_BYTE, &pixels_[y*width_]);
        }
    }

} // namespace rawray
