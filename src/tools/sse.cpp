/////////////////////////////////////////////////////////////////////////////
// sse.cpp
//
/////////////////////////////////////////////////////////////////////////////
#include "sse.h"
#include <xmmintrin.h>

namespace tools {
namespace sse {

//BIT_15;           // Flush all underflows to go to zero
//BIT_14;           // Round to positive values
//BIT_13;           // Round to negative values
//BIT_13 | BIT_14;  // Round to zero
//BIT_13 | BIT_14;  // Round to nearest (these bits must be both 0)
//BIT_12;           // Mask out Precision exceptions
//BIT_11;           // Mask out Underflow exceptions
//BIT_10;           // Mask out Overflow exceptions
//BIT_09;           // Mask out Divide by Zero exceptions
//BIT_08;           // Mask out Denormal exceptions
//BIT_07;           // Mask out Invalid Operation exceptions
//BIT_06;           // Force denormals directly to zero (note: not implemented in all SSE cpus)

#define FPU_MXCSR_DEFAULT 0x1f80
#define FPU_FAST_MASK BIT_15 | BIT_12 | BIT_11 | BIT_10 | BIT_09 | BIT_08 | BIT_07 | BIT_06
#define FPU_PRECISE_MASK 0

// Loose precision on floating point calculations in favor of speed
DllExport void SetFastFPU() {
    // TODO: Check if DAZ is supported before trying to change that bit
    _mm_setcsr( FPU_MXCSR_DEFAULT | FPU_FAST_MASK );
}

// Gain precision on floating point calculations at cost of speed
DllExport void SetNormalFPU() {
    _mm_setcsr( FPU_MXCSR_DEFAULT );
}

// TODO: Return an enum so we can differentiate between versions of SSE3 and SSE4
VERSION GetVersion() {
    // Call cpuid to see which functions is supports
    // We want function 0x01 to get features
    int reg_eax;
    __asm {
        mov eax, 0;
        cpuid;
        mov reg_eax, eax;
    }

    // If the cpuid doesn't even support telling us the features, it doesn't support sse
    if( reg_eax < 1 ) return tools::sse::NONE;

    // Now we can request features from cpuid
    int reg_ecx, reg_edx;
    __asm {
        mov eax, 1;
        cpuid;
        mov reg_ecx, ecx;
        mov reg_edx, edx;
    }

    // SSE4.2 is bit 20
    if( reg_ecx & BIT_20 )
        return tools::sse::SSE4_2;

    // SSE4.1 is bit 19
    if( reg_ecx & BIT_19 )
        return tools::sse::SSE4_1;

    // SSSE3 is bit 9 is ecx
    if( reg_ecx & BIT_09 )
        return tools::sse::SSSE3;

    // SSE3 is bit 0 in ecx
    if( reg_ecx & BIT_00 )
        return tools::sse::SSE3;

    // SSE2 is bit 26 in edx
    if( reg_edx & BIT_26 )
        return tools::sse::SSE2;

    // SSE is bit 25 in edx
    if( reg_edx & BIT_25 )
        return tools::sse::SSE1;

    return tools::sse::NONE;
}

} // namespace tools::sse
} // namespace tools
