// rawray_gui.cpp : Defines the class behaviors for the application.
//

#include "stdafx.h"
#include "rawray_gui.h"
#include "rawray_guiDlg.h"
#include ".\rawray_gui.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// Crawray_guiApp

BEGIN_MESSAGE_MAP(Crawray_guiApp, CWinApp)
	ON_COMMAND(ID_HELP, CWinApp::OnHelp)
    ON_COMMAND(ID_FILE_EXIT, OnFileExit)
    ON_COMMAND(ID_HELP_ABOUT, OnHelpAbout)
END_MESSAGE_MAP()


// Crawray_guiApp construction

Crawray_guiApp::Crawray_guiApp()
{
	// TODO: add construction code here,
	// Place all significant initialization in InitInstance
}


// The one and only Crawray_guiApp object

Crawray_guiApp theApp;


// Crawray_guiApp initialization

BOOL Crawray_guiApp::InitInstance()
{
	// InitCommonControls() is required on Windows XP if an application
	// manifest specifies use of ComCtl32.dll version 6 or later to enable
	// visual styles.  Otherwise, any window creation will fail.
	InitCommonControls();

	CWinApp::InitInstance();

	// Standard initialization
	// If you are not using these features and wish to reduce the size
	// of your final executable, you should remove from the following
	// the specific initialization routines you do not need
	// Change the registry key under which our settings are stored
	// TODO: You should modify this string to be something appropriate
	// such as the name of your company or organization
	SetRegistryKey(_T("Local AppWizard-Generated Applications"));

	Crawray_guiDlg dlg;
	m_pMainWnd = &dlg;
	INT_PTR nResponse = dlg.DoModal();

	// Since the dialog has been closed, return FALSE so that we exit the
	//  application, rather than start the application's message pump.
	return FALSE;
}

void Crawray_guiApp::OnFileExit()
{
    exit(0);
}

void Crawray_guiApp::OnHelpAbout()
{
    // TODO: Add your command handler code here

}
