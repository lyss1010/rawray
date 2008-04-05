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
}

// Console Entry point
int _tmain( int argc, _TCHAR* argv[] )
{
	// Enable memory leak messages on exit
	_CrtSetDbgFlag ( _CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF );
	//_CrtSetBreakAlloc( 139 );

    // Initialize options defaults
    rawray::options::init();

    // TODO: Read in options

    // Open GLUT window and begin rendering
	atexit( exit_cleanup );
	rawray::GlutWindow::Create(&argc, argv);
	rawray::g_window->MainLoop(); // never returns

	assert( 0 );
	return 0;
}
