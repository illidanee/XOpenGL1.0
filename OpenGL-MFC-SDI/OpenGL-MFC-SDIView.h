
// OpenGL-MFC-SDIView.h : interface of the COpenGLMFCSDIView class
//

#pragma once

#include "XGLContent.h"

class COpenGLMFCSDIView : public CView
{
protected: // create from serialization only
	COpenGLMFCSDIView();
	DECLARE_DYNCREATE(COpenGLMFCSDIView)

// Attributes
public:
	COpenGLMFCSDIDoc* GetDocument() const;

// Operations
public:

// Overrides
public:
	virtual void OnDraw(CDC* pDC);  // overridden to draw this view
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
protected:
	virtual BOOL OnPreparePrinting(CPrintInfo* pInfo);
	virtual void OnBeginPrinting(CDC* pDC, CPrintInfo* pInfo);
	virtual void OnEndPrinting(CDC* pDC, CPrintInfo* pInfo);

// Implementation
public:
	virtual ~COpenGLMFCSDIView();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// Generated message map functions
protected:
	afx_msg void OnFilePrintPreview();
	afx_msg void OnRButtonUp(UINT nFlags, CPoint point);
	afx_msg void OnContextMenu(CWnd* pWnd, CPoint point);
	DECLARE_MESSAGE_MAP()
public:
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
	afx_msg void OnDestroy();
	afx_msg BOOL OnEraseBkgnd(CDC* pDC);

private:
	Smile::XGLContent _GLContent;
};

#ifndef _DEBUG  // debug version in OpenGL-MFC-SDIView.cpp
inline COpenGLMFCSDIDoc* COpenGLMFCSDIView::GetDocument() const
   { return reinterpret_cast<COpenGLMFCSDIDoc*>(m_pDocument); }
#endif

