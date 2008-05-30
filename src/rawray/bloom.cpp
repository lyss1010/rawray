/////////////////////////////////////////////////////////////////////////////
// bloom.cpp
//
/////////////////////////////////////////////////////////////////////////////
#include "bloom.h"

namespace rawray {

void Bloom::Process(Image& image) {
	// Create a copy of the image where the colors are multiplied by the 4th component
	Image* alphaMix = image.CreateAlphaMixImage();
	Image bloom; bloom.Resize( image.GetWidth(), image.GetHeight() );

	// Gaussian blur this mixed image and overlay it with the original
	alphaMix->GaussianBlur( options::global::hdr_bloom_radius, bloom );
	delete alphaMix;

	image += bloom;
}

} // namespace rawray
