/////////////////////////////////////////////////////////////////////////////
// Class : vector2.h
// 
// 2 Element floating point vector
// Based off of Miro code from UCSD.CSE168.SP08
/////////////////////////////////////////////////////////////////////////////
#ifndef RAWRAY_MATH_VECTOR2_H
#define RAWRAY_MATH_VECTOR2_H
#include "stdafx.h"


/////////////////////////////////////////////////////////////////////////////
namespace math {

class DllExport Vector2
{
public:
    float x, y;

    Vector2() : x(0.0f), y(0.0f) { }
    explicit Vector2(float f) : x(f), y(f) { }
    Vector2(float x, float y) : x(x), y(y) { }
    Vector2(const Vector2& v) : x(v.x), y(v.y) { }

    ~Vector2() { }

    // Assignment operations
    const Vector2& operator=(const Vector2& v) { x=v.x; y=v.y; return *this; }
    const Vector2& operator=(float f) { x=y=f; return *this; }

    inline void Set(float f) { x=f; y=f; }
    inline void Set(float _x, float _y) { x=_x; y=_y; }
    inline void Set(const Vector2& v) { x=v.x; y=v.y; }
    inline void Set(const float *array) { if( !array ) return; x=array[0]; y=array[1]; }

    // Array access (NOTE: no bounds check done)
    float& operator[](int i) { return (&x)[i]; }
    const float & operator[](int i) const { return (&x)[i]; }

    // Component wise assignemnt operators
    const Vector2& operator+=(const Vector2& v) { x+=v.x; y+=v.y; return *this; }
    const Vector2& operator-=(const Vector2& v) { x-=v.x; y-=v.y; return *this; }
    const Vector2& operator*=(const Vector2& v) { x*=v.x; y*=v.y; return *this; }
    const Vector2& operator/=(const Vector2& v) { x/=v.x; y/=v.y; return *this; }

    const Vector2& operator+=(float f) { x+=f; y+=f; return *this; }
    const Vector2& operator-=(float f) { x-=f; y-=f; return *this; }
    const Vector2& operator*=(float f) { x*=f; y*=f; return *this; }
    const Vector2& operator/=(float f) { float div = 1.0f/f; x*=div; y*=div; return *this; }
    
    // NOTE: Do not chain these operators, it will result in many temporary copies
    Vector2 operator+(const Vector2& v) const { return Vector2(x+v.x, y+v.y); }
    Vector2 operator-(const Vector2& v) const { return Vector2(x-v.x, y-v.y); }
    Vector2 operator*(const Vector2& v) const { return Vector2(x*v.x, y*v.y); }
    Vector2 operator/(const Vector2& v) const { return Vector2(x/v.x, y/v.y); }
    
    Vector2 operator+(const float f) const { return Vector2(x+f, y+f); }
    Vector2 operator-(const float f) const { return Vector2(x-f, y-f); }
    Vector2 operator*(const float f) const { return Vector2(x*f, y*f); }
    Vector2 operator/(const float f) const { float div = 1.0f/f; return Vector2(x*div, y*div); }

    //Negation operator
    Vector2 operator-() const { return Vector2(-x,-y); }
    inline const Vector2& Negate() { x=-x; y=-y; return *this; }

    // Equivalance operators
    bool operator==(const Vector2& v) const { return (x==v.x && y==v.y); }
    bool operator!=(const Vector2& v) const { return (x!=v.x || y!=v.y); }

    inline bool Equals(const Vector2& v, float delta) const;

    // Length squared
    inline float Length2() const { return x*x + y*y; }
    inline float Length() const { return sqrtf( Length2() ); }

    // Make unit length & return old length
    inline float Unitize() { float length = Length(); *this /= length; return length; }
    
    // Creation of unit length vector
    inline const Vector2& Normalize() { return *this /= Length(); }
    inline Vector2 Normalized() const { return *this / Length(); }

}; // class Vector2

} // namespace math
/////////////////////////////////////////////////////////////////////////////

DllExport inline math::Vector2 operator*(float f, const math::Vector2& v) { return math::Vector2(v.x*f, v.y*f); }
DllExport std::ostream& operator<<(std::ostream& out, const math::Vector2& v);


#endif // RAWRAY_MATH_VECTOR2_H
