
// OpenGL-MFC-Dialog.h : main header file for the PROJECT_NAME application
//

#pragma once

#ifndef __AFXWIN_H__
	#error "include 'stdafx.h' before including this file for PCH"
#endif

#include "resource.h"		// main symbols


// COpenGLMFCDialogApp:
// See OpenGL-MFC-Dialog.cpp for the implementation of this class
//

class COpenGLMFCDialogApp : public CWinApp
{
public:
	COpenGLMFCDialogApp();

// Overrides
public:
	virtual BOOL InitInstance();

// Implementation

	DECLARE_MESSAGE_MAP()
};

extern COpenGLMFCDialogApp theApp;