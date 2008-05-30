/////////////////////////////////////////////////////////////////////////////
// indirect_diffuse.cpp
//
/////////////////////////////////////////////////////////////////////////////
#include "indirect_diffuse.h"
#include "math/vector3.h"
#include "light.h"
#include "stats.h"
#include "tools/random.h"

namespace rawray {

void IndirectDiffuse::ShadeLight(HitInfo& hit, Scene& scene, const Light& light, float intensity, Vector4& shadedColor) const {
	UNREFERENCED_PARAMETER(light);
	UNREFERENCED_PARAMETER(intensity);

	if( hit.diffuse_bounce < options::global::max_diffuse_bounce ) {

		// Get a random direction on a sphere
		Vector3 indirectRay = tools::random::RandomUnitCircleLoc();

		// Check if our direction is behind the normal, and flip it if so
		if( hit.normal.Dot( indirectRay ) < 0 )
			indirectRay *= -1;

		// Now calculate indirect lighting from this direction
		HitInfo indirectHit;
		indirectHit.ior_bounce = hit.ior_bounce;
		indirectHit.diffuse_bounce = hit.diffuse_bounce + 1;
		indirectHit.eyeRay = Ray( hit.point + math::EPSILON * indirectRay, indirectRay );
		indirectHit.ior = hit.ior;
		indirectHit.distance = MAX_DISTANCE;
		indirectHit.weight = hit.weight;

		if( scene.Intersect( indirectHit ) )
			shadedColor += weight_ * indirectHit.material->Shade(indirectHit, scene);
		else
			shadedColor += weight_ * scene.GetBackground().GetColor( indirectHit.eyeRay.direction );
	}
}

} // namespace rawray
