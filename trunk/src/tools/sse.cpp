/////////////////////////////////////////////////////////////////////////////
// sse.cpp
//
/////////////////////////////////////////////////////////////////////////////
#include "sse.h"

namespace tools {
namespace sse {

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
