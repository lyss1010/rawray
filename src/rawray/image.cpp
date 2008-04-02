/////////////////////////////////////////////////////////////////////////////
// image.cpp
//
/////////////////////////////////////////////////////////////////////////////
#include "image.h"
#include "base/conversions.h"

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

void Image::SetPixel(uint32 x, uint32 y, const Vector3& color) {
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

void Image::Clear(const Vector3 &color) {
    for(uint32 y=0; y<height_; y++)
        for(uint32 x=0; x<width_; x++)
            SetPixel( x, y, color );
}

void Image::Clear(const Pixel &color) {
    for(uint32 y=0; y<height_; y++)
        for(uint32 x=0; x<width_; x++)
            SetPixel( x, y, color );
}

void Image::ScreenShot() {
    glReadPixels( 0, 0, width_, height_, 
                  GL_RGB, GL_RGB, pixels_ );
}

bool GaussianBlur(float sigma) {
    if( sigma < 0.0f ) return false;
    // See: http://en.wikipedia.org/wiki/Gaussian_blur

    // Clamp the gaussian distribution off at a fixed distance (rounding up)
    int weightMatrixSize = static_cast<int>(0.5f + 6*sigma);

    // Precompute matrix with weight multipliers
    float weights[] = new float[weightMatrixSize * weightMatrixSize];
    float two_sigma_sqared = 2 * sigma * sigma;

    for( int y=0; y<weightMatrixSize; ++y ) {
        for( int x=0; x<weightMatrixSize; ++x ) {


        }
    }
}

void Image::RenderGL() {
    for(uint32 y=0; y<height_; ++y)
        RenderScanlineGL(y);
}

void Image::RenderScanlineGL(uint32 y) {
    glRasterPos2f(-1, -1 + 2*y / float(height_));
    glDrawPixels(width_, 1, GL_RGB, GL_UNSIGNED_BYTE, &pixels_[y*width_]);
}

void Image::WritePPM(const char* filename) {
    WritePPM(filename, 
             static_cast<uint8*>( &((*pixels_).x) ), 
             width_, height_);
}

void Image::WritePPM(const char* filename, uint8* data, uint32 width, uint32 height) {
    FILE* fp = NULL;
    fp = fopen( filename, "wb" );
    if (fp) {
        fprintf(fp, "P6\n");
        fprintf(fp, "%d %d\n", width, height);
        fprintf(fp, "255\n");

        // Invert image
        int stride = width*3;
        for (int i = height-1; i >= 0; --i)
            fwrite( data + stride*i, stride, 1, fp );

        fclose(fp);
    }
}

} // namespace rawray
