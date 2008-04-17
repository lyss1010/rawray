/////////////////////////////////////////////////////////////////////////////
// triangle_plucker.cpp
//
/////////////////////////////////////////////////////////////////////////////
#include "triangle_factory.h"
#include "triangle.h"
#include "triangle_barycentric.h"
#include "triangle_barycentric_projection.h"
#include "triangle_moller.h"
#include "triangle_plucker.h"

namespace rawray {
namespace TriangleFactory {

Triangle* NewTriangle(TriangleMesh& mesh, uint32 index, const Material* material) {
	switch( rawray::options::global::triangle_intersection_algorithm ) {
	case rawray::options::BARYCENTRIC:
		return new TriangleBarycentric(mesh, index, material);

	case rawray::options::BARYCENTRIC_PROJECTION:
		return new TriangleBarycentricProjection(mesh, index, material);

	case rawray::options::MOLLER:
		return new TriangleMoller(mesh, index, material);

	default:
	case rawray::options::PLUCKER:
		return new TrianglePlucker(mesh, index, material);
	}
}

} // namespace rawray::TriangleFactory
} // namespace rawray
