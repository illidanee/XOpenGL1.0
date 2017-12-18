
// OpenGL-MFC-SDI.h : main header file for the OpenGL-MFC-SDI application
//
#pragma once

#ifndef __AFXWIN_H__
	#error "include 'stdafx.h' before including this file for PCH"
#endif

#include "resource.h"       // main symbols


// COpenGLMFCSDIApp:
// See OpenGL-MFC-SDI.cpp for the implementation of this class
//

class COpenGLMFCSDIApp : public CWinAppEx
{
public:
	COpenGLMFCSDIApp();


// Overrides
public:
	virtual BOOL InitInstance();
	virtual int ExitInstance();

// Implementation
	UINT  m_nAppLook;
	BOOL  m_bHiColorIcons;

	virtual void PreLoadState();
	virtual void LoadCustomState();
	virtual void SaveCustomState();

	afx_msg void OnAppAbout();
	DECLARE_MESSAGE_MAP()
};

extern COpenGLMFCSDIApp theApp;
