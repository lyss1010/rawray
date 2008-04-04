/////////////////////////////////////////////////////////////////////////////
// glut_window.cpp
//
/////////////////////////////////////////////////////////////////////////////
#include "glut_window.h"
#include "light.h"
#include "lambert.h"
#include "sphere.h"
#include "triangle_mesh.h"
#include "triangle.h"
#include "render_job.h"

namespace {

// Proxy callbacks to member functions for GLUT
rawray::GlutWindow* g_window;
void Display() { g_window->Display(); }
void Reshape(int x, int y) { g_window->Reshape(x, y); }
void Keyboard(uint8 key, int x, int y) { g_window->Keyboard(key, x, y); }
void Mouse(int btn, int state, int x, int y) { g_window->Mouse(btn, state, x, y); }
void Motion(int x, int y) { g_window->Motion(x,y); }
void Idle() { g_window->Idle(); }

} // namespace


namespace rawray {

const uint8 MOUSE_LEFT   = 1;
const uint8 MOUSE_RIGHT  = 2;
const uint8 MOUSE_MIDDLE = 4;

GlutWindow::GlutWindow(int* argc, char* argv[]) : cam_(), img_(), scene_(),
    renderGL_(true), keySpeed_(0.1f), mouseXSpeed_(0.1f), mouseYSpeed_(0.03f),
    activeButton_(0), mouseX_(0), mouseY_(0), render_(NULL)
    
{
    glutInit(argc, argv);

    CreateGlutWindow();
    InitGL();
    InitCallbacks();

    MakeSpiralScene();
    //MakeBunnyScene();
}

void GlutWindow::MainLoop() {
    glutMainLoop();
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
    // Come out of raytrace mode if needed
    if( !renderGL_ )
        ToggleRenderGL();

    if( x < 0 ) x = -x;
    else if( x == 0 ) x = 1;

    if( y < 0 ) y = -y;
    else if( y == 0 ) y = 1;

    img_.Resize( (uint32)x, (uint32)y );
    glViewport( 0, 0, x, y );

    img_.ScreenShot();
}

void GlutWindow::Keyboard(uint8 key, int x, int y) {
    UNREFERENCED_PARAMETER(x);
    UNREFERENCED_PARAMETER(y);

    bool need_display_update = true;

    switch (key) {
    case 27:
        exit(0);
        break;

    case 'c':
    case 'C':
        std::cout << "Camera Pos: " << cam_.GetEye() << std::endl;
        break;

    case 'i':
    case 'I':
        if (renderGL_)
            img_.ScreenShot();

        img_.WritePPM();
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
        cam_.SetEye( cam_.GetEye() - keySpeed_*math::Cross( cam_.GetViewDir(), cam_.GetUp() ) );
        break;

    case 'd':
    case 'D':
        cam_.SetEye( cam_.GetEye() + keySpeed_*math::Cross( cam_.GetViewDir(), cam_.GetUp() ) );
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

    if (renderGL_ && activeButton_ & MOUSE_LEFT) {
        Vector3 viewDir = cam_.GetViewDir();
        Vector3 right = math::Cross(viewDir, cam_.GetUp());

        viewDir.Rotate( -mouseYSpeed_*dy*math::DEG_TO_RAD, right );
        viewDir.Rotate( -mouseXSpeed_*dx*math::DEG_TO_RAD, cam_.GetUp() );
        cam_.SetViewDir(viewDir);

        glutPostRedisplay();
    }

    mouseX_ = x;
    mouseY_ = y;
}

void GlutWindow::Idle() {
    if( !renderGL_ ) {
        glutPostRedisplay();

        if( render_ && !render_->IsDone() )
            std::cout << "Raytrace Progress: " << (int)render_->Progress() << "%\r" << std::flush;
    }
}

void GlutWindow::InitGL() {
    glClearColor( options::gl_bg_color.x, options::gl_bg_color.y, options::gl_bg_color.z, 1.0f );
    glClearDepth( 1.0f );
    glDepthFunc( GL_LEQUAL );
    glEnable( GL_DEPTH_TEST );

    glDisable( GL_LIGHTING );
    glDisable( GL_TEXTURE_2D );

    glShadeModel( GL_SMOOTH );
    glFrontFace( GL_FRONT );
    //glEnable( GL_CULL_FACE );

	glPolygonMode( GL_FRONT, GL_FILL );
    glPolygonMode( GL_BACK, GL_POINT );

    glHint( GL_PERSPECTIVE_CORRECTION_HINT, GL_NICEST );
}

void GlutWindow::InitCallbacks() {
    ::g_window = this;
    glutDisplayFunc( ::Display );
    glutKeyboardFunc( ::Keyboard );
    glutMouseFunc( ::Mouse );
    glutMotionFunc( ::Motion );
    glutReshapeFunc( ::Reshape );
    glutIdleFunc( ::Idle );
}

void GlutWindow::CreateGlutWindow() {
    glutInitWindowSize( options::win_width, options::win_height );
    glutInitDisplayMode( GLUT_RGB | GLUT_DOUBLE );
    glutInitWindowPosition( options::win_posX, options::win_posY );
    glutCreateWindow( options::win_name.c_str() );
}

void GlutWindow::ToggleRenderGL() {
    renderGL_ = !renderGL_;

    // Clean up any old ray trace jobs
    SAFE_DELETE( render_ );

    if( !renderGL_ ) {
        // We set the un-raytraced pixels to be the a blurred opengl render
        img_.ScreenShot();
        img_.GaussianBlur(0.75f);

        render_ = new RenderJob(options::num_threads, scene_, cam_, img_);
        render_->Run();
    }

    glutPostRedisplay();
}

void GlutWindow::MakeSpiralScene() {
    //cam_.SetEye( Vector3(-5.0f, 2.0f, 3.0f) );
    cam_.SetEye( Vector3(1.73f, -1.23f, -4.04f) );
    cam_.SetLookAt( Vector3(0, 0, 0) );
    cam_.SetUp( Vector3(0, 1, 0) );
    cam_.SetFOV( 45 );

    Light* light = new Light( Vector3(-3, 15, 3),
                              Vector3(1, 1, 1),
                              1000 );
    scene_.AddLight(light);
    
    const int maxI = 200;
    const float a = 0.15f;
    for (int i=0; i<maxI; ++i ) {
        float t = i/float(maxI);
        float theta = 4 * math::PI * t;
        float r = a*theta;

        float x = r*cos(theta);
        float y = r*sin(theta);
        float z = 2 * ( 2 * math::PI * a - r);

        //float red = 0.5f * ( 1.0f + sin(x+y*y-z) );
        //float green = 0.5f * ( 1.0f + sin(theta-z) );
        //float blue = 0.5f * ( 1.0f + tan(r) );

        // NOTE: Memory leak!
        Material* mat = new Lambert( Vector3(1,0,0) );
        rawray::Sphere * sphere = new Sphere( Vector3(x,y,z), r/10, mat );
        scene_.AddObject(sphere);
    }

    scene_.PreCalc();
}

void GlutWindow::MakeLorenzScene() {
    cam_.SetEye( Vector3(-5.0f, 2.0f, 3.0f) );
    cam_.SetLookAt( Vector3(0, 0, 0) );
    cam_.SetUp( Vector3(0, 1, 0) );
    cam_.SetFOV( 45 );

    Light* light = new Light( Vector3(-3, 15, 3),
                              Vector3(1, 1, 1),
                              1000 );
    scene_.AddLight(light);
    
    const int maxI = 200;
    const float a = 0.15f;
    for (int i=0; i<maxI; ++i ) {
        float t = i/float(maxI);
        float theta = 4 * math::PI * t;
        float r = a*theta;
    }

    scene_.PreCalc();
}

void GlutWindow::MakeBunnyScene() {
    // set up the camera
    options::bg_color = Vector3(0.0f, 0.0f, 0.2f);

    cam_.SetEye( Vector3(-2.0f, 3.0f, 5.0f) );
    cam_.SetLookAt( Vector3(-0.5f, 1.0f, 0.0f) );
    cam_.SetUp( Vector3(0, 1, 0) );
    cam_.SetFOV( 45 );

    Light* light = new Light( Vector3(-3, 15, 3),
							  Vector3(1, 1, 1),
							  500 );
    scene_.AddLight(light);

    Material* mat = new Lambert( Vector3(1, 1, 1) );

    TriangleMesh* bunny = new TriangleMesh;
    bunny->LoadOBJ( "./../res/sphere.obj" );
    
    // create all the triangles in the bunny mesh and add to the scene
    for (uint32 i = 0; i < bunny->GetNumTriangles(); ++i)
    {
        Triangle* t = new Triangle( *bunny, i, mat );
        scene_.AddObject(t);
    }
    
    scene_.PreCalc();
}

} // namespace rawray