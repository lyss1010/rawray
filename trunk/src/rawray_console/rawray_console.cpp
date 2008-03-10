/////////////////////////////////////////////////////////////////////////////
// Console Entry Point : rawray_console.cpp
//
/////////////////////////////////////////////////////////////////////////////
#include "rawray_console.h"
#include "rawray/glut_window.h"
#include "rawray/options.h"

// Console Entry point
int _tmain( int argc, _TCHAR* argv[] )
{
    // Initialize options defaults
    rawray::options::init();

    // TODO: Read in options

    // Open GLUT window and begin rendering
    rawray::GlutWindow window(&argc, argv);
    window.MainLoop();

    system("pause");
	return 0;
}
