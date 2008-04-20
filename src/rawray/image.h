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

    int Resize(int width, int height);
    void SetPixel(int x, int y, const Vector3& color);
	void SetPixel(int x, int y, const math::Tuple3<uint8>& color);

    void Clear(const Vector3& color);
    void Clear(const math::Tuple3<uint8>& color);
    void ScreenShot();
    bool GaussianBlur(float sigma);
    
    void RenderGL();
    void RenderScanlineGL(int y);

	void WritePPM();
    void WritePPM(clock_t rendertime);
    void WritePPM(const char* filename);

	Vector3& GetPixel(int x, int y) { return pixels_[y*width_ + x]; }
    Vector3* GetPixels() { return pixels_; }
    int GetWidth() const { return width_; }
    int GetHeight() const { return height_; }

private:
    Vector3* pixels_;
    int width_;
    int height_;

    void WritePPM(const char* filename, uint8* data, int width, int height);


}; // class Image

} // namespace rawray
/////////////////////////////////////////////////////////////////////////////


#endif // RAWRAY_RAWRAY_IMAGE_H
