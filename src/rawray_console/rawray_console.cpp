/////////////////////////////////////////////////////////////////////////////
// Console Entry Point : rawray_console.cpp
//
/////////////////////////////////////////////////////////////////////////////
#include "rawray_console.h"
#include "rawray/glut_window.h"
#include "rawray/options.h"
#include "tools/sse.h"

#include "rawray/object.h"
#include "rawray/triangle.h"
#include "rawray/triangle_factory.h"
#include <vector>

// Exit point
void exit_cleanup(void) {
	rawray::GlutWindow::Destroy();
    _CrtDumpMemoryLeaks();
}


bool SSETest() {
#ifdef SSE
    std::cout << "Testing SSE Version... ";
    int version = tools::sse::GetVersion();
    if( version > tools::sse::SSE1 ) {
        std::cout << "OK" << std::endl;
        return true;
    } else {
        std::cout << "FAILED" << std::endl;
        return false;
    }
    
#else
    std::cout << "SSE Disabled" << std::endl;
    return true;
#endif // SSE
}

// Console Entry point
int _tmain( int argc, _TCHAR* argv[] )
{
	// Enable memory leak messages on exit
	_CrtSetDbgFlag ( _CRTDBG_ALLOC_MEM_DF );
	//_CrtSetBreakAlloc( 143 );

    if( !SSETest() ) {
        std::cout << "This compute does not support the required SSE Version" << std::endl;
        return -1;
    }
        
    tools::sse::SetFastFPU();

    // Initialize options defaults
    rawray::options::init();

    // Open GLUT window and begin rendering
	atexit( exit_cleanup );
	rawray::GlutWindow::Create(&argc, argv);

    // This will only return if we are in headless mode
	rawray::g_window->MainLoop();

	return 0;
}
