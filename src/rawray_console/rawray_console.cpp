/////////////////////////////////////////////////////////////////////////////
// Console Entry Point : rawray_console.cpp
//
/////////////////////////////////////////////////////////////////////////////
#include "rawray_console.h"
#include "rawray/glut_window.h"
#include "rawray/options.h"
#include "tools/sse.h"


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

    //std::cout << vec1.x << " " << vec1.y << " " << vec1.z << '\n';
}

void SSETest() {
    std::cout << "Testing SSE Version... ";
    switch( tools::sse::GetVersion() ) {
    case tools::sse::SSE1:
        std::cout << "SSE" << std::endl;
        break;

    case tools::sse::SSE2:
        std::cout << "SSE2" << std::endl;
        break;
    
    case tools::sse::SSE3:
        std::cout << "SSE3" << std::endl;
        break;
    
    case tools::sse::SSSE3:
        std::cout << "SSSE3" << std::endl;
        break;
            
    case tools::sse::SSE4_1:
        std::cout << "SSE4.1" << std::endl;
        break;
            
    case tools::sse::SSE4_2:
        std::cout << "SSE4.2" << std::endl;
        break;
    }
}

// Console Entry point
int _tmain( int argc, _TCHAR* argv[] )
{
	// Enable memory leak messages on exit
	_CrtSetDbgFlag ( _CRTDBG_ALLOC_MEM_DF );
	//_CrtSetBreakAlloc( 143 );

    SSETest();
    VectorTest();
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
