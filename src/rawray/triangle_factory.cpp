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

Triangle* NewTriangle(TriangleMesh* mesh, int index, Material* material) {
	switch( rawray::options::global::triangle_intersection_algorithm ) {
	case rawray::options::BARYCENTRIC:
        return dynamic_cast<Triangle*>(
            TriangleBarycentric::newTriangle(mesh, index, material) );

	case rawray::options::BARYCENTRIC_PROJECTION:
        return dynamic_cast<Triangle*>(
            TriangleBarycentricProjection::newTriangle(mesh, index, material) );

	case rawray::options::PLUCKER:
		return dynamic_cast<Triangle*>(
            TrianglePlucker::newTriangle(mesh, index, material) );

	default:
	case rawray::options::MOLLER:
        return dynamic_cast<Triangle*>(
            TriangleMoller::newTriangle(mesh, index, material) );
	}
}

void DeleteTriangle(Triangle* t) {
    _aligned_free(t);
}

} // namespace rawray::TriangleFactory
} // namespace rawray
