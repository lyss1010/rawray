/////////////////////////////////////////////////////////////////////////////
// Class : background.h
//
/////////////////////////////////////////////////////////////////////////////
#ifndef RAWRAY_RAWRAY_BACKGROUND_H
#define RAWRAY_RAWRAY_BACKGROUND_H
#include "stdafx.h"
#include "math/vector3.h"
#include "math/vector4.h"
#include "image.h"

/////////////////////////////////////////////////////////////////////////////
namespace rawray {

// Function to get a background color from a missed ray
class Background;
typedef const Vector4&(Background::*ColorGetterFunc)(const Vector3&);

class DllExport Background {
public:
	Background() : colorGetter_(&Background::GetBGColor) { }
	~Background() { }

	const Vector4& GetColor( const Vector3& ray ) { return (this->*colorGetter_)(ray); }
	void SetBGColor( const Vector4& color ) { bgColor_ = color; }
	void LoadPFM( const char* filename );

private:
	ColorGetterFunc colorGetter_;
	Vector4 bgColor_;
	Image hdr_;

	const Vector4& GetBGColor( const Vector3& d );
	const Vector4& GetHDRColor( const Vector3& d );

	DISALLOW_COPY_CONSTRUCTORS(Background);

}; // class Background

} // namespace rawray
/////////////////////////////////////////////////////////////////////////////


#endif // RAWRAY_RAWRAY_BACKGROUND_H
