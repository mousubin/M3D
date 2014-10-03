
// ChildView.h : CChildView ��Ľӿ�
//


#pragma once


#include "render/Render.h"

// CChildView ����

class CChildView : public CWnd
{
// ����
public:
	CChildView();

// ����
public:
	bool _bInit;
	HGLRC _hRC;
	mrd::Render *_rd;
// ����
public:
	bool initGL(HDC hDC);
	bool setupPixelFormat(HDC hDC);
// ��д
	protected:
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);

// ʵ��
public:
	virtual ~CChildView();

	// ���ɵ���Ϣӳ�亯��
protected:
	afx_msg void OnPaint();
	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnTimer(UINT_PTR nIDEvent);
	afx_msg BOOL OnEraseBkgnd(CDC* pDC);
};

