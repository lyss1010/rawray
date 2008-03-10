/////////////////////////////////////////////////////////////////////////////
// Class : glut_window.h
//
/////////////////////////////////////////////////////////////////////////////
#ifndef RAWRAY_RAWRAY_GLUT_WINDOW_H
#define RAWRAY_RAWRAY_GLUT_WINDOW_H
#include "stdafx.h"
#include "image.h"
#include "camera.h"
#include "scene.h"

/////////////////////////////////////////////////////////////////////////////
namespace rawray {

class DllExport GlutWindow
{
public:
    GlutWindow(int* argc, char* argv[]);
    ~GlutWindow() { }

    void MainLoop();

    void Display();
    void Reshape(int x, int y);
    void Keyboard(uint8 key, int x, int y);
    void Mouse(int btn, int state, int x, int y);
    void Motion(int x, int y);
    void Idle();

private:
    void InitGL();
    void InitCallbacks();
    void CreateWindow();

    void MakeSpiralScene();
    void MakeBunnyScene();
    
    Scene scene_;
    Camera cam_;
    Image img_;

    bool renderGL_;
    float movementSpeed_;
    int activeButton_;
    int mouseX_;
    int mouseY_;

    DISALLOW_IMPLICIT_CONSTRUCTORS(GlutWindow);

}; // class GlutWindow

} // namespace rawray
/////////////////////////////////////////////////////////////////////////////


#endif // RAWRAY_RAWRAY_GLUT_WINDOW_H
