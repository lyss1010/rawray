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

bool TriangleMesh::LoadOBJ(const char* filename, const Matrix4x4& ctm) {
    FILE* fp = NULL;
    fp = fopen( filename, "rb" );

    if( !fp ) {
        return false;
    }

    LoadOBJFile(fp, ctm);
    fclose(fp);

    return true;
}

void TriangleMesh::LoadOBJFile(FILE* fp, const Matrix4x4& ctm) {
    int nv=0, nt=0, nn=0, nf=0;
    char line[81];

    while (fgets(line, 80, fp) != 0) {
        if ( line[0] == 'v' ) {
            if (line[1] == 'n' )
                nn++;
            else if (line[1] == 't' )
                nt++;
            else
                nv++;
        } else if ( line[0] == 'f' )
            nf++;
    }

    fseek(fp, 0, 0);

    normals_ = new Vector3[ std::max(nv, nf) ];
    vertices_ = new Vector3[ nv ];

    if (nt) {
        texCoords_ = new Vector2[ nt ];
        texCoordIndices_ = new Tuple3I[ nf ];
    }

    normalIndices_ = new Tuple3I[nf]; // always make normals
    vertexIndices_ = new Tuple3I[nf]; // always have vertices

    numTriangles_ = 0;
    int nvertices = 0;
    int nnormals = 0;
    int ntextures = 0;

    Matrix4x4 nctm = ctm;
    nctm.Invert();
    nctm.Transpose();
    nctm.Invert();

    while (fgets(line, 80, fp) != 0)
    {
        if (line[0] == 'v')
        {
            if (line[1] == 'n')
            {
                float x, y, z;
                sscanf(&line[2], "%f %f %f\n", &x, &y, &z);
                Vector3 n(x, y, z);
                normals_[nnormals] = nctm*n;
                normals_[nnormals].Normalize();
                nnormals++;
            }
            else if (line[1] == 't')
            {
                float x, y;
                sscanf(&line[2], "%f %f\n", &x, &y);
                texCoords_[ntextures].x = x;
                texCoords_[ntextures].y = y;
                ntextures++;
            }
            else
            {
                float x, y, z;
                sscanf(&line[1], "%f %f %f\n", &x, &y, &z);
                Vector3 v(x, y, z);
                vertices_[nvertices] = ctm*v;
                nvertices++;
            }
        }
        else if (line[0] == 'f')
        {
            char s1[32], s2[32], s3[32];
            int v, t, n;
            sscanf(&line[1], "%s %s %s\n", s1, s2, s3);

            GetIndices(s1, &v, &t, &n);
            vertexIndices_[numTriangles_].x = v-1;
            if (n)
                normalIndices_[numTriangles_].x = n-1;
            if (t)
                texCoordIndices_[numTriangles_].x = t-1;
            GetIndices(s2, &v, &t, &n);
            vertexIndices_[numTriangles_].y = v-1;
            if (n)
                normalIndices_[numTriangles_].y = n-1;
            if (t)
                texCoordIndices_[numTriangles_].y = t-1;
            GetIndices(s3, &v, &t, &n);
            vertexIndices_[numTriangles_].z = v-1;
            if (n)
                normalIndices_[numTriangles_].z = n-1;
            if (t)
                texCoordIndices_[numTriangles_].z = t-1;

            if (!n)
            {   // if no normal was supplied
                Vector3 e1 = vertices_[vertexIndices_[numTriangles_].y] -
                             vertices_[vertexIndices_[numTriangles_].x];
                Vector3 e2 = vertices_[vertexIndices_[numTriangles_].z] -
                             vertices_[vertexIndices_[numTriangles_].x];

                normals_[nn] = math::Cross(e1, e2);
                normalIndices_[nn].x = nn;
                normalIndices_[nn].y = nn;
                normalIndices_[nn].z = nn;
                nn++;
            }

            numTriangles_++;
        } //  else ignore line
    }
}

void TriangleMesh::GetIndices(char* word, int* vIndex, int* tIndex, int* nIndex) {
    char* null = " ";
    char* texture = null;
    char* normal = null;

    // Replace slashes with null characters and setup pointers to characters after these
    for (char* ptr = word; *ptr != '\0'; ++ptr) {
        if (*ptr == '/') {
            if (texture == null)
                texture = ptr + 1;
            else
                normal = ptr + 1;

            *ptr = '\0';
        }
    }

    *vIndex = atoi(word);
    *tIndex = atoi(texture);
    *nIndex = atoi(normal);
}

} // namespace rawray
