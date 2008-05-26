/////////////////////////////////////////////////////////////////////////////
// reflective.cpp
//
/////////////////////////////////////////////////////////////////////////////
#include "reflective.h"
#include "math/vector3.h"
#include "light.h"
#include "background.h"

namespace rawray {

void Reflective::ShadeLight(HitInfo& hit, Scene& scene, const Light& light, float intensity, Vector4& shadedColor) const {
	UNREFERENCED_PARAMETER(intensity);
	UNREFERENCED_PARAMETER(light);

	if( hit.ior_bounce < options::global::max_ior_bounce ) {

		Vector3 e = hit.point - hit.eyeRay.origin;
		e.Normalize();

		Vector3 reflect = e;
		reflect += -2 * e.Dot( hit.normal ) * hit.normal;
	
		HitInfo reflectiveHit;
		reflectiveHit.ior_bounce = hit.ior_bounce + 1;
		reflectiveHit.diffuse_bounce = hit.diffuse_bounce;
		reflectiveHit.eyeRay = Ray( hit.point + math::EPSILON * reflect, reflect );
		reflectiveHit.ior = hit.ior;
		reflectiveHit.distance = MAX_DISTANCE;

		if( scene.Intersect( reflectiveHit ) )
			shadedColor += reflectiveHit.material->Shade(reflectiveHit, scene);
		else
			shadedColor += scene.GetBackground().GetColor( reflectiveHit.eyeRay.direction );
	}
}

} // namespace rawray
