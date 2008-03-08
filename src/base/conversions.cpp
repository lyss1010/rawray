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

} // namespace base
