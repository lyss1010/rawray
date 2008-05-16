/////////////////////////////////////////////////////////////////////////////
// Helper Functions : conversions.h
//
/////////////////////////////////////////////////////////////////////////////
#ifndef RAWRAY_BASE_CONVERSIONS_H
#define RAWRAY_BASE_CONVERSIONS_H
#include "stdafx.h"


/////////////////////////////////////////////////////////////////////////////
namespace base {

    const float DIVISOR_255 = 1.0f / float(UCHAR_MAX);

    uint8 DllExport FloatToByte( float f );
    float DllExport ByteToFloat( uint8 b );

	// big endian system, need to swap bytes to convert into
	// external little-endian representation
	void DllExport ByteSwapFloat(float& f);
	void DllExport LittleEndianFloat(float& f);
	void DllExport BigEndianFloat(float& f);

} // namespace base
/////////////////////////////////////////////////////////////////////////////


#endif // RAWRAY_BASE_CONVERSIONS_H
