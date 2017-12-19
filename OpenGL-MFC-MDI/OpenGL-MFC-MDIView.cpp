
// OpenGL-MFC-MDIView.cpp : implementation of the COpenGLMFCMDIView class
//

#include "stdafx.h"
// SHARED_HANDLERS can be defined in an ATL project implementing preview, thumbnail
// and search filter handlers and allows sharing of document code with that project.
#ifndef SHARED_HANDLERS
#include "OpenGL-MFC-MDI.h"
#endif

#include "OpenGL-MFC-MDIDoc.h"
#include "OpenGL-MFC-MDIView.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// COpenGLMFCMDIView

IMPLEMENT_DYNCREATE(COpenGLMFCMDIView, CView)

BEGIN_MESSAGE_MAP(COpenGLMFCMDIView, CView)
	// Standard printing commands
	ON_COMMAND(ID_FILE_PRINT, &CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_DIRECT, &CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_PREVIEW, &COpenGLMFCMDIView::OnFilePrintPreview)
	ON_WM_CONTEXTMENU()
	ON_WM_RBUTTONUP()
	ON_WM_CREATE()
	ON_WM_DESTROY()
	ON_WM_ERASEBKGND()
END_MESSAGE_MAP()

// COpenGLMFCMDIView construction/destruction

COpenGLMFCMDIView::COpenGLMFCMDIView()
{
	// TODO: add construction code here

}

COpenGLMFCMDIView::~COpenGLMFCMDIView()
{
}

BOOL COpenGLMFCMDIView::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: Modify the Window class or styles here by modifying
	//  the CREATESTRUCT cs

	return CView::PreCreateWindow(cs);
}

// COpenGLMFCMDIView drawing

void COpenGLMFCMDIView::OnDraw(CDC* /*pDC*/)
{
	COpenGLMFCMDIDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	if (!pDoc)
		return;

	// TODO: add draw code for native data here
	_GLContent.MakeCurrent();
	glClearColor(1.0f, 1.0f, 0.0f, 1.0f);
	glClear(GL_COLOR_BUFFER_BIT);
	_GLContent.SwapBuffer();
}


// COpenGLMFCMDIView printing


void COpenGLMFCMDIView::OnFilePrintPreview()
{
#ifndef SHARED_HANDLERS
	AFXPrintPreview(this);
#endif
}

BOOL COpenGLMFCMDIView::OnPreparePrinting(CPrintInfo* pInfo)
{
	// default preparation
	return DoPreparePrinting(pInfo);
}

void COpenGLMFCMDIView::OnBeginPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: add extra initialization before printing
}

void COpenGLMFCMDIView::OnEndPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: add cleanup after printing
}

void COpenGLMFCMDIView::OnRButtonUp(UINT /* nFlags */, CPoint point)
{
	ClientToScreen(&point);
	OnContextMenu(this, point);
}

void COpenGLMFCMDIView::OnContextMenu(CWnd* /* pWnd */, CPoint point)
{
#ifndef SHARED_HANDLERS
	theApp.GetContextMenuManager()->ShowPopupMenu(IDR_POPUP_EDIT, point.x, point.y, this, TRUE);
#endif
}


// COpenGLMFCMDIView diagnostics

#ifdef _DEBUG
void COpenGLMFCMDIView::AssertValid() const
{
	CView::AssertValid();
}

void COpenGLMFCMDIView::Dump(CDumpContext& dc) const
{
	CView::Dump(dc);
}

COpenGLMFCMDIDoc* COpenGLMFCMDIView::GetDocument() const // non-debug version is inline
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(COpenGLMFCMDIDoc)));
	return (COpenGLMFCMDIDoc*)m_pDocument;
}
#endif //_DEBUG


// COpenGLMFCMDIView message handlers


int COpenGLMFCMDIView::OnCreate(LPCREATESTRUCT lpCreateStruct)
{
	if (CView::OnCreate(lpCreateStruct) == -1)
		return -1;

	// TODO:  Add your specialized creation code here

	_GLContent.Begin(m_hWnd);

	return 0;
}

void COpenGLMFCMDIView::OnDestroy()
{
	_GLContent.End();

	CView::OnDestroy();

	// TODO: Add your message handler code here
}

BOOL COpenGLMFCMDIView::OnEraseBkgnd(CDC* pDC)
{
	// TODO: Add your message handler code here and/or call default

	return TRUE; // CView::OnEraseBkgnd(pDC);
}
