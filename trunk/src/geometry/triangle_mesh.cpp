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
        delete [] normals_;
        delete [] vertices_;
        delete [] texCoords_;
        delete [] normalIndices_;
        delete [] vertexIndices_;
        delete [] texCoordIndices_;
    }

} // namespace geometry
