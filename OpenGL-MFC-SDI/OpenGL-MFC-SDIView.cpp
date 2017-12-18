
// OpenGL-MFC-SDIView.cpp : implementation of the COpenGLMFCSDIView class
//

#include "stdafx.h"
// SHARED_HANDLERS can be defined in an ATL project implementing preview, thumbnail
// and search filter handlers and allows sharing of document code with that project.
#ifndef SHARED_HANDLERS
#include "OpenGL-MFC-SDI.h"
#endif

#include "OpenGL-MFC-SDIDoc.h"
#include "OpenGL-MFC-SDIView.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// COpenGLMFCSDIView

IMPLEMENT_DYNCREATE(COpenGLMFCSDIView, CView)

BEGIN_MESSAGE_MAP(COpenGLMFCSDIView, CView)
	// Standard printing commands
	ON_COMMAND(ID_FILE_PRINT, &CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_DIRECT, &CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_PREVIEW, &COpenGLMFCSDIView::OnFilePrintPreview)
	ON_WM_CONTEXTMENU()
	ON_WM_RBUTTONUP()
	ON_WM_CREATE()
	ON_WM_DESTROY()
	ON_WM_ERASEBKGND()
END_MESSAGE_MAP()

// COpenGLMFCSDIView construction/destruction

COpenGLMFCSDIView::COpenGLMFCSDIView()
{
	// TODO: add construction code here

}

COpenGLMFCSDIView::~COpenGLMFCSDIView()
{
}

BOOL COpenGLMFCSDIView::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: Modify the Window class or styles here by modifying
	//  the CREATESTRUCT cs

	return CView::PreCreateWindow(cs);
}

// COpenGLMFCSDIView drawing

void COpenGLMFCSDIView::OnDraw(CDC* /*pDC*/)
{
	COpenGLMFCSDIDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	if (!pDoc)
		return;

	// TODO: add draw code for native data here

	glClearColor(1.0f, 1.0f, 0.0f, 1.0f);
	glClear(GL_COLOR_BUFFER_BIT);
	_GLContent.SwapBuffer();
}


// COpenGLMFCSDIView printing


void COpenGLMFCSDIView::OnFilePrintPreview()
{
#ifndef SHARED_HANDLERS
	AFXPrintPreview(this);
#endif
}

BOOL COpenGLMFCSDIView::OnPreparePrinting(CPrintInfo* pInfo)
{
	// default preparation
	return DoPreparePrinting(pInfo);
}

void COpenGLMFCSDIView::OnBeginPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: add extra initialization before printing
}

void COpenGLMFCSDIView::OnEndPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: add cleanup after printing
}

void COpenGLMFCSDIView::OnRButtonUp(UINT /* nFlags */, CPoint point)
{
	ClientToScreen(&point);
	OnContextMenu(this, point);
}

void COpenGLMFCSDIView::OnContextMenu(CWnd* /* pWnd */, CPoint point)
{
#ifndef SHARED_HANDLERS
	theApp.GetContextMenuManager()->ShowPopupMenu(IDR_POPUP_EDIT, point.x, point.y, this, TRUE);
#endif
}


// COpenGLMFCSDIView diagnostics

#ifdef _DEBUG
void COpenGLMFCSDIView::AssertValid() const
{
	CView::AssertValid();
}

void COpenGLMFCSDIView::Dump(CDumpContext& dc) const
{
	CView::Dump(dc);
}

COpenGLMFCSDIDoc* COpenGLMFCSDIView::GetDocument() const // non-debug version is inline
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(COpenGLMFCSDIDoc)));
	return (COpenGLMFCSDIDoc*)m_pDocument;
}
#endif //_DEBUG


// COpenGLMFCSDIView message handlers


int COpenGLMFCSDIView::OnCreate(LPCREATESTRUCT lpCreateStruct)
{
	if (CView::OnCreate(lpCreateStruct) == -1)
		return -1;

	// TODO:  Add your specialized creation code here

	_GLContent.Begin(m_hWnd);

	return 0;
}


void COpenGLMFCSDIView::OnDestroy()
{
	_GLContent.End();

	CView::OnDestroy();

	// TODO: Add your message handler code here
}


BOOL COpenGLMFCSDIView::OnEraseBkgnd(CDC* pDC)
{
	// TODO: Add your message handler code here and/or call default

	return TRUE; // CView::OnEraseBkgnd(pDC);
}
