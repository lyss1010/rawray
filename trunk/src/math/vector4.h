/////////////////////////////////////////////////////////////////////////////
// Class : vector4.h
// 
// 4 Element floating point vector
// Based off of Miro code from UCSD.CSE168.SP08
/////////////////////////////////////////////////////////////////////////////
#ifndef RAWRAY_MATH_VECTOR4_H
#define RAWRAY_MATH_VECTOR4_H
#include "stdafx.h"


/////////////////////////////////////////////////////////////////////////////
// Includes
/////////////////////////////////////////////////////////////////////////////
#include "vector3.h"


/////////////////////////////////////////////////////////////////////////////
namespace math {

class DllExport Vector4
{
public:
    float x, y, z, w;

    Vector4() : x(0.0f), y(0.0f), z(0.0f), w(0.0f) { }
    explicit Vector4(float f) : x(f), y(f), z(f), w(1.0f) { }
    Vector4(float x, float y, float z, float w) : x(x), y(y), z(z), w(w) { }
    Vector4(const Vector4& v) : x(v.x), y(v.y), z(v.z), w(v.w) { }
    explicit Vector4(const Vector3& v) : x(v.x), y(v.y), z(v.z), w(1.0f) { }
    Vector4(const Vector3& v, float w) : x(v.x), y(v.y), z(v.z), w(w) { }

    ~Vector4() { }

    // Assignment operations
    const Vector4& operator=(const Vector4& v) { x=v.x; y=v.y; z=v.z; w=v.w; return *this; }
    const Vector4& operator=(float f) { x=y=z=w=f; return *this; }

    inline void Set(float f) { x=f; y=f; z=f; w=f; }
    inline void Set(float _x, float _y, float _z, float _w) { x=_x; y=_y; z=_z; w=_w; }
    inline void Set(const Vector4& v) { x=v.x; y=v.y; z=v.z; w=v.w; }
    inline void Set(const Vector3& v, float f) { x=v.x; y=v.y; z=v.z; w=f; }
    inline void Set(const float *array) { if( !array ) return; x=array[0]; y=array[1]; z=array[2]; w=array[3]; }

    // Array access (NOTE: no bounds check done)
    float& operator[](int i) { return (&x)[i]; }
    const float& operator[](int i) const { return (&x)[i]; }

    // Component wise assignemnt operators
    const Vector4& operator+=(const Vector4& v) { x+=v.x; y+=v.y; z+=v.z; w+=v.w; return *this; }
    const Vector4& operator-=(const Vector4& v) { x-=v.x; y-=v.y; z-=v.z; w-=v.w; return *this; }
    const Vector4& operator*=(const Vector4& v) { x*=v.x; y*=v.y; z*=v.z; w*=v.w; return *this; }
    const Vector4& operator/=(const Vector4& v) { x/=v.x; y/=v.y; z/=v.z; w/=v.w; return *this; }

    const Vector4& operator+=(float f) { x+=f; y+=f; z+=f; w+=f; return *this; }
    const Vector4& operator-=(float f) { x-=f; y-=f; z-=f; w-=f; return *this; }
    const Vector4& operator*=(float f) { x*=f; y*=f; z*=f; w*=f; return *this; }
    const Vector4& operator/=(float f) { float div = 1.0f/f; x*=div; y*=div; z*=div; w*=div; return *this; }
    
    // NOTE: Do not chain these operators, it will result in many temporary copies
    Vector4 operator+(const Vector4& v) const { return Vector4(x+v.x, y+v.y, z+v.z, w+v.w); }
    Vector4 operator-(const Vector4& v) const { return Vector4(x-v.x, y-v.y, z-v.z, w-v.w); }
    Vector4 operator*(const Vector4& v) const { return Vector4(x*v.x, y*v.y, z*v.z, w*v.w); }
    Vector4 operator/(const Vector4& v) const { return Vector4(x/v.x, y/v.y, z/v.z, w/v.w); }
    
    Vector4 operator+(const float f) const { return Vector4(x+f, y+f, z+f, w+f); }
    Vector4 operator-(const float f) const { return Vector4(x-f, y-f, z-f, w-f); }
    Vector4 operator*(const float f) const { return Vector4(x*f, y*f, z*f, w*f); }
    Vector4 operator/(const float f) const { float div = 1.0f/f; return Vector4(x*div, y*div, z*div, w*div); }

    //Negation operator
    Vector4 operator-() const { return Vector4(-x,-y,-z,-w); }
    inline const Vector4& Negate() { x=-x; y=-y; z=-z; w=-w; return *this; }

    // Equivalance operators
    bool operator==(const Vector4& v) const { return (x==v.x && y==v.y && z==v.z && w==v.w); }
    bool operator!=(const Vector4& v) const { return (x!=v.x || y!=v.y || z!=v.z || w!=v.w); }

    inline bool Equals(const Vector4& v, float delta) const;

    // Length squared
    inline float Length2() const { return x*x + y*y + z*z + w*w; }
    inline float Length() const { return sqrtf( Length2() ); }

    // Make unit length & return old length
    inline float Unitize() { float length = Length(); *this /= length; return length; }
    
    // Creation of unit length vector
    inline const Vector4& Normalize() { return *this /= Length(); }
    inline Vector4 Normalized() const { return *this / Length(); }

    inline float Dot(const Vector4& v) const { return x*v.x + y*v.y + z*v.z + w*v.w; }

}; // class Vector4

DllExport inline float Dot(const Vector4& a, const Vector4& b) { return a.x*b.x + a.y*b.y + a.z*b.z + a.w*b.w; }


} // namespace math
/////////////////////////////////////////////////////////////////////////////

DllExport inline math::Vector4 operator*(float f, const math::Vector4& v) { return math::Vector4(v.x*f, v.y*f, v.z*f, v.w*f); }
DllExport std::ostream& operator<<(std::ostream& out, const math::Vector4& v);


#endif // RAWRAY_MATH_VECTOR4_H