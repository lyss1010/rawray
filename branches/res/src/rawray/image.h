/////////////////////////////////////////////////////////////////////////////
// Class : image.h
//
/////////////////////////////////////////////////////////////////////////////
#ifndef RAWRAY_RAWRAY_IMAGE_H
#define RAWRAY_RAWRAY_IMAGE_H
#include "stdafx.h"
#include "math/tuple3.h"
#include "math/vector3.h"
#include "time.h"

/////////////////////////////////////////////////////////////////////////////
namespace rawray {

typedef math::Vector3			Vector3;

class DllExport Image
{
public:
    Image();
    explicit Image(const Image& i); // Copies entire image, does not link to same data
    ~Image();

    int Resize(uint32 width, uint32 height);
    void SetPixel(uint32 x, uint32 y, const Vector3& color);
	void SetPixel(uint32 x, uint32 y, const math::Tuple3<uint8>& color);

    void Clear(const Vector3& color);
    void Clear(const math::Tuple3<uint8>& color);
    void ScreenShot();
    bool GaussianBlur(float sigma);
    
    void RenderGL();
    void RenderScanlineGL(uint32 y);

	void WritePPM();
    void WritePPM(clock_t rendertime);
    void WritePPM(const char* filename);

	Vector3& GetPixel(int x, int y) { return pixels_[y*width_ + x]; }
    Vector3* GetPixels() { return pixels_; }
    uint32  GetWidth() const { return width_; }
    uint32  GetHeight() const { return height_; }

private:
    Vector3* pixels_;
    uint32 width_;
    uint32 height_;

    void WritePPM(const char* filename, uint8* data, uint32 width, uint32 height);


}; // class Image

} // namespace rawray
/////////////////////////////////////////////////////////////////////////////


#endif // RAWRAY_RAWRAY_IMAGE_H