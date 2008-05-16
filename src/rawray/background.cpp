/////////////////////////////////////////////////////////////////////////////
// background.cpp
//
/////////////////////////////////////////////////////////////////////////////
#include "background.h"
#include "tools/pfm_loader.h"

namespace rawray {

const Vector3& Background::GetBGColor( const Vector3& d ) {
	UNREFERENCED_PARAMETER( d );
	return bgColor_;
}

const Vector3& Background::GetHDRColor( const Vector3& d ) {
	// Calculate (u,v) coordinates 
	// u = Dx*r
	// v = Dy*r
	// r = (1/pi)*acos(Dz)/sqrt( Dx*Dx + Dy*Dy )
	const float r = math::INV_PI * acos(d.z) / sqrtf( d.x*d.x + d.y*d.y );
	return hdr_.GetUVPixel( d.x*r, d.y*r );
}

void Background::LoadPFM( const char* filename ) {
	std::cout << "Loading HDR File: '" << filename << "'\n";
	hdr_.LoadPFM(filename);

	// Use the HDR function for getting colors now
	colorGetter_ = &Background::GetHDRColor;
}

} // namespace rawray
