/////////////////////////////////////////////////////////////////////////////
// glut_window.cpp
//
/////////////////////////////////////////////////////////////////////////////
#include "glut_window.h"
#include "render_job.h"
#include "parser.h"

namespace {

// Proxy callbacks to member functions for GLUT
void Display() { rawray::g_window->Display(); }
void Reshape(int x, int y) { rawray::g_window->Reshape(x, y); }
void Keyboard(uint8 key, int x, int y) { rawray::g_window->Keyboard(key, x, y); }
void Mouse(int btn, int state, int x, int y) { rawray::g_window->Mouse(btn, state, x, y); }
void Motion(int x, int y) { rawray::g_window->Motion(x,y); }
void Idle() { rawray::g_window->Idle(); }

} // namespace

namespace rawray {

// Singleton global window
GlutWindow* g_window = NULL;

const uint8 MOUSE_LEFT   = 1;
const uint8 MOUSE_RIGHT  = 2;
const uint8 MOUSE_MIDDLE = 4;


void GlutWindow::Create(int* argc, char* argv[]) {
	if( !g_window )
		g_window = new GlutWindow(argc, argv);
}

GlutWindow::GlutWindow(int* argc, char* argv[]) : cam_(), img_(), scene_(),
    renderGL_(true), keySpeed_(0.03f), mouseXSpeed_(0.08f), mouseYSpeed_(0.025f),
    activeButton_(0), mouseX_(0), mouseY_(0), render_(NULL)
{
    SetConfigSources(&scene_, &cam_, &img_);
    MakeScene(argc,argv);
    scene_.PreCalc();

    if( options::global::headless ) {
        // Begin render immediately w/o user interaction
        ToggleRenderGL();

        if( !render_ )
            std::cout << "ERROR: Could not create render job" << std::endl;
        else {
            // Wait for render to finish, printing out current progress along the way
            while( render_->IsRendering() ) {
                std::cout << "Progress: " << render_->Progress() << "\r";
                Sleep( 100 );
            }

            // Wait for post processing to finish
            while( !render_->IsDone() ) {
                Sleep( 100 );
            }
        }

    } else {
        // Initialize GLUT and begin GL Rendering
        glutInit(argc, argv);

        CreateGlutWindow();
        InitGL();
        InitCallbacks();
    }
}

GlutWindow::~GlutWindow() {
	delete render_;
}

void GlutWindow::MainLoop() {
    if( options::global::headless )
        return;

    // This will never return
    glutMainLoop(); 
	assert( 0 );
}

void GlutWindow::Display() {
    if( renderGL_ ) {
        cam_.RenderGL();
        scene_.RenderGL();

        glutSwapBuffers();
    } else {
        cam_.RenderImage();
        img_.RenderGL();
    }
    
    glFinish();
}

void GlutWindow::Reshape(int x, int y) {
    // Ignore resize in raytrace mode
    if( !renderGL_ )
        return;

    if( x < 0 ) x = -x;
    else if( x == 0 ) x = 1;

    if( y < 0 ) y = -y;
    else if( y == 0 ) y = 1;

	cam_.Resize( x, y );
    img_.Resize( x, y );
    glViewport( 0, 0, x, y );

    img_.ScreenShot();
}

void GlutWindow::Keyboard(uint8 key, int x, int y) {
    UNREFERENCED_PARAMETER(x);
    UNREFERENCED_PARAMETER(y);

    Vector3 v;
    bool need_display_update = true;

    switch (key) {
    case 27:
        exit(0);
        break;

    case 'c':
    case 'C':
        std::cout << "Camera Pos: " << cam_.GetEye() << std::endl;
		std::cout << "View Direc: " << cam_.GetViewDir() << std::endl;
        break;

    case 'i':
    case 'I':
        if (renderGL_)
            img_.ScreenShot();

        img_.WritePPM();
        break;

	case 'o':
	case 'O':
		WriteAlphaImage();
		break;

    case 'r':
    case 'R':
        ToggleRenderGL();
        break;

    case '+':
        keySpeed_ *= 1.5f;
        mouseXSpeed_ *= 1.5f;
        mouseYSpeed_ *= 1.5f;
        break;

    case '-':
        keySpeed_ /= 1.5f;
        mouseXSpeed_ /= 1.5f;
        mouseYSpeed_ /= 1.5f;
        break;

    case 'w':
    case 'W':
        cam_.SetEye( cam_.GetEye() + keySpeed_*cam_.GetViewDir() );
        break;

    case 's':
    case 'S':
        cam_.SetEye( cam_.GetEye() - keySpeed_*cam_.GetViewDir() );
        break;

    case 'q':
    case 'Q':
        cam_.SetEye( cam_.GetEye() + keySpeed_*cam_.GetUp() );
        break;

    case 'z':
    case 'Z':
        cam_.SetEye( cam_.GetEye() - keySpeed_*cam_.GetUp() );
        break;

    case 'a':
    case 'A':
        math::Cross( cam_.GetViewDir(), cam_.GetUp(), v );
        cam_.SetEye( cam_.GetEye() - keySpeed_*v );
        break;

    case 'd':
    case 'D':
        math::Cross( cam_.GetViewDir(), cam_.GetUp(), v );
        cam_.SetEye( cam_.GetEye() + keySpeed_*v );
        break;

    default:
        need_display_update = false;
    }

    if( need_display_update )
        glutPostRedisplay();
}

void GlutWindow::Mouse(int btn, int state, int x, int y) {
    uint32 buttonMask;

    switch (btn) {
    case GLUT_LEFT_BUTTON:
        buttonMask = MOUSE_LEFT;
        break;

    case GLUT_RIGHT_BUTTON:
        buttonMask = MOUSE_RIGHT;
        break;

    case GLUT_MIDDLE_BUTTON:
        buttonMask = MOUSE_MIDDLE;
        break;

    default:
        buttonMask = 0;
    }

    if (state==GLUT_DOWN) {
        mouseX_ = x;
        mouseY_ = y;
        activeButton_ |= buttonMask; // Flip button bit on
    } else
        activeButton_ &= ~buttonMask; // Flip button bit off
}

void GlutWindow::Motion(int x, int y) {
    int dx = x - mouseX_;
    int dy = y - mouseY_;

	if (renderGL_) {
		if( activeButton_ & MOUSE_LEFT ) {
			Vector3 viewDir = cam_.GetViewDir();
			Vector3 right; math::Cross( viewDir, cam_.GetUp(), right );

			viewDir.Rotate( -mouseYSpeed_*dy*math::DEG_TO_RAD, right );
			viewDir.Rotate( -mouseXSpeed_*dx*math::DEG_TO_RAD, cam_.GetUp() );
			cam_.SetViewDir(viewDir);
		} else if( activeButton_ & MOUSE_RIGHT ) {
			Vector3 up = cam_.GetUp();
			up.Rotate( mouseXSpeed_*dx*math::DEG_TO_RAD, cam_.GetViewDir() );
			cam_.SetUp(up);
		}

        glutPostRedisplay();
    }

    mouseX_ = x;
    mouseY_ = y;
}

void GlutWindow::Idle() {
    if( !renderGL_ ) {
        glutPostRedisplay();

        //if( render_ && !render_->IsDone() )
            //std::cout << "Raytrace Progress: " << (int)render_->Progress() << "%\r" << std::flush;
    }
}

void GlutWindow::InitGL() {
    glClearColor( options::global::gl_bg_color.x, 
                  options::global::gl_bg_color.y, 
                  options::global::gl_bg_color.z, 
                  1.0f );

    glClearDepth( 1.0f );
    glDepthFunc( GL_LEQUAL );
    glEnable( GL_DEPTH_TEST );

    glDisable( GL_LIGHTING );
    glDisable( GL_TEXTURE_2D );

    glShadeModel( GL_SMOOTH );
    glFrontFace( GL_FRONT );
    //glEnable( GL_CULL_FACE );

	glPolygonMode( GL_FRONT, GL_LINE );
    glPolygonMode( GL_BACK, GL_POINT );

    glHint( GL_PERSPECTIVE_CORRECTION_HINT, GL_NICEST );
}

void GlutWindow::ReInitGL() {
	if( img_.GetWidth() > 0 && img_.GetHeight() > 0 )
		glutReshapeWindow( img_.GetWidth(), img_.GetHeight() );

    glClearColor( options::global::gl_bg_color.x, 
                  options::global::gl_bg_color.y, 
                  options::global::gl_bg_color.z, 
                  1.0f );
}

void GlutWindow::InitCallbacks() {
    glutDisplayFunc( ::Display );
    glutKeyboardFunc( ::Keyboard );
    glutMouseFunc( ::Mouse );
    glutMotionFunc( ::Motion );
    glutReshapeFunc( ::Reshape );
    glutIdleFunc( ::Idle );
}

void GlutWindow::CreateGlutWindow() {
    glutInitDisplayMode( GLUT_RGB | GLUT_DOUBLE );
    glutInitWindowSize( options::global::win_width, options::global::win_height );
    glutInitWindowPosition( options::global::win_posX, options::global::win_posY );
	glutCreateWindow( "RawRay" );
}

void GlutWindow::ToggleRenderGL() {
    renderGL_ = !renderGL_;

    // Clean up any old ray trace jobs
    SAFE_DELETE( render_ );

    if( !renderGL_ ) {
        //img_.ScreenShot();
        //img_.GaussianBlur(options::global::gaussian_blur_sigma);

		// We have to black out the image before raytracing so we can use addition for anti aliasing
		img_.Clear( Vector4(0) );

		if( scene_.GetObjects().size() > 0 ) {
			render_ = new RenderJob( options::global::num_threads, 
									scene_, cam_, img_, 
									options::global::aax, options::global::aay);

			render_->Run();
		}
    }
	
    if( !options::global::headless )
        glutPostRedisplay();
}

void GlutWindow::WriteAlphaImage() {
	Image* alpha = img_.CreateAlphaImage();
	alpha->WritePPM();
	delete alpha;
}

} // namespace rawray
