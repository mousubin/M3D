
// ChildView.cpp : CChildView 类的实现
//

#include "stdafx.h"
#include "MRenderTest_MFC.h"
#include "ChildView.h"

#include "UnitTest\UnitTestRender.h"
#include "..\MRenderTestShare\T_Render.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CChildView

CChildView::CChildView()
{
	_bInit = false;
}

CChildView::~CChildView()
{
}


BEGIN_MESSAGE_MAP(CChildView, CWnd)
	ON_WM_PAINT()
	ON_WM_TIMER()
	ON_WM_ERASEBKGND()
END_MESSAGE_MAP()



// CChildView 消息处理程序

BOOL CChildView::PreCreateWindow(CREATESTRUCT& cs) 
{
	if (!CWnd::PreCreateWindow(cs))
		return FALSE;

	cs.dwExStyle |= WS_EX_CLIENTEDGE;
	cs.style &= ~WS_BORDER;
	cs.lpszClass = AfxRegisterWndClass(CS_HREDRAW|CS_VREDRAW|CS_DBLCLKS, 
		::LoadCursor(NULL, IDC_ARROW), reinterpret_cast<HBRUSH>(COLOR_WINDOW+1), NULL);

	return TRUE;
}

void CChildView::OnPaint() 
{
	CPaintDC dc(this); // 用于绘制的设备上下文
	
	if (!_bInit) {	
		initGL(dc);
		SetTimer(0, 50, NULL);
	}
	wglMakeCurrent(dc, _hRC);
	MT_RUN;
	/*glClearColor(1, 1, 0, 1);
	glClear(GL_COLOR_BUFFER_BIT);
	glFlush();*/
	SwapBuffers(dc);
	GLenum err = glGetError();
}

bool CChildView::initGL(HDC hDC)
{
	if (_bInit)
		return true;
	_bInit = true;
	if (!setupPixelFormat(hDC))
		return false;
	_hRC = wglCreateContext(hDC);
	wglMakeCurrent(hDC, _hRC);
	GLenum err = glewInit();
	if (err == GLEW_ERROR_NO_GL_VERSION) {
		int i = 0;
	}

	_rd = new mrd::Render;

	MT_CASES
	{
		MT_RENDER_CASE(Shape, _rd);
	}
	return true;
}


bool CChildView::setupPixelFormat(HDC hDC)
{
	PIXELFORMATDESCRIPTOR pixelDesc =
    {
        sizeof(PIXELFORMATDESCRIPTOR),
        1,
        PFD_DRAW_TO_WINDOW|PFD_SUPPORT_OPENGL|PFD_DOUBLEBUFFER|PFD_SUPPORT_GDI,
        PFD_TYPE_RGBA,
        32,
        0,0,0,0,0,0,
        0,
        0,
        0,
        0,0,0,0,
        24,
        8,
        0,
        PFD_MAIN_PLANE,
        0,
        0,0,0
    };

    int pixelIndex = ChoosePixelFormat(hDC,&pixelDesc);
    if (pixelIndex == 0)
    {
        pixelIndex = 1;
        if(DescribePixelFormat(hDC, pixelIndex, sizeof(PIXELFORMATDESCRIPTOR), &pixelDesc) == 0)
        {
            return false;
        }
    }

    if(SetPixelFormat(hDC, pixelIndex, &pixelDesc)==FALSE)
    {
        return false;
    }
	return true;
}


void CChildView::OnTimer(UINT_PTR nIDEvent)
{
	// TODO: 在此添加消息处理程序代码和/或调用默认值
	Invalidate();
	CWnd::OnTimer(nIDEvent);
}


BOOL CChildView::OnEraseBkgnd(CDC* pDC)
{
	// TODO: 在此添加消息处理程序代码和/或调用默认值

	return TRUE;
}
