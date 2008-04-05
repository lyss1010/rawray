// rawray_gui.h : main header file for the PROJECT_NAME application
//

#pragma once

#ifndef __AFXWIN_H__
	#error include 'stdafx.h' before including this file for PCH
#endif

#include "resource.h"		// main symbols


// Crawray_guiApp:
// See rawray_gui.cpp for the implementation of this class
//

class Crawray_guiApp : public CWinApp
{
public:
	Crawray_guiApp();

// Overrides
	public:
	virtual BOOL InitInstance();

// Implementation

	DECLARE_MESSAGE_MAP()
    afx_msg void OnFileExit();
    afx_msg void OnHelpAbout();
};

extern Crawray_guiApp theApp;