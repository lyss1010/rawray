/////////////////////////////////////////////////////////////////////////////
// refractive.cpp
//
/////////////////////////////////////////////////////////////////////////////
#include "refractive.h"
#include "math/vector3.h"
#include "light.h"
#include "background.h"

namespace rawray {

void Refractive::ShadeLight(HitInfo& hit, Scene& scene, const Light& light, float intensity, Vector3& shadedColor) const {
	UNREFERENCED_PARAMETER(intensity);
	UNREFERENCED_PARAMETER(light);

	Vector3 w = hit.eyeRay.origin - hit.point;
	w.Normalize();

	// incoming ior / outgoing material ior
	const float iorRatio = hit.ior / ior_;
	const float iorRatio2 = iorRatio * iorRatio;
	const float w_dot_n = w.Dot(hit.normal);
	const float w_dot_n2 = w_dot_n * w_dot_n;
	
	Vector3 refract = -iorRatio * (  w - w_dot_n * hit.normal );
	refract -= sqrtf( 1.0f - iorRatio2 * ( 1.0f - w_dot_n2 ) ) * hit.normal;

	if( hit.ior_bounce < options::global::max_ior_bounce ) {
		HitInfo refractiveHit;
		refractiveHit.ior_bounce = hit.ior_bounce + 1;
		refractiveHit.diffuse_bounce = hit.diffuse_bounce;
		refractiveHit.eyeRay = Ray( hit.point + math::EPSILON * refract, refract );
		refractiveHit.ior = ior_;
		refractiveHit.distance = MAX_DISTANCE;

		if( scene.Intersect( refractiveHit ) ) {
			Vector3 color = refractiveHit.material->Shade( refractiveHit, scene );
			shadedColor += color;
		}
		else
			shadedColor += scene.GetBackground().GetColor( refractiveHit.eyeRay.direction );
	}
}

} // namespace rawray
