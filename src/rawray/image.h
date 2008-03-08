/////////////////////////////////////////////////////////////////////////////
// Class : image.h
//
/////////////////////////////////////////////////////////////////////////////
#ifndef RAWRAY_RAWRAY_IMAGE_H
#define RAWRAY_RAWRAY_IMAGE_H
#include "stdafx.h"
#include "tuple3.h"
#include "vector3.h"

/////////////////////////////////////////////////////////////////////////////
namespace rawray {

typedef math::Tuple3<uint8> Pixel;

class DllExport Image
{
public:
    Image();
    explicit Image(const Image& i); // Copies entire image, does not link to same data
    ~Image();

    int Resize(uint32 width, uint32 height);
    void SetPixel(uint32 x, uint32 y, const math::Vector3& color);
    void SetPixel(uint32 x, uint32 y, const Pixel& color);

    void Clear(const math::Vector3& color);
    void Clear(const Pixel& color);
    
    void RenderGL();

    Pixel* GetPixels() { return pixels_; }
    uint32 GetWidth() const { return width_; }
    uint32 GetHeight() const { return height_; }

private:
    void RenderScanlineGL(uint32 y);

    Pixel* pixels_;
    uint32 width_;
    uint32 height_;

}; // class Image

} // namespace rawray
/////////////////////////////////////////////////////////////////////////////


#endif // RAWRAY_RAWRAY_IMAGE_H
