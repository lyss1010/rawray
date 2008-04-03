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

class RenderJob;

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
    void CreateGlutWindow();
    void ToggleRenderGL();

    void MakeSpiralScene();
    void MakeLorenzScene();
    void MakeBunnyScene();
    
    Scene scene_;
    Camera cam_;
    Image img_;
    RenderJob* render_;

    bool renderGL_;
    float keySpeed_;
    float mouseXSpeed_;
    float mouseYSpeed_;
    int activeButton_;
    int mouseX_;
    int mouseY_;

    DISALLOW_IMPLICIT_CONSTRUCTORS(GlutWindow);

}; // class GlutWindow

} // namespace rawray
/////////////////////////////////////////////////////////////////////////////


#endif // RAWRAY_RAWRAY_GLUT_WINDOW_H
