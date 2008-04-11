/////////////////////////////////////////////////////////////////////////////
// Console Entry Point : rawray_console.cpp
//
/////////////////////////////////////////////////////////////////////////////
#include "rawray_console.h"
#include "rawray/glut_window.h"
#include "rawray/options.h"


// Exit point
void exit_cleanup(void) {
	rawray::GlutWindow::Destroy();
    _CrtDumpMemoryLeaks();
}

// Console Entry point
int _tmain( int argc, _TCHAR* argv[] )
{
	// Enable memory leak messages on exit
	_CrtSetDbgFlag ( _CRTDBG_ALLOC_MEM_DF );
	//_CrtSetBreakAlloc( 438 );

    // Initialize options defaults
    rawray::options::init();

    // Open GLUT window and begin rendering
	atexit( exit_cleanup );
	rawray::GlutWindow::Create(&argc, argv);

    // This will only return if we are in headless mode
	rawray::g_window->MainLoop();

	return 0;
}
