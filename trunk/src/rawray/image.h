/////////////////////////////////////////////////////////////////////////////
// Class : image.h
//
/////////////////////////////////////////////////////////////////////////////
#ifndef RAWRAY_RAWRAY_IMAGE_H
#define RAWRAY_RAWRAY_IMAGE_H
#include "stdafx.h"
#include "math/tuple3.h"
#include "math/vector4.h"
#include "time.h"

/////////////////////////////////////////////////////////////////////////////
namespace rawray {

typedef math::Vector4			Vector4;

class DllExport Image
{
public:
    Image();
    ~Image();

    int Resize(int width, int height);
	void SetPixel(int x, int y, const Vector4& color);
	void SetPixel(int x, int y, const math::Tuple3<uint8>& color);

	void Clear(const Vector4& color);
    void Clear(const math::Tuple3<uint8>& color);
	void Clear(const Vector4& color, int x, int y, int width, int height);
	void Clear(const math::Tuple3<uint8>& color, int x, int y, int width, int height);
    void ScreenShot();
    bool GaussianBlur(float sigma);
	Image* CreateAlphaImage();
	Image* CreateAlphaMixImage();
    
    void RenderGL();
    void RenderScanlineGL(int y);

	void WritePPM();
    void WritePPM(clock_t rendertime);
    void WritePPM(const char* filename);
	void LoadPFM(const char* filename);
	
	Vector4& Get0UVPixel(float u, float v); // u,v are [ 0,1]
	Vector4& GetUVPixel(float u, float v);  // u,v are [-1,1]
	Vector4& GetBoundPixel(int x, int y);
	Vector4& GetPixel(int x, int y)				{ return pixels_[y*width_ + x]; }
	const Vector4& GetPixel(int x, int y) const { return pixels_[y*width_ + x]; }
    Vector4* GetPixels() { return pixels_; }
    int GetWidth() const { return width_; }
    int GetHeight() const { return height_; }

	const Image& operator+=(const Image& i);

private:
    Vector4* pixels_;
    int width_;
    int height_;

    void WritePPM(const char* filename, uint8* data, int width, int height);
    void DeleteBuffer();

}; // class Image

} // namespace rawray
/////////////////////////////////////////////////////////////////////////////


#endif // RAWRAY_RAWRAY_IMAGE_H
