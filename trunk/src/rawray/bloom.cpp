/////////////////////////////////////////////////////////////////////////////
// bloom.cpp
//
/////////////////////////////////////////////////////////////////////////////
#include "bloom.h"

namespace rawray {

void Bloom::Process(Image& image) {
	// Create a copy of the image where the colors are multiplied by the 4th component
	Image* bloom = image.CreateAlphaMixImage();

	bloom->WritePPM("alpha_mix.ppm");

	// Gaussian blur this mixed image and overlay it with the original
	bloom->GaussianBlur( 4.0f );
	bloom->WritePPM("alpha_mix_blur.ppm");

	image += *bloom;
	delete bloom;
}

} // namespace rawray
