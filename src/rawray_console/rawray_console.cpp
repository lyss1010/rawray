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

struct cVector
{
	float x,y,z;
};

// See: http://www.3dbuzz.com/vbforum/showthread.php?t=104753
void VectorTest()
{
	cVector vec1;
	vec1.x=0.5;
	vec1.y=1.5;
	vec1.z=-3.141;

	__asm {
	    movups xmm1, vec1
		mulps xmm1, xmm1
		movups vec1, xmm1
	}

    std::cout << vec1.x << " " << vec1.y << " " << vec1.z << '\n';
}


// Console Entry point
int _tmain( int argc, _TCHAR* argv[] )
{
	// Enable memory leak messages on exit
	_CrtSetDbgFlag ( _CRTDBG_ALLOC_MEM_DF );
	//_CrtSetBreakAlloc( 438 );

    // TEMP: vector test
    //VectorTest();

    // Initialize options defaults
    rawray::options::init();

    // Open GLUT window and begin rendering
	atexit( exit_cleanup );
	rawray::GlutWindow::Create(&argc, argv);

    // This will only return if we are in headless mode
	rawray::g_window->MainLoop();

	return 0;
}
