/////////////////////////////////////////////////////////////////////////////
// Class : tuple3.h
//
// A basic grouping of 3 objects. Should be used for simple types
// such as primatives because it relies heavily on copy constructors
/////////////////////////////////////////////////////////////////////////////
#ifndef RAWRAY_MATH_TUPLE3_H
#define RAWRAY_MATH_TUPLE3_H
#include "stdafx.h"


/////////////////////////////////////////////////////////////////////////////
namespace math {

template <class T>
class DllExport Tuple3
{
public:
    T x, y, z;

    Tuple3() : x(), y(), z() { }
    explicit Tuple3(const T& t) : x(t), y(t), z(t) { }
    Tuple3(const T& x, const T& y, const T& z) : x(x), y(y), z(z) { }
    Tuple3(const Tuple3<T>& t) : x(t.x), y(t.y), z(t.z) { }

    ~Tuple3() { }

    // Assignment operations
    const Tuple3<T>& operator=(const Tuple3<T>& t) { x=t.x; y=t.y; z=t.z; return *this; }
    const Tuple3<T>& operator=(const T& t) { x=y=z=t; }

    inline void Set(const T& t) { x=t; y=t; z=t; }
    inline void Set(const T& _x, const T& _y, const T& _z) { x=_x; y=_y; z=_z; }
    inline void Set(const Tuple3& t) { x=v.x; y=t.y; z=t.z; }
    inline void Set(const T* array) { if( !array ) return; x=array[0]; y=array[1]; z=array[2]; w=array[3]; }

    // Array access (NOTE: no bounds check done)
    T& operator[](int i) { return (&x)[i]; }
    const T& operator[](int i) const { return (&x)[i]; }

    // Component wise assignemnt operators
    const Tuple3<T>& operator+=(const Tuple3& t) { x+=v.x; y+=t.y; z+=t.z; return *this; }
    const Tuple3<T>& operator-=(const Tuple3& t) { x-=v.x; y-=t.y; z-=t.z; return *this; }
    const Tuple3<T>& operator*=(const Tuple3& t) { x*=v.x; y*=t.y; z*=t.z; return *this; }
    const Tuple3<T>& operator/=(const Tuple3& t) { x/=v.x; y/=t.y; z/=t.z; return *this; }

    const Tuple3<T>& operator+=(const T& t) { x+=t; y+=t; z+=t; return *this; }
    const Tuple3<T>& operator-=(const T& t) { x-=t; y-=t; z-=t; return *this; }
    const Tuple3<T>& operator*=(const T& t) { x*=t; y*=t; z*=t; return *this; }
    const Tuple3<T>& operator/=(const T& t) { x/=t; y/=t; z/=t; return *this; }
    
    // NOTE: Do not chain these operators, it will result in many temporary copies
    Tuple3<T> operator+(const Tuple3& t) const { return Tuple3<T>(x+v.x, y+t.y, z+t.z); }
    Tuple3<T> operator-(const Tuple3& t) const { return Tuple3<T>(x-v.x, y-t.y, z-t.z); }
    Tuple3<T> operator*(const Tuple3& t) const { return Tuple3<T>(x*v.x, y*t.y, z*t.z); }
    Tuple3<T> operator/(const Tuple3& t) const { return Tuple3<T>(x/v.x, y/t.y, z/t.z); }
    
    Tuple3<T> operator+(const T& t) const { return Tuple3<T>(x+t, y+t, z+t); }
    Tuple3<T> operator-(const T& t) const { return Tuple3<T>(x-t, y-t, z-t); }
    Tuple3<T> operator*(const T& t) const { return Tuple3<T>(x*t, y*t, z*t); }
    Tuple3<T> operator/(const T& t) const { return Tuple3<T>(x/t, y/t, z/t); }

    // Negation operator
    Tuple3<T> operator-() const { return Tuple3<T>(-x,-y,-z); }
    inline const Tuple3<T>& Negate() { x=-x; y=-y; z=-z; return *this; }

    // Equivalance operators
    bool operator==(const Tuple3& t) const { return (x==v.x && y==t.y && z==t.z); }
    bool operator!=(const Tuple3& t) const { return (x!=v.x || y!=t.y || z!=t.z); }
    
}; // class Tuple3

} // namespace math
/////////////////////////////////////////////////////////////////////////////

template <class T>
DllExport inline std::ostream& operator<<(std::ostream& out, const math::Tuple3<T>& t);


#endif // RAWRAY_MATH_TUPLE3_H
