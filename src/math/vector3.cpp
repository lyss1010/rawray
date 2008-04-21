/////////////////////////////////////////////////////////////////////////////
// vector3.cpp
//
/////////////////////////////////////////////////////////////////////////////
#include "vector3.h"
#include <xmmintrin.h>


namespace math {

bool Vector3::Equals(const Vector3& v, float delta) const {
    return (FloatEquals(x, v.x, delta) &&
            FloatEquals(y, v.y, delta) &&
            FloatEquals(y, v.y, delta) );
}

Vector3 Vector3::Rotated(float theta, const Vector3& v) const {
    const float c = cosf(theta);
    const float s = sinf(theta);
    const float x = math::Dot(*this, v);

    Vector3 v0 = x * v;
    Vector3 v1 = *this - v0;
    Vector3 v2; math::Cross(v, v1, v2);

    return v0 + c*v1 + s*v2;
}

uint8 Vector3::GetDominantAxis() const {
    const float absX = fabs(x);
    const float absY = fabs(y);
    const float absZ = fabs(z);

    if( absX > absY )
        return ( (absX > absZ) ? 0 : 2 );
    else
        return ( (absY > absZ) ? 1 : 2 );
}

Vector3& Cross(const Vector3& a, const Vector3& b, Vector3& out) {
    out.x = a.y*b.z - a.z*b.y;
    out.y = a.z*b.x - a.x*b.z;
    out.z = a.x*b.y - a.y*b.x;

    return out;
//
//#else // SSE
//    const float* pa = &a.x;
//    const float* pb = &b.x;
//    float* pout = &out.x;
//
//    __asm {
//        mov    esi, pa;
//        movaps xmm0, [esi];
//        movaps xmm1, xmm0;
//
//        mov    esi, pb;
//        movaps xmm2, [esi];
//        movaps xmm3, xmm2;
//
//        // xmm2 = [ by bz bx . ]
//        shufps xmm2, xmm2, 201; // 11:00:10:01
//
//        // xmm3 = [ bz bx by . ]
//        shufps xmm3, xmm3, 210; // 11:01:00:10
//
//        // xmm0 = [ ax*by ay*bz az*bx ]
//        mulps xmm0, xmm2;
//
//        // xmm1 = [ ax*bz ay*bx az*by ]
//        mulps xmm1, xmm3;
//
//        // xmm1 = [ ay*bx az*by ax*bz ]
//        shufps xmm1, xmm1, 201; // 11:00:10:01
//
//        // xmm0 = [ ax*by-ay*bx ay*bz-az*by az*bx-az*bz ]
//        subps xmm0, xmm1;
//
//        // xmm0 = [ ay*bz-az*by az*bx-az*bz ax*by-ay*bx ]
//        shufps xmm0, xmm0, 201; // 11:00:10:01
//
//        // Export data
//        movaps [pout], xmm0;
//    }
//
//    return out;
//#endif
}


} // namespace math



inline std::ostream& operator<<(std::ostream& out, const math::Vector3& v) {
    return out << v.x << " " << v.y << " " << v.z;
}
