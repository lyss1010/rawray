/////////////////////////////////////////////////////////////////////////////
// Class : triangle_mesh.h
// 
/////////////////////////////////////////////////////////////////////////////
#ifndef RAWRAY_GEOMETRY_TRIANGLE_MESH_H
#define RAWRAY_GEOMETRY_TRIANGLE_MESH_H
#include "stdafx.h"

// Forward Declerations
namespace math {
    class Vector2;
    class Vector3;

    template <class T>
    class Tuple3;
}


/////////////////////////////////////////////////////////////////////////////
namespace geometry {

class DllExport TriangleMesh
{
public:
    TriangleMesh() 
        : normals_(NULL), vertices_(NULL), texCoords_(NULL),
        normalIndices_(NULL), vertexIndices_(NULL), texCoordIndices_(NULL) { }

    TriangleMesh(TriangleMesh& m)
        : normals_(m.normals_), vertices_(m.vertices_), texCoords_(m.texCoords_),
        normalIndices_(m.normalIndices_), vertexIndices_(m.vertexIndices_), texCoordIndices_(m.texCoordIndices_) { }

    ~TriangleMesh();

    math::Vector3* GetNormals() { return normals_; }
    math::Vector3* GetVertices() { return vertices_; }
    math::Vector2* GetTexCoords() { return texCoords_; }
    math::Tuple3<uint32>* GetNormalIndices() { return normalIndices_; }
    math::Tuple3<uint32>* GetVertexIndices() { return vertexIndices_; }
    math::Tuple3<uint32>* GetTexCoordIndices() { return texCoordIndices_; }
    uint32 GetNumTriangles() const { return numTriangles; }


private:
    math::Vector3* normals_;
    math::Vector3* vertices_;
    math::Vector2* texCoords_;

    math::Tuple3<uint32>* normalIndices_;
    math::Tuple3<uint32>* vertexIndices_;
    math::Tuple3<uint32>* texCoordIndices_;
    uint32 numTriangles;

}; // class TriangleMesh


} // namespace geometry
/////////////////////////////////////////////////////////////////////////////

#endif // RAWRAY_GEOMETRY_TRIANGLE_MESH_H
