/////////////////////////////////////////////////////////////////////////////
// image.cpp
//
/////////////////////////////////////////////////////////////////////////////
#include "image.h"
#include "base/conversions.h"
#include <sstream>
#include "time.h"

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
    if( width == width_ && height == height_ )
        return width*height;

    width_ = width;
    height_ = height;

    register uint32 numPixels = width_*height_;
    if( numPixels <= 0 ) return 0;
    
    SAFE_DELETE_ARRAY( pixels_ );
    pixels_ = new Vector3[ numPixels ];
    memset( pixels_, 0, sizeof( *pixels_ )*numPixels );

    return numPixels;
}

void Image::SetPixel(uint32 x, uint32 y, const Vector3& color) {
    if( x < width_ && y < height_ )
		GetPixel(x, y) = color;
}

void Image::SetPixel(uint32 x, uint32 y, const math::Tuple3<uint8>& color) {
	if( x < width_ && y < height_ ) {
		Vector3& pixel = GetPixel(x, y);
		pixel.x = base::ByteToFloat(color.x);
		pixel.y = base::ByteToFloat(color.y);
		pixel.z = base::ByteToFloat(color.z);
	}
}

void Image::Clear(const Vector3 &color) {
    for(uint32 y=0; y<height_; y++)
        for(uint32 x=0; x<width_; x++)
            SetPixel( x, y, color );
}

void Image::Clear(const math::Tuple3<uint8> &color) {
    for(uint32 y=0; y<height_; y++)
        for(uint32 x=0; x<width_; x++)
            SetPixel( x, y, color );
}

void Image::ScreenShot() {
    glReadBuffer(GL_FRONT);

    // Disable packing so we don't buffer overrun
    glPushClientAttrib( GL_CLIENT_PIXEL_STORE_BIT );
    glPixelStorei(GL_PACK_ALIGNMENT, 1);
    
    glReadPixels( 0, 0, width_, height_, GL_RGB, GL_FLOAT, pixels_ );

    // Enable the default packing
    glPopClientAttrib();
}

bool Image::GaussianBlur(float sigma) {
    if( sigma < 0.0f ) return false;
    // See: http://en.wikipedia.org/wiki/Gaussian_blur

    // Clamp the gaussian distribution off at a fixed distance (x*sigma pixels in each direction)
    int half_matrix_size = static_cast<int>(options::global::gaussian_blur_max*sigma);
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
            Vector3 sum = Vector3(0,0,0);
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

                    Vector3& pixel = GetPixel(posX, posY);
                    float weight = weights[ i + matrix_size*j ];

                    sum.x += pixel.x * weight;
                    sum.y += pixel.y * weight;
                    sum.z += pixel.z * weight;
                }
            }

            SetPixel( x, y, sum );
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
    glDrawPixels(width_, 1, GL_RGB, GL_FLOAT, &pixels_[y*width_]);
}

void Image::WritePPM( ) {
    std::ostringstream filename;
    filename << "rawray_" << time(0) << ".ppm";

    WritePPM( filename.str().c_str() );
}

void Image::WritePPM( clock_t rendertime ) {
    std::ostringstream filename;
    filename << "rawray_" << time(0) << "_" << ( float(rendertime)/CLOCKS_PER_SEC ) << ".ppm";

    WritePPM( filename.str().c_str() );
}

void Image::WritePPM(const char* filename) {
	math::Tuple3<uint8>* data = new math::Tuple3<uint8>[ width_ * height_ ];

	for(uint32 y=0; y<height_; y++) {
		int yOffset = y*width_;
		for(uint32 x=0; x<width_; x++) {
			Vector3* p = pixels_ + yOffset + x;
			math::Tuple3<uint8>* d = data    + yOffset + x;

			d->x = base::FloatToByte( p->x );
			d->y = base::FloatToByte( p->y );
			d->z = base::FloatToByte( p->z );
		}
	}

    WritePPM(filename, static_cast<uint8*>( &((*data).x) ), width_, height_);
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
        std::cout << "\nWrote image to file: " << filename << std::endl;
    } else
        std::cout << "\nFailed to write image to file: " << filename << std::endl;
}

} // namespace rawray