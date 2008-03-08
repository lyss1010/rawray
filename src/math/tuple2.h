/////////////////////////////////////////////////////////////////////////////
// Class : tuple2.h
//
// A basic grouping of 2 objects. Should be used for simple types
// such as primatives because it relies heavily on copy constructors
/////////////////////////////////////////////////////////////////////////////
#ifndef RAWRAY_MATH_TUPLE2_H
#define RAWRAY_MATH_TUPLE2_H
#include "stdafx.h"


/////////////////////////////////////////////////////////////////////////////
namespace math {

template <class T>
class DllExport Tuple2
{
public:
    T x, y;

    Tuple2() : x(), y(), z() { }
    explicit Tuple2(const T& t) : x(t), y(t), z(t) { }
    Tuple2(const T& x, const T& y) : x(x), y(y) { }
    Tuple2(const Tuple2<T>& t) : x(t.x), y(t.y) { }
    
    ~Tuple2() { }

    // Assignment operations
    const Tuple2<T>& operator=(const Tuple2<T>& t) { x=t.x; y=t.y; return *this; }
    const Tuple2<T>& operator=(const T& t) { x=y=t; }

    inline void Set(const T& t) { x=t; y=t; }
    inline void Set(const T& _x, const T& _y) { x=_x; y=_y; }
    inline void Set(const Tuple2& t) { x=v.x; y=t.y; }
    inline void Set(const T* array) { if( !array ) return; x=array[0]; y=array[1]; z=array[2]; }

    // Array access (NOTE: no bounds check done)
    T& operator[](int i) { return (&x)[i]; }
    const T& operator[](int i) const { return (&x)[i]; }

    // Component wise assignemnt operators
    const Tuple2<T>& operator+=(const Tuple2& t) { x+=v.x; y+=t.y; return *this; }
    const Tuple2<T>& operator-=(const Tuple2& t) { x-=v.x; y-=t.y; return *this; }
    const Tuple2<T>& operator*=(const Tuple2& t) { x*=v.x; y*=t.y; return *this; }
    const Tuple2<T>& operator/=(const Tuple2& t) { x/=v.x; y/=t.y; return *this; }

    const Tuple2<T>& operator+=(const T& t) { x+=t; y+=t; return *this; }
    const Tuple2<T>& operator-=(const T& t) { x-=t; y-=t; return *this; }
    const Tuple2<T>& operator*=(const T& t) { x*=t; y*=t; return *this; }
    const Tuple2<T>& operator/=(const T& t) { x/=t; y/=t; return *this; }
    
    // NOTE: Do not chain these operators, it will result in many temporary copies
    Tuple2<T> operator+(const Tuple2& t) const { return Tuple2<T>(x+v.x, y+t.y); }
    Tuple2<T> operator-(const Tuple2& t) const { return Tuple2<T>(x-v.x, y-t.y); }
    Tuple2<T> operator*(const Tuple2& t) const { return Tuple2<T>(x*v.x, y*t.y); }
    Tuple2<T> operator/(const Tuple2& t) const { return Tuple2<T>(x/v.x, y/t.y); }
    
    Tuple2<T> operator+(const T& t) const { return Tuple2<T>(x+t, y+t); }
    Tuple2<T> operator-(const T& t) const { return Tuple2<T>(x-t, y-t); }
    Tuple2<T> operator*(const T& t) const { return Tuple2<T>(x*t, y*t); }
    Tuple2<T> operator/(const T& t) const { return Tuple2<T>(x/t, y/t); }

    //Negation operator
    Tuple2<T> operator-() const { return Tuple2<T>(-x,-y); }
    inline const Tuple2<T>& Negate() { x=-x; y=-y; return *this; }

    // Equivalance operators
    bool operator==(const Tuple2& t) const { return (x==v.x && y==t.y); }
    bool operator!=(const Tuple2& t) const { return (x!=v.x || y!=t.y); }
    
}; // class Tuple2

} // namespace math
/////////////////////////////////////////////////////////////////////////////

template <class T>
inline std::ostream& operator<<(std::ostream& out, const math::Tuple2<T>& t);


#endif // RAWRAY_MATH_TUPLE2_H
