
// ChildView.h : CChildView 类的接口
//


#pragma once


#include "render/Render.h"

// CChildView 窗口

class CChildView : public CWnd
{
// 构造
public:
	CChildView();

// 特性
public:
	bool _bInit;
	HGLRC _hRC;
	mrd::Render *_rd;
// 操作
public:
	bool initGL(HDC hDC);
	bool setupPixelFormat(HDC hDC);
// 重写
	protected:
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);

// 实现
public:
	virtual ~CChildView();

	// 生成的消息映射函数
protected:
	afx_msg void OnPaint();
	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnTimer(UINT_PTR nIDEvent);
	afx_msg BOOL OnEraseBkgnd(CDC* pDC);
};

