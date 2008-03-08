/////////////////////////////////////////////////////////////////////////////
// triangle_mesh.cpp
//
/////////////////////////////////////////////////////////////////////////////
#include "triangle_mesh.h"
#include "vector2.h"
#include "vector3.h"
#include "tuple3.h"

namespace geometry {

    TriangleMesh::~TriangleMesh() {
        SAFE_DELETE_ARRAY( normals_ );
        SAFE_DELETE_ARRAY( vertices_ );
        SAFE_DELETE_ARRAY( texCoords_ );
        SAFE_DELETE_ARRAY( normalIndices_ );
        SAFE_DELETE_ARRAY( vertexIndices_ );
        SAFE_DELETE_ARRAY( texCoordIndices_ );
    }

} // namespace geometry
