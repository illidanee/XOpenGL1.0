
// OpenGLES2.0-MFC-Dialog.h : main header file for the PROJECT_NAME application
//

#pragma once

#ifndef __AFXWIN_H__
	#error "include 'stdafx.h' before including this file for PCH"
#endif

#include "resource.h"		// main symbols


// COpenGLES20MFCDialogApp:
// See OpenGLES2.0-MFC-Dialog.cpp for the implementation of this class
//

class COpenGLES20MFCDialogApp : public CWinApp
{
public:
	COpenGLES20MFCDialogApp();

// Overrides
public:
	virtual BOOL InitInstance();

// Implementation

	DECLARE_MESSAGE_MAP()
};

extern COpenGLES20MFCDialogApp theApp;