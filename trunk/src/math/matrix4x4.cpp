/////////////////////////////////////////////////////////////////////////////
// matrix4x4.cpp
//
/////////////////////////////////////////////////////////////////////////////
#include "matrix4x4.h"

namespace math {

Matrix4x4::Matrix4x4(const Vector4& u, 
                     const Vector4& v, 
                     const Vector4& s, 
                     const Vector4& t) :
    m11(u.x), m21(u.y), m31(u.z), m41(u.w),
    m12(v.x), m22(v.y), m32(v.z), m42(v.w),
    m13(s.x), m23(s.y), m33(s.z), m43(s.w),
    m14(t.x), m24(t.y), m34(t.z), m44(t.w) { }


Matrix4x4::Matrix4x4(float f11, float f12, float f13, float f14,
                     float f21, float f22, float f23, float f24,
                     float f31, float f32, float f33, float f34,
                     float f41, float f42, float f43, float f44) :
    m11(f11), m12(f12), m13(f13), m14(f14),
    m21(f21), m22(f22), m23(f23), m24(f24),
    m31(f31), m32(f32), m33(f33), m34(f34),
    m41(f41), m42(f42), m43(f43), m44(f44) { }


inline void Matrix4x4::SetIdentity() {
        m11 = m22 = m33 = m44 = 1.0;
        m12 = m13 = m14 = m21 = m23 = m24 = m31 = m32 = m34 = m41= m42 = m43 = 0.0;
    }

inline void Matrix4x4::Set(const Matrix4x4& m) {
    m11 = m.m11; m12 = m.m12; m13 = m.m13; m14 = m.m14;
    m21 = m.m21; m22 = m.m22; m23 = m.m23; m24 = m.m24;
    m31 = m.m31; m32 = m.m32; m33 = m.m33; m34 = m.m34;
    m41 = m.m41; m42 = m.m42; m43 = m.m43; m44 = m.m44;
}

inline void Matrix4x4::Set(float f11, float f12, float f13, float f14,
                           float f21, float f22, float f23, float f24,
                           float f31, float f32, float f33, float f34,
                           float f41, float f42, float f43, float f44) {
    m11 = f11; m12 = f12; m13 = f13; m14 = f14;
    m21 = f21; m22 = f22; m23 = f23; m24 = f24;
    m31 = f31; m32 = f32; m33 = f33; m34 = f34;
    m41 = f41; m42 = f42; m43 = f43; m44 = f44;
}

inline void Matrix4x4::SetColumn1(float f1, float f2, float f3, float f4) {
    m11 = f1; m21 = f2; m31 = f3; m41 = f4;
}

inline void Matrix4x4::SetColumn2(float f1, float f2, float f3, float f4) {
    m12 = f1; m22 = f2; m32 = f3; m42 = f4;
}

inline void Matrix4x4::SetColumn3(float f1, float f2, float f3, float f4) {
    m13 = f1; m23 = f2; m33 = f3; m43 = f4;
}

inline void Matrix4x4::SetColumn4(float f1, float f2, float f3, float f4) {
    m14 = f1; m24 = f2; m34 = f3; m44 = f4;
}

inline void Matrix4x4::SetColumn1(const Vector4& v) {
    m11 = v.x; m21 = v.y; m31 = v.z; m41 = v.w;
}

inline void Matrix4x4::SetColumn2(const Vector4& v) {
    m12 = v.x; m22 = v.y; m32 = v.z; m42 = v.w;
}

inline void Matrix4x4::SetColumn3(const Vector4& v) {
    m13 = v.x; m23 = v.y; m33 = v.z; m43 = v.w;
}

inline void Matrix4x4::SetColumn4(const Vector4& v) {
    m14 = v.x; m24 = v.y; m34 = v.z; m44 = v.w;
}

inline void Matrix4x4::SetRow1(float f1, float f2, float f3, float f4) {
    m11 = f1; m12 = f2; m13 = f3; m14 = f4;
}

inline void Matrix4x4::SetRow2(float f1, float f2, float f3, float f4) {
    m21 = f1; m22 = f2; m23 = f3; m24 = f4;
}

inline void Matrix4x4::SetRow3(float f1, float f2, float f3, float f4) {
    m31 = f1; m32 = f2; m33 = f3; m34 = f4;
}

inline void Matrix4x4::SetRow4(float f1, float f2, float f3, float f4) {
    m41 = f1; m42 = f2; m43 = f3; m44 = f4;
}

inline void Matrix4x4::SetRow1(const Vector4& v) {
    m11 = v.x; m12 = v.y; m13 = v.z; m14 = v.w;
}

inline void Matrix4x4::SetRow2(const Vector4& v) {
    m21 = v.x; m22 = v.y; m23 = v.z; m24 = v.w;
}

inline void Matrix4x4::SetRow3(const Vector4& v) {
    m31 = v.x; m32 = v.y; m33 = v.z; m34 = v.w;
}

inline void Matrix4x4::SetRow4(const Vector4& v) {
    m41 = v.x; m42 = v.y; m43 = v.z; m44 = v.w;
}

inline Matrix4x4& Matrix4x4::operator*=(float f) {
    m11*=f; m12*=f; m13*=f; m14*=f;
    m21*=f; m22*=f; m23*=f; m24*=f;
    m31*=f; m32*=f; m33*=f; m34*=f;
    m41*=f; m42*=f; m43*=f; m44*=f;

    return *this;
}

inline Matrix4x4& Matrix4x4::operator/=(float f) {
    register float div = 1.0f/f;
    return *this *= div;
}

inline Matrix4x4& Matrix4x4::operator+=(const Matrix4x4& m) {
    m11 += m.m11; m12 += m.m12; m13 += m.m13; m14 += m.m14;
    m21 += m.m21; m22 += m.m22; m23 += m.m23; m24 += m.m24;
    m31 += m.m31; m32 += m.m32; m33 += m.m33; m34 += m.m34;
    m41 += m.m41; m42 += m.m42; m43 += m.m43; m44 += m.m44;

    return *this;
}

inline Matrix4x4& Matrix4x4::operator-=(const Matrix4x4& m) {
    m11 -= m.m11; m12 -= m.m12; m13 -= m.m13; m14 -= m.m14;
    m21 -= m.m21; m22 -= m.m22; m23 -= m.m23; m24 -= m.m24;
    m31 -= m.m31; m32 -= m.m32; m33 -= m.m33; m34 -= m.m34;
    m41 -= m.m41; m42 -= m.m42; m43 -= m.m43; m44 -= m.m44;

    return *this;
}

inline Matrix4x4& Matrix4x4::operator*=(const Matrix4x4& m) {
    float t1, t2, t3;
    t1 =  m11*m.m11 + m12*m.m21 + m13*m.m31 + m14*m.m41;
    t2 =  m11*m.m12 + m12*m.m22 + m13*m.m32 + m14*m.m42;
    t3 =  m11*m.m13 + m12*m.m23 + m13*m.m33 + m14*m.m43;
    m14 = m11*m.m14 + m12*m.m24 + m13*m.m34 + m14*m.m44;
    m11 = t1;
    m12 = t2;
    m13 = t3;

    t1 =  m21*m.m11 + m22*m.m21 + m23*m.m31 + m24*m.m41;
    t2 =  m21*m.m12 + m22*m.m22 + m23*m.m32 + m24*m.m42;
    t3 =  m21*m.m13 + m22*m.m23 + m23*m.m33 + m24*m.m43;
    m24 = m21*m.m14 + m22*m.m24 + m23*m.m34 + m24*m.m44;
    m21 = t1;
    m22 = t2;
    m23 = t3;

    t1 =  m31*m.m11 + m32*m.m21 + m33*m.m31 + m34*m.m41;
    t2 =  m31*m.m12 + m32*m.m22 + m33*m.m32 + m34*m.m42;
    t3 =  m31*m.m13 + m32*m.m23 + m33*m.m33 + m34*m.m43;
    m34 = m31*m.m14 + m32*m.m24 + m33*m.m34 + m34*m.m44;
    m31 = t1;
    m32 = t2;
    m33 = t3;

    t1 =  m41*m.m11 + m42*m.m21 + m43*m.m31 + m44*m.m41;
    t2 =  m41*m.m12 + m42*m.m22 + m43*m.m32 + m44*m.m42;
    t3 =  m41*m.m13 + m42*m.m23 + m43*m.m33 + m44*m.m43;
    m44 = m41*m.m14 + m42*m.m24 + m43*m.m34 + m44*m.m44;
    m41 = t1;
    m42 = t2;
    m43 = t3;
    return *this;
}

inline Matrix4x4& Matrix4x4::Invert() {
    float Tbt34C12 = m31*m42-m32*m41;       // 2x2 subdeterminants
    float Tbt34C13 = m31*m43-m33*m41;
    float Tbt34C14 = m31*m44-m34*m41;
    float Tbt34C23 = m32*m43-m33*m42;
    float Tbt34C24 = m32*m44-m34*m42;
    float Tbt34C34 = m33*m44-m34*m43;
    float Tbt24C12 = m21*m42-m22*m41;       // 2x2 subdeterminants
    float Tbt24C13 = m21*m43-m23*m41;
    float Tbt24C14 = m21*m44-m24*m41;
    float Tbt24C23 = m22*m43-m23*m42;
    float Tbt24C24 = m22*m44-m24*m42;
    float Tbt24C34 = m23*m44-m24*m43;
    float Tbt23C12 = m21*m32-m22*m31;       // 2x2 subdeterminants
    float Tbt23C13 = m21*m33-m23*m31;
    float Tbt23C14 = m21*m34-m24*m31;
    float Tbt23C23 = m22*m33-m23*m32;
    float Tbt23C24 = m22*m34-m24*m32;
    float Tbt23C34 = m23*m34-m24*m33;

    float sd11 = m22*Tbt34C34 - m23*Tbt34C24 + m24*Tbt34C23;    // 3x3 subdeterminants
    float sd12 = m21*Tbt34C34 - m23*Tbt34C14 + m24*Tbt34C13;
    float sd13 = m21*Tbt34C24 - m22*Tbt34C14 + m24*Tbt34C12;
    float sd14 = m21*Tbt34C23 - m22*Tbt34C13 + m23*Tbt34C12;
    float sd21 = m12*Tbt34C34 - m13*Tbt34C24 + m14*Tbt34C23;    // 3x3 subdeterminants
    float sd22 = m11*Tbt34C34 - m13*Tbt34C14 + m14*Tbt34C13;
    float sd23 = m11*Tbt34C24 - m12*Tbt34C14 + m14*Tbt34C12;
    float sd24 = m11*Tbt34C23 - m12*Tbt34C13 + m13*Tbt34C12;
    float sd31 = m12*Tbt24C34 - m13*Tbt24C24 + m14*Tbt24C23;    // 3x3 subdeterminants
    float sd32 = m11*Tbt24C34 - m13*Tbt24C14 + m14*Tbt24C13;
    float sd33 = m11*Tbt24C24 - m12*Tbt24C14 + m14*Tbt24C12;
    float sd34 = m11*Tbt24C23 - m12*Tbt24C13 + m13*Tbt24C12;
    float sd41 = m12*Tbt23C34 - m13*Tbt23C24 + m14*Tbt23C23;    // 3x3 subdeterminants
    float sd42 = m11*Tbt23C34 - m13*Tbt23C14 + m14*Tbt23C13;
    float sd43 = m11*Tbt23C24 - m12*Tbt23C14 + m14*Tbt23C12;
    float sd44 = m11*Tbt23C23 - m12*Tbt23C13 + m13*Tbt23C12;

    register float detInv = 1.0f/(m11*sd11 - m12*sd12 + m13*sd13 - m14*sd14);

    m11 =  sd11*detInv;
    m12 = -sd21*detInv;
    m13 =  sd31*detInv;
    m14 = -sd41*detInv;
    m21 = -sd12*detInv;
    m22 =  sd22*detInv;
    m23 = -sd32*detInv;
    m24 =  sd42*detInv;
    m31 =  sd13*detInv;
    m32 = -sd23*detInv;
    m33 =  sd33*detInv;
    m34 = -sd43*detInv;
    m41 = -sd14*detInv;
    m42 =  sd24*detInv;
    m43 = -sd34*detInv;
    m44 =  sd44*detInv;

    return *this;
}

inline Matrix4x4& Matrix4x4::Transpose() {
    register float temp;

    temp = m12;
    m12 = m21;
    m21=temp;

    temp = m13;
    m13 = m31;
    m31 = temp;

    temp = m14;
    m14 = m41;
    m41 = temp;

    temp = m23;
    m23 = m32;
    m32 = temp;

    temp = m24;
    m24 = m42;
    m42 = temp;

    temp = m34;
    m34 = m43;
    m43 = temp;

    return *this;
}

Matrix4x4 Matrix4x4::Rotation(float angle, float x, float y, float z) {
	const float rad = angle * DEG_TO_RAD;

	const float x2 = x*x;
	const float y2 = y*y;
	const float z2 = z*z;
	const float c = cos(rad);
	const float s = sin(rad);
	const float cinv = 1-c;
	const float xy = x*y;
	const float xz = x*z;
	const float yz = y*z;
	const float xs = x*s;
	const float ys = y*s;
	const float zs = z*s;
	const float xzcinv = xz*cinv;
	const float xycinv = xy*cinv;
	const float yzcinv = yz*cinv;

	return Matrix4x4(x2 + c*(1-x2), xy*cinv+zs,    xzcinv - ys,   0,
					 xycinv - zs,   y2 + c*(1-y2), yzcinv + xs,   0,
					 xzcinv + ys,   yzcinv - xs,   z2 + c*(1-z2), 0,
					 0,             0,             0,             1);
}

} // namespace math

