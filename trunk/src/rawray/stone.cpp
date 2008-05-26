/////////////////////////////////////////////////////////////////////////////
// stone.cpp
//
/////////////////////////////////////////////////////////////////////////////
#include "stone.h"
#include "math/vector3.h"
#include "light.h"
#include "stats.h"
#include "tools/worley.h"
#include "tools/perlin.h"

namespace rawray {

void Stone::ShadeLight(HitInfo& hit, Scene& scene, const Light& light, float intensity, Vector4& shadedColor) const {
	UNREFERENCED_PARAMETER(scene);

	static const int MAX_ORDER = 3;

	unsigned long id;
	float at[3] = { hit.point.x, hit.point.y, hit.point.z };
	float f[MAX_ORDER];
	float delta[MAX_ORDER][3];

	tools::Worley::Noise3D( at, MAX_ORDER, f, delta, &id );
	const float coord = sqrtf(f[2] - f[1]);
	//float invCoord = 1.0f - coord;
	//invCoord *= invCoord; // 2nd power
	//invCoord *= invCoord; // 4th power

	Vector4 color( sqrtf(coord) );
	color *= colorA_;

	//Vector3 invColor( invCoord );
	//invColor *= colorB_;

	color *= 1.0f - 0.1f * tools::Perlin::Noise( 0.5f*hit.point.x, 0.5f*hit.point.y, 0.5f*hit.point.z );

	//color += invColor;
	
	

	// Compute diffuse shading with this color
	color *= light.GetColor();

	Vector3 direction = light.GetPosition() - hit.point;
	direction.Normalize();
	intensity *= hit.normal.Dot(direction);

	if( intensity > 0.0f ) {
		color *= intensity;
		shadedColor += color;
	}
}

} // namespace rawray
