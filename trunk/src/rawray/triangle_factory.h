/////////////////////////////////////////////////////////////////////////////
// Class : triangle_factory.h
// 
/////////////////////////////////////////////////////////////////////////////
#ifndef RAWRAY_RAWRAY_TRIANGLE_FACTORY_H
#define RAWRAY_RAWRAY_TRIANGLE_FACTORY_H
#include "stdafx.h"
#include "triangle.h"
#include "triangle_mesh.h"
#include "triangle_barycentric.h"
#include "triangle_barycentric_projection.h"
#include "triangle_moller.h"
#include "triangle_plucker.h"


/////////////////////////////////////////////////////////////////////////////
namespace rawray {

class Material;
class Triangle;

namespace TriangleFactory {

Triangle* NewTriangle(TriangleMesh& mesh, int index, const Material* material);

} // namespace rawray::TriangleFactory


} // namespace rawray
/////////////////////////////////////////////////////////////////////////////

#endif // RAWRAY_RAWRAY_TRIANGLE_H
