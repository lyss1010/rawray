/////////////////////////////////////////////////////////////////////////////
// GUI Entry Point : rawray_gui.h
//
/////////////////////////////////////////////////////////////////////////////
#ifndef RAWRAY_RAWRAY_GUI_RAWRAY_GUI_H
#define RAWRAY_RAWRAY_GUI_RAWRAY_GUI_H
#include "stdafx.h"


/////////////////////////////////////////////////////////////////////////////
// Includes
/////////////////////////////////////////////////////////////////////////////
#include "resource.h"


/////////////////////////////////////////////////////////////////////////////
// Public Function Prototypes
/////////////////////////////////////////////////////////////////////////////
ATOM				MyRegisterClass(HINSTANCE hInstance);
BOOL				InitInstance(HINSTANCE, int);
LRESULT CALLBACK	WndProc(HWND, UINT, WPARAM, LPARAM);
LRESULT CALLBACK	About(HWND, UINT, WPARAM, LPARAM);


#endif // RAWRAY_RAWRAY_GUI_RAWRAY_GUI_H
