/////////////////////////////////////////////////////////////////////////////
// conversions.cpp
//
/////////////////////////////////////////////////////////////////////////////
#include "conversions.h"

namespace base {

inline uint8 DllExport FloatToByte( float f ) {
    register float scaled = f * UCHAR_MAX;
    return scaled>UCHAR_MAX ? UCHAR_MAX : (uint8)scaled;
}

inline float DllExport ByteToFloat( uint8 b ) {
    return b * DIVISOR_255;
}

inline void ByteSwapFloat(float& f) {
	union {float f; unsigned char b[4];} u1, u2;

	u1.f = f;
	u2.b[0] = u1.b[3];
	u2.b[1] = u1.b[2];
	u2.b[2] = u1.b[1];
	u2.b[3] = u1.b[0];
	f = u2.f;
}

#if WORDS_BIGENDIAN

inline void LittleEndianFloat(float& f) { ByteSwapFloat (f); }
inline void BigEndianFloat(float&) {}

#else

// little endian, no need to swap
inline void LittleEndianFloat(float&) { }
inline void BigEndianFloat(float& f) { ByteSwapFloat(f); }

#endif


} // namespace base