inline math::Matrix4x4 operator*(const math::Matrix4x4& a, const math::Matrix4x4& b) {
    math::Matrix4x4 out(a);
    return out*=b;
}

inline math::Matrix4x4 operator*(const math::Matrix4x4& m, float f) {
    return math::Matrix4x4(
                    m.m11 * f, m.m12 * f, m.m13 * f, m.m14 * f, 
                    m.m21 * f, m.m22 * f, m.m23 * f, m.m24 * f, 
                    m.m31 * f, m.m32 * f, m.m33 * f, m.m34 * f, 
                    m.m41 * f, m.m42 * f, m.m43 * f, m.m44 * f);
}

inline math::Matrix4x4 operator*(float f, const math::Matrix4x4& m) {
    return math::Matrix4x4(
                    f * m.m11, f * m.m12, f * m.m13, f * m.m14, 
                    f * m.m21, f * m.m22, f * m.m23, f * m.m24, 
                    f * m.m31, f * m.m32, f * m.m33, f * m.m34, 
                    f * m.m41, f * m.m42, f * m.m43, f * m.m44);
}

inline math::Matrix4x4 operator/(const math::Matrix4x4& m, float f) {
    register float div = 1.0f/f;
    return m*div;
}

inline math::Vector4 operator*(const math::Matrix4x4& m, const math::Vector4& v) {
    return math::Vector4(
                   m.m11*v.x + m.m12*v.y + m.m13*v.z + m.m14*v.w,
                   m.m21*v.x + m.m22*v.y + m.m23*v.z + m.m24*v.w,
                   m.m31*v.x + m.m32*v.y + m.m33*v.z + m.m34*v.w,
                   m.m41*v.x + m.m42*v.y + m.m43*v.z + m.m44*v.w);
}

// NOTE: This ignores the fourth row in the matrix
inline math::Vector3 operator*(const math::Matrix4x4& m, const math::Vector3& v) {
    return math::Vector3(
                   m.m11*v.x + m.m12*v.y + m.m13*v.z + m.m14,
                   m.m21*v.x + m.m22*v.y + m.m23*v.z + m.m24,
                   m.m31*v.x + m.m32*v.y + m.m33*v.z + m.m34);
}

inline std::ostream& operator<<(std::ostream& out, const math::Matrix4x4& m) {
    out << m.m11 << " " << m.m12 << " " << m.m13 << " " << m.m14 << std::endl;
    out << m.m21 << " " << m.m22 << " " << m.m23 << " " << m.m24 << std::endl;
    out << m.m31 << " " << m.m32 << " " << m.m33 << " " << m.m34 << std::endl;
    out << m.m41 << " " << m.m42 << " " << m.m43 << " " << m.m44 << std::endl;

    return out;
}
