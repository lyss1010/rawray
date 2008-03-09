/////////////////////////////////////////////////////////////////////////////
// triangle_mesh.cpp
//
/////////////////////////////////////////////////////////////////////////////
#include "triangle_mesh.h"
#include "math/vector2.h"
#include "math/vector3.h"
#include "math/tuple3.h"

namespace rawray {

    TriangleMesh::~TriangleMesh() {
        SAFE_DELETE_ARRAY( normals_ );
        SAFE_DELETE_ARRAY( vertices_ );
        SAFE_DELETE_ARRAY( texCoords_ );
        SAFE_DELETE_ARRAY( normalIndices_ );
        SAFE_DELETE_ARRAY( vertexIndices_ );
        SAFE_DELETE_ARRAY( texCoordIndices_ );
    }

} // namespace rawray
