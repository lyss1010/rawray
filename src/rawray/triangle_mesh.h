/////////////////////////////////////////////////////////////////////////////
// Class : triangle_mesh.h
// 
/////////////////////////////////////////////////////////////////////////////
#ifndef RAWRAY_RAWRAY_TRIANGLE_MESH_H
#define RAWRAY_RAWRAY_TRIANGLE_MESH_H
#include "stdafx.h"
#include "math/matrix4x4.h"
#include <stdio.h>

/////////////////////////////////////////////////////////////////////////////
namespace rawray {

class DllExport TriangleMesh
{
public:
    TriangleMesh() 
        : normals_(NULL), vertices_(NULL), texCoords_(NULL),
        normalIndices_(NULL), vertexIndices_(NULL), texCoordIndices_(NULL),
        numTriangles_(0) { }

    TriangleMesh(TriangleMesh* m)
        : normals_(m->normals_), vertices_(m->vertices_), texCoords_(m->texCoords_),
        normalIndices_(m->normalIndices_), vertexIndices_(m->vertexIndices_), texCoordIndices_(m->texCoordIndices_),
        numTriangles_(0) { }

    ~TriangleMesh();

    Vector3* GetNormals() { return normals_; }
    Vector3* GetVertices() { return vertices_; }
    Vector2* GetTexCoords() { return texCoords_; }
    Tuple3I* GetNormalIndices() { return normalIndices_; }
    Tuple3I* GetVertexIndices() { return vertexIndices_; }
    Tuple3I* GetTexCoordIndices() { return texCoordIndices_; }
    int GetNumTriangles() const { return numTriangles_; }

    bool LoadOBJ(const char* filename, const Matrix4x4& ctm = Matrix4x4());

protected:
    void LoadOBJFile(FILE* fp, const Matrix4x4& ctm);
    void GetIndices(char* word, int* vIndex, int* tIndex, int* nIndex);

    Vector3* normals_;
    Vector3* vertices_;
    Vector2* texCoords_;

    Tuple3I* normalIndices_;
    Tuple3I* vertexIndices_;
    Tuple3I* texCoordIndices_;
    int numTriangles_;

}; // class TriangleMesh


} // namespace rawray
/////////////////////////////////////////////////////////////////////////////

#endif // RAWRAY_RAWRAY_TRIANGLE_MESH_H
