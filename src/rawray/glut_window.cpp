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
#include "time.h"

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
    renderGL_(true), movementSpeed_(0.1f), activeButton_(0), 
    mouseX_(0), mouseY_(0)
    
{
    glutInit(argc, argv);

    CreateWindow();
    InitGL();
    InitCallbacks();

    //MakeSpiralScene();
    MakeBunnyScene();
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
        if( cam_.RenderImage(img_) )
            scene_.Raytrace(cam_, img_);
        
        img_.RenderGL();
    }
    
    glFinish();
}

void GlutWindow::Reshape(int x, int y) {
    if( x < 0 ) x = -x;
    else if( x == 0 ) x = 1;

    if( y < 0 ) y = -y;
    else if( y == 0 ) y = 1;

    img_.Resize( (uint32)x, (uint32)y );
    glViewport( 0, 0, x, y );

    renderGL_ = true;
    glutPostRedisplay();
}

void GlutWindow::Keyboard(uint8 key, int x, int y) {
    UNREFERENCED_PARAMETER(x);
    UNREFERENCED_PARAMETER(y);

    bool displayNeedsUpdate = true;

    switch (key) {
    case 27:
        exit(0);
        break;

    case 'i':
    case 'I':
        char str[1024];
        sprintf(str, "miro_%d.ppm", time(0));
        if (renderGL_) {
            uint8* buf = new uint8[ img_.GetWidth()*img_.GetHeight()*3 ];
            glReadPixels( 0, 0, img_.GetWidth(), img_.GetHeight(), GL_RGB, GL_UNSIGNED_BYTE, buf );
            img_.WritePPM( str, buf, img_.GetWidth(), img_.GetHeight() );
        } else {
            img_.WritePPM( str );
        }
        break;

    case 'r':
    case 'R':
        renderGL_ = !renderGL_;
        break;

    case '+':
        movementSpeed_ *= 1.5f;
        break;

    case '-':
        movementSpeed_ /= 1.5f;
        break;

    case 'w':
    case 'W':
        cam_.SetEye( cam_.GetEye() + movementSpeed_*cam_.GetViewDir() );
        break;

    case 's':
    case 'S':
        cam_.SetEye( cam_.GetEye() - movementSpeed_*cam_.GetViewDir() );
        break;

    case 'q':
    case 'Q':
        cam_.SetEye( cam_.GetEye() + movementSpeed_*cam_.GetUp() );
        break;

    case 'z':
    case 'Z':
        cam_.SetEye( cam_.GetEye() - movementSpeed_*cam_.GetUp() );
        break;

    case 'a':
    case 'A':
        cam_.SetEye( cam_.GetEye() - movementSpeed_*math::Cross( cam_.GetViewDir(), cam_.GetUp() ) );
        break;

    case 'd':
    case 'D':
        cam_.SetEye( cam_.GetEye() + movementSpeed_*math::Cross( cam_.GetViewDir(), cam_.GetUp() ) );
        break;

    default:
        displayNeedsUpdate = false;
    }

    if (displayNeedsUpdate)
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
    bool displayNeedsUpdate = false;
    int dx = x - mouseX_;
    int dy = y - mouseY_;

    if (activeButton_ & MOUSE_LEFT) {
        Vector3 viewDir = cam_.GetViewDir();
        Vector3 right = math::Cross(viewDir, cam_.GetUp());

        viewDir.Rotate( -dx*math::DEG_TO_RAD, right );
        viewDir.Rotate( -dy*math::DEG_TO_RAD, cam_.GetUp() );
        cam_.SetViewDir(viewDir);

        displayNeedsUpdate = true;
    }

    mouseX_ = x;
    mouseY_ = y;

    if (displayNeedsUpdate)
        glutPostRedisplay();
}

void GlutWindow::Idle() {
}

void GlutWindow::InitGL() {
    glClearColor( options::bg_color.x, options::bg_color.y, options::bg_color.z, 1.0f );
    glClearDepth( 1.0f );
    glDepthFunc( GL_LEQUAL );
    glEnable( GL_DEPTH_TEST );

    glDisable( GL_LIGHTING );
    glDisable( GL_TEXTURE_2D );

    glShadeModel( GL_SMOOTH );
    glPolygonMode( GL_FRONT_AND_BACK, GL_FILL );

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

void GlutWindow::CreateWindow() {
    glutInitWindowSize( options::win_width, options::win_height );
    glutInitDisplayMode( GLUT_RGB | GLUT_DOUBLE );
    glutInitWindowPosition( options::win_posX, options::win_posY );
    glutCreateWindow( options::win_name.c_str() );
}

void GlutWindow::MakeSpiralScene() {
    img_.Resize(512, 512);

    cam_.SetEye( Vector3(-5, 2, 3) );
    cam_.SetLookAt( Vector3(0, 0, 0) );
    cam_.SetUp( Vector3(0, 1, 0) );
    cam_.SetFOV( 45 );

    Light* light = new Light( Vector3(-3,15,3),
                              Vector3(1,1,1),
                              1000 );
    scene_.AddLight(light);

    Material* mat = new Lambert( Vector3(1,0,0) );
    const int maxI = 200;
    const float a = 0.15f;
    for (int i=0; i<maxI; ++i ) {
        float t = i/float(maxI);
        float theta = 4 * math::PI * t;
        float r = a*theta;
        float x = r*cos(theta);
        float y = r*sin(theta);
        float z = 2 * ( 2 * math::PI * a - r);

        rawray::Sphere * sphere = new Sphere( Vector3(x,y,z), r/10, mat );
        scene_.AddObject(sphere);
    }

    scene_.PreCalc();
}

void GlutWindow::MakeBunnyScene() {
    img_.Resize(128, 128);
    
    // set up the camera
    options::bg_color = Vector3(0.0f, 0.0f, 0.2f);

    cam_.SetEye( Vector3(-2, 3, 5) );
    cam_.SetLookAt( Vector3(-0.5f, 1, 0) );
    cam_.SetUp( Vector3(0, 1, 0) );
    cam_.SetFOV( 45 );

    Light* light = new Light( Vector3(-3, 15, 3),
                          Vector3(1,1,1),
                          500 );
    scene_.AddLight(light);

    Material* mat = new Lambert( Vector3(1,1,1) );

    TriangleMesh* bunny = new TriangleMesh;
    bunny->LoadOBJ( "D:\\Documents\\Documents\\Visual Studio 2008\\Projects\\rawray\\res\\bunny.obj" );
    
    // create all the triangles in the bunny mesh and add to the scene
    for (uint32 i = 0; i < bunny->GetNumTriangles(); ++i)
    {
        Triangle* t = new Triangle( *bunny, i, mat );
        scene_.AddObject(t);
    }
    
    scene_.PreCalc();
}

} // namespace rawray