/////////////////////////////////////////////////////////////////////////////
// Class : triangle.h
// 
/////////////////////////////////////////////////////////////////////////////
#ifndef RAWRAY_GEOMETRY_TRIANGLE_H
#define RAWRAY_GEOMETRY_TRIANGLE_H
#include "stdafx.h"
#include "object.h"
#include "triangle_mesh.h"

/////////////////////////////////////////////////////////////////////////////
namespace geometry {

class DllExport Triangle : public Object
{
public:
    Triangle(Triangle& t) : mesh_(t.mesh_), index_(t.index_) { }

    Triangle(TriangleMesh& mesh, uint32 index)
            : mesh_(mesh), index_(index) { }

    virtual ~Triangle();

    TriangleMesh& GetMesh() { return mesh_; }
    uint32 GetIndex() const { return index_; }

    void SetMesh(TriangleMesh& mesh) { mesh_=mesh; }
    void SetIndex(uint32 index) { index_=index; }

private:
    TriangleMesh& mesh_;
    uint32 index_;

}; // class Triangle


} // namespace geometry
/////////////////////////////////////////////////////////////////////////////

#endif // RAWRAY_GEOMETRY_TRIANGLE_H
