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

bool Image::GaussianBlur(float sigma) {
    if( sigma < 0.0f ) return false;
    // See: http://en.wikipedia.org/wiki/Gaussian_blur

    // Clamp the gaussian distribution off at a fixed distance (3sigma pixels in each direction)
    int half_matrix_size = static_cast<int>(3*sigma);
    int matrix_size = 1 + 2*half_matrix_size;

    // Precompute matrix with weight multipliers
    float two_sigma_squared = 2 * sigma * sigma;
    float scale = 1.0f / ( math::PI * two_sigma_squared );
    float exponent_scale = -1.0f / two_sigma_squared;
    
    float* weights = new float[matrix_size * matrix_size];
    for( int y=0; y<matrix_size; ++y ) {
        float dY = y - half_matrix_size;
        float yy = dY*dY;
        for( int x=0; x<matrix_size; ++x ) {
            float dX = x - half_matrix_size;
            weights[ x + y*matrix_size ] = scale * exp( exponent_scale * (dX*dX + yy) );
        }
    }

    // Loop over all pixels
    for( int y=0; y<height_; ++y ) {
        for( int x=0; x<width_; ++x ) {
            Pixel sum = Pixel(0,0,0);
            int left = x - half_matrix_size;
            int top = y - half_matrix_size;

            // Loop over our weight matrix and add up values of pixels*weight
            // Ensure we are not trying to compute values of out of bounds pixels
            for( int j=0; j<matrix_size; ++j ) {
                int posY = top + j;
                if( posY < 0 || posY >= height_ )
                    continue;

                for( int i=0; i<matrix_size; ++i ) {
                    int posX = left + i;
                    if( posX < 0 || posX >= width_ )
                        continue;

                    Pixel* pixel = pixels_ + y*width_ + x;
                    float weight = weights[ i + matrix_size*j ];

                    sum.x += pixel->x * weight;
                    sum.y += pixel->y * weight;
                    sum.z += pixel->z * weight;
                }
            }
        }
    }

    delete [] weights;
    return true;
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
