/////////////////////////////////////////////////////////////////////////////
// Console Entry Point : rawray_console.cpp
//
/////////////////////////////////////////////////////////////////////////////
#include "rawray_console.h"
#include "rawray.h"


// Console Entry point
int _tmain( int argc, _TCHAR* argv[] )
{
    UNREFERENCED_PARAMETER(argc);
    UNREFERENCED_PARAMETER(argv);

    rawray::RawRay rayTracer(argc);

	return 0;
}
