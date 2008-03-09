/////////////////////////////////////////////////////////////////////////////
// Class : triangle_mesh.h
// 
/////////////////////////////////////////////////////////////////////////////
#ifndef RAWRAY_RAWRAY_TRIANGLE_MESH_H
#define RAWRAY_RAWRAY_TRIANGLE_MESH_H
#include "stdafx.h"


/////////////////////////////////////////////////////////////////////////////
namespace rawray {

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

    Vector3* GetNormals() { return normals_; }
    Vector3* GetVertices() { return vertices_; }
    Vector2* GetTexCoords() { return texCoords_; }
    Tuple3I* GetNormalIndices() { return normalIndices_; }
    Tuple3I* GetVertexIndices() { return vertexIndices_; }
    Tuple3I* GetTexCoordIndices() { return texCoordIndices_; }
    uint32 GetNumTriangles() const { return numTriangles; }

protected:
    Vector3* normals_;
    Vector3* vertices_;
    Vector2* texCoords_;

    Tuple3I* normalIndices_;
    Tuple3I* vertexIndices_;
    Tuple3I* texCoordIndices_;
    uint32 numTriangles;

}; // class TriangleMesh


} // namespace rawray
/////////////////////////////////////////////////////////////////////////////

#endif // RAWRAY_RAWRAY_TRIANGLE_MESH_H
