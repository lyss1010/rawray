/////////////////////////////////////////////////////////////////////////////
// image.cpp
//
/////////////////////////////////////////////////////////////////////////////
#include "image.h"
#include "base/conversions.h"
#include <sstream>
#include "time.h"
#include "tools/pfm_loader.h"

namespace rawray {

Image::Image() : pixels_(NULL), width_(0), height_(0) { }

Image::~Image() {
    DeleteBuffer();
}

void Image::DeleteBuffer( ) {
    SAFE_DELETE_ARRAY( pixels_ );
}

Vector4& Image::GetBoundPixel(int x, int y) {
	if( x < 0 ) x = 0;
	if( y < 0 ) y = 0;
	if( x >= width_ ) x = width_ - 1;
	if( y >= height_ ) y = height_ - 1;

	return GetPixel(x, y);
}

Vector4& Image::GetUVPixel(float u, float v) {
	return GetBoundPixel( 
		0.5f*(1.0f+u)*(width_-1),
		0.5f*(1.0f+v)*(height_-1) );
}

Vector4& Image::Get0UVPixel(float u, float v) {
	return GetBoundPixel( 
		u*(width_-1),
		v*(height_-1) );
}

int Image::Resize(int width, int height) {
    if( width == width_ && height == height_ )
        return width*height;

    width_ = width;
    height_ = height;

    register int numPixels = width_*height_;
    if( numPixels <= 0 ) return 0;
    
    DeleteBuffer();

    pixels_ = new Vector4[ numPixels ];
    memset( pixels_, 0, sizeof( *pixels_ )*numPixels );
    return numPixels;
}

void Image::SetPixel(int x, int y, const Vector4& color) {
    if( x < width_ && y < height_ )
		GetPixel(x, y) = color;
}

void Image::SetPixel(int x, int y, const math::Tuple3<uint8>& color) {
	if( x < width_ && y < height_ ) {
		Vector4& pixel = GetPixel(x, y);
		pixel.x = base::ByteToFloat(color.x);
		pixel.y = base::ByteToFloat(color.y);
		pixel.z = base::ByteToFloat(color.z);
	}
}

void Image::Clear(const Vector4 &color) {
    for(int y=0; y<height_; y++)
        for(int x=0; x<width_; x++)
            SetPixel( x, y, color );
}

void Image::Clear(const math::Tuple3<uint8> &color) {
    Clear( Vector4(	base::ByteToFloat(color.x),
					base::ByteToFloat(color.y),
					base::ByteToFloat(color.z),
					0.0f) );
}

void Image::Clear(const Vector4& color, int x, int y, int width, int height) {
	for( int row=y; row<height; ++row )
		for( int col=x; col<width; ++col )
			SetPixel( col, row, color );
}

void Image::Clear(const math::Tuple3<uint8>& color, int x, int y, int width, int height) {
	Clear( Vector4( 
				base::ByteToFloat(color.x), 
				base::ByteToFloat(color.y), 
				base::ByteToFloat(color.z),
				0.0f), 
				x, y, width, height );
}

void Image::ScreenShot() {
    glReadBuffer(GL_FRONT);

    // Save the current packing value for pixel storage
    glPushClientAttrib( GL_CLIENT_PIXEL_STORE_BIT );

	// We will get alpha in the 4th component of our color
	// If we don't want this, clear it out later
    glPixelStorei(GL_PACK_ALIGNMENT, 4);
    glReadPixels( 0, 0, width_, height_, GL_RGBA, GL_FLOAT, pixels_ );

    // Re-enable the default packing
    glPopClientAttrib();
}

bool Image::GaussianBlur(float sigma, Image& dest) const {
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
            Vector4 sum = Vector4(0);
            int left = x - half_matrix_size;
            int top =  y - half_matrix_size;

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

                    Vector4 pixel( GetPixel(posX, posY) );
                    pixel *= weights[ i + matrix_size*j ];
                    sum += pixel;
                }
            }

            dest.SetPixel( x, y, sum );
        }
    }

    delete [] weights;
    return true;
}

void Image::RenderGL() {
    for(int y=0; y<height_; ++y)
        RenderScanlineGL(y);
}

void Image::RenderScanlineGL(int y) {
    glRasterPos2f(-1, -1 + 2*y / float(height_));

	// not using alpha, but using vector4 so just pretend we are
	// it won't affect the output colors
    glDrawPixels(width_, 1, GL_RGBA, GL_FLOAT, &pixels_[y*width_]);
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

	for(int y=0; y<height_; y++) {
		int yOffset = y*width_;
		for(int x=0; x<width_; x++) {
			Vector4* p = pixels_ + yOffset + x;
			math::Tuple3<uint8>* d = data + yOffset + x;

			d->x = base::FloatToByte( p->x );
			d->y = base::FloatToByte( p->y );
			d->z = base::FloatToByte( p->z );
			// Ignore 4th component when dealing with simple color 3tuples
		}
	}

    WritePPM(filename, static_cast<uint8*>( &((*data).x) ), width_, height_);

	delete[] data;
}

void Image::WritePPM(const char* filename, uint8* data, int width, int height) {
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

void Image::LoadPFM(const char* filename) {
	DeleteBuffer();
	pixels_ = tools::PFMLoader::ReadPFMImage( filename, &width_, &height_ );

	int numpixels = width_ * height_;
	float* pixelMagnitudes = new float[ numpixels ];
	float avgRGB = 0.0f;

	// Find the "average" color of the entire image by looping over all pixels and doing some stuff
	for( int i=0; i<numpixels; ++i ) {
		Vector4& pixel = pixels_[i];
		pixelMagnitudes[i] = pow( (pixel.x + pixel.y + pixel.z), options::global::hdr_bloom_power );
		avgRGB += pixelMagnitudes[i];
	}
	avgRGB /= numpixels;

	// Now that we have the average value, assign bloom component based on difference
	for( int i=0; i<numpixels; ++i ) {
		float magDiff = pixelMagnitudes[i] - avgRGB;
		pixels_[i].w = std::max( 0.0f, magDiff );
	}

	delete [] pixelMagnitudes;
}

const Image& Image::operator+=(const Image& i) {
	int width = std::min( width_, i.width_ );
	int height = std::min( height_, i.height_ );

	for( int col=0; col<width; ++col )
		for( int row=0; row<height; ++row)
			this->GetPixel(col, row) += i.GetPixel(col, row);

	return *this;
}


Image* Image::CreateAlphaImage() {
	int numpixels = width_ * height_;
	Image* alpha = new Image();
	alpha->Resize( width_, height_ );

	for( int i=0; i<numpixels; ++i ) {
		Vector4& srcpixel  = pixels_[i];
		Vector4& destpixel = alpha->pixels_[i];

		destpixel.x = destpixel.y = destpixel.z = destpixel.w = srcpixel.w;
	}

	return alpha;
}

Image* Image::CreateAlphaMixImage() {
	int numpixels = width_ * height_;
	Image* alpha = new Image();
	alpha->Resize( width_, height_ );

	for( int i=0; i<numpixels; ++i ) {
		Vector4& srcpixel  = pixels_[i];
		Vector4& destpixel = alpha->pixels_[i];

		destpixel.x = srcpixel.x * srcpixel.w;
		destpixel.y = srcpixel.y * srcpixel.w;
		destpixel.z = srcpixel.z * srcpixel.w;
		destpixel.w = srcpixel.w * srcpixel.w;
	}

	return alpha;
}

} // namespace rawray
