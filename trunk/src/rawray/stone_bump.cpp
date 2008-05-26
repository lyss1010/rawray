/////////////////////////////////////////////////////////////////////////////
// stone_bump.cpp
//
/////////////////////////////////////////////////////////////////////////////
#include "stone_bump.h"
#include "math/vector3.h"
#include "light.h"
#include "stats.h"
#include "tools/worley.h"
#include "tools/perlin.h"

namespace rawray {

void StoneBump::ShadeLight(HitInfo& hit, Scene& scene, const Light& light, float intensity, Vector4& shadedColor) const {
	UNREFERENCED_PARAMETER(scene);
	UNREFERENCED_PARAMETER(shadedColor);
	UNREFERENCED_PARAMETER(intensity);
	UNREFERENCED_PARAMETER(light);

	// NOTE: Does not change color, will effect any further materials which use the hit.normal
	static const int MAX_ORDER = 3;

	unsigned long id;
	float at[3] = { hit.point.x, hit.point.y, hit.point.z };
	float f[MAX_ORDER];
	float delta[MAX_ORDER][3];

	tools::Worley::Noise3D( at, MAX_ORDER, f, delta, &id );

	hit.normal *= 1.0f - amplitude_ * sqrtf(f[2] - f[1]);
}

} // namespace rawray
