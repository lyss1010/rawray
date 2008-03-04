/////////////////////////////////////////////////////////////////////////////
// Class : vector3.h
// 
// 3 Element floating point vector
// Based off of Miro code from UCSD.CSE168.SP08
/////////////////////////////////////////////////////////////////////////////
#ifndef RAWRAY_MATH_VECTOR3_H
#define RAWRAY_MATH_VECTOR3_H
#include "stdafx.h"


/////////////////////////////////////////////////////////////////////////////
// Includes
/////////////////////////////////////////////////////////////////////////////
#include <math.h>
#include <iostream>


/////////////////////////////////////////////////////////////////////////////
namespace math {

struct DllExport Vector3
{
    float x, y, z;

    Vector3() : 
        x(0.0f), y(0.0f), z(0.0f) { std::cout << "Vector3()" << std::endl; }

    Vector3(float f) : 
        x(f), y(f), z(f) { std::cout << "Vector3(f=" << f << ")" << std::endl; }

    Vector3(float x, float y, float z) :
        x(x), y(y), z(z) { std::cout << "Vector3(x=" << x << ", y=" << y << ", z=" << z << ")" << std::endl; }

    // Assignment operations
    const Vector3& operator=(const Vector3& v) { x=v.x; y=v.y; z=v.z; return *this; }
    const Vector3& operator=(float f) { x=y=z=f; return *this; }

    inline void Set(float _x, float _y, float _z) { x=_x; y=_y; z=_z; }
    inline void Set(const float *array) { if( !array ) return; x=array[0]; y=array[1]; z=array[2]; }

    // Array access (NOTE: no bounds check done)
    float& operator[](int i) { return (&x)[i]; }
    const float & operator[](int i) const { return (&x)[i]; }

    // Component wise assignemnt operators
    const Vector3& operator+=(const Vector3& v) { x+=v.x; y+=v.y; z+=v.z; return *this; }
    const Vector3& operator-=(const Vector3& v) { x-=v.x; y-=v.y; z-=v.z; return *this; }
    const Vector3& operator*=(const Vector3& v) { x*=v.x; y*=v.y; z*=v.z; return *this; }
    const Vector3& operator/=(const Vector3& v) { x/=v.x; y/=v.y; z/=v.z; return *this; }

    const Vector3& operator+=(float f) { x+=f; y+=f; z+=f; return *this; }
    const Vector3& operator-=(float f) { x-=f; y-=f; z-=f; return *this; }
    const Vector3& operator*=(float f) { x*=f; y*=f; z*=f; return *this; }
    const Vector3& operator/=(float f) { float div = 1.0f/f; x*=div; y*=div; z*=div; return *this; }
    
    // Component wise operators (NOTE: Makes and returns new object every time)
    //Vector3 operator+(const Vector3& v) const { return Vector3(x+v.x, y+v.y, z+v.z); }
    //Vector3 operator-(const Vector3& v) const { return Vector3(x-v.x, y-v.y, z-v.z); }
    //Vector3 operator*(const Vector3& v) const { return Vector3(x*v.x, y*v.y, z*v.z); }
    Vector3 operator/(const Vector3& v) const { return Vector3(x/v.x, y/v.y, z/v.z); }
    
    //Vector3 operator+(const float f) const { return Vector3(x+f, y+f, z+f); }
    //Vector3 operator-(const float f) const { return Vector3(x-f, y-f, z-f); }
    //Vector3 operator*(const float f) const { return Vector3(x*f, y*f, z*f); }
    Vector3 operator/(const float f) const { float div = 1.0f/f; return Vector3(x*div, y*div, z*div); }

    // Negation operator
    //Vector3 operator-() const { return Vector3(-x,-y,-z); }
    inline const Vector3& Negate() { x=-x; y=-y; z=-z; return *this; }

    // Equivalance operators
    bool operator==(const Vector3& v) const { return (x==v.x && y==v.y && z==v.z); }
    bool operator!=(const Vector3& v) const { return (x!=v.x || y!=v.y || z!=v.z); }

    inline bool Equals(const Vector3& v, float delta);

    // Length squared
    inline float Length2() const { return x*x + y*y + z*z; }
    inline float Length() const { return sqrtf( Length2() ); }

    // Make unit length & return old length
    inline float Unitize() { float length = Length(); *this /= length; return length; }
    
    // Creation of unit length vector
    inline const Vector3& Normalize() { return *this /= Length(); }
    inline Vector3 Normalized() { return *this / Length(); }

    // Rotation around a given vector by given angle in radians
    inline const Vector3& Rotate(float theta, const Vector3 & v) { return *this = Rotated(theta, v); }
    inline Vector3 Rotated(float theta, const Vector3 & v) const;

    inline float Dot(const Vector3& v) { return x*v.x + y*v.y + z*v.z; }

    inline Vector3& Cross(const Vector3& v) { 
        Set( y*v.z - z*v.y,
             z*v.x - x*v.z,
             x*v.y - y*v.x );

        return *this;
    }

}; // struct Vector3

/////////////////////////////////////////////////////////////////////////////
// Localized Friend functions
/////////////////////////////////////////////////////////////////////////////
inline float Dot(const Vector3& a, const Vector3& b) { return a.x*b.x + a.y*b.y + a.z*b.z; }

inline Vector3 Cross(const Vector3& a, const Vector3& b) {
    return Vector3( a.y*b.z - a.z*b.y,
                    a.z*b.x - a.x*b.z,
                    a.x*b.y - a.y*b.x );
}

} // namespace math
/////////////////////////////////////////////////////////////////////////////


/////////////////////////////////////////////////////////////////////////////
// Global Friend functions
/////////////////////////////////////////////////////////////////////////////

inline math::Vector3 operator*(float f, const math::Vector3& v) { return math::Vector3(v.x*f, v.y*f, v.z*f); }


#endif // RAWRAY_MATH_VECTOR3_H