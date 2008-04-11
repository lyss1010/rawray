/////////////////////////////////////////////////////////////////////////////
// Class : matrix4x4.h
// 
// 4 Element floating point vector
// Based off of Miro code from UCSD.CSE168.SP08
/////////////////////////////////////////////////////////////////////////////
#ifndef RAWRAY_MATH_MATRIX4X4_H
#define RAWRAY_MATH_MATRIX4X4_H
#include "stdafx.h"


/////////////////////////////////////////////////////////////////////////////
// Includes
/////////////////////////////////////////////////////////////////////////////
#include "vector3.h"
#include "vector4.h"


/////////////////////////////////////////////////////////////////////////////
namespace math {

class DllExport Matrix4x4
{
public: 
    //      u    v    s    t
    float m11, m12, m13, m14,
          m21, m22, m23, m24,
          m31, m32, m33, m34,
          m41, m42, m43, m44;

    Matrix4x4() { SetIdentity(); }

    Matrix4x4(const Vector4& u, const Vector4& v, 
              const Vector4& s, const Vector4& t);
    
    Matrix4x4(float f11, float f12, float f13, float f14,
              float f21, float f22, float f23, float f24,
              float f31, float f32, float f33, float f34,
              float f41, float f42, float f43, float f44);

    void SetIdentity();

    void Set(const Matrix4x4& m);

    void Set(const Vector4& u, const Vector4& v,
                    const Vector4& s, const Vector4& t);

    void Set(float f11, float f12, float f13, float f14,
                    float f21, float f22, float f23, float f24,
                    float f31, float f32, float f33, float f34,
                    float f41, float f42, float f43, float f44);

    void SetColumn1(float f1, float f2, float f3, float f4);
    void SetColumn2(float f1, float f2, float f3, float f4);
    void SetColumn3(float f1, float f2, float f3, float f4);
    void SetColumn4(float f1, float f2, float f3, float f4);
    void SetColumn1(const Vector4& v);
    void SetColumn2(const Vector4& v);
    void SetColumn3(const Vector4& v);
    void SetColumn4(const Vector4& v);

    void SetRow1(float f1, float f2, float f3, float f4);
    void SetRow2(float f1, float f2, float f3, float f4);
    void SetRow3(float f1, float f2, float f3, float f4);
    void SetRow4(float f1, float f2, float f3, float f4);
    void SetRow1(const Vector4& v);
    void SetRow2(const Vector4& v);
    void SetRow3(const Vector4& v);
    void SetRow4(const Vector4& v);

    inline Vector4 CopyColumn1() const { return Vector4(m11,m21,m31,m41); }
    inline Vector4 CopyColumn2() const { return Vector4(m12,m22,m32,m42); }
    inline Vector4 CopyColumn3() const { return Vector4(m13,m23,m33,m43); }
    inline Vector4 CopyColumn4() const { return Vector4(m14,m24,m34,m44); }

    inline Vector4 CopyRow1() const { return Vector4(m11,m12,m13,m14); }
    inline Vector4 CopyRow2() const { return Vector4(m21,m22,m23,m24); }
    inline Vector4 CopyRow3() const { return Vector4(m31,m32,m33,m34); }
    inline Vector4 CopyRow4() const { return Vector4(m41,m42,m43,m44); }

    Matrix4x4& operator*=(float f);
    Matrix4x4& operator/=(float f);
    
    Matrix4x4& operator+=(const Matrix4x4& m);
    Matrix4x4& operator-=(const Matrix4x4& m);
    Matrix4x4& operator*=(const Matrix4x4& m);

    Matrix4x4& Invert();
    Matrix4x4& Transpose();

}; // class Matrix4x4


} // namespace math
/////////////////////////////////////////////////////////////////////////////

DllExport math::Matrix4x4 operator*(const math::Matrix4x4& a, const math::Matrix4x4& b);
DllExport math::Matrix4x4 operator*(const math::Matrix4x4& m, float f);
DllExport math::Matrix4x4 operator*(float f, const math::Matrix4x4& m);
DllExport math::Matrix4x4 operator/(const math::Matrix4x4& m, float f);
DllExport math::Vector4 operator*(const math::Matrix4x4& m, const math::Vector4& v);
DllExport math::Vector3 operator*(const math::Matrix4x4& m, const math::Vector3& v);
DllExport std::ostream& operator<<(std::ostream& out, const math::Matrix4x4& m);


#endif // RAWRAY_MATH_MATRIX4X4_H