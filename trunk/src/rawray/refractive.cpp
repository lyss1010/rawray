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
	UNREFERENCED_PARAMETER(scene);
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

	if( hit.bounce < options::global::max_bounce ) {
		HitInfo refractiveHit;
		refractiveHit.bounce = hit.bounce + 1;
		refractiveHit.eyeRay = Ray( hit.point + math::EPSILON * refract,
									refract );

		refractiveHit.ior = ior_;
		refractiveHit.distance = MAX_DISTANCE;

		if( scene.Intersect( refractiveHit ) )
			shadedColor += hit.material->Shade(refractiveHit, scene);
		else
			shadedColor += scene.GetBackground().GetColor( refractiveHit.eyeRay.direction );
	}
}

} // namespace rawray
