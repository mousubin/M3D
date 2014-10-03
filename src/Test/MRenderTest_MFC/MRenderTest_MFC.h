
// MRenderTest_MFC.h : MRenderTest_MFC 应用程序的主头文件
//
#pragma once

#ifndef __AFXWIN_H__
	#error "在包含此文件之前包含“stdafx.h”以生成 PCH 文件"
#endif

#include "resource.h"       // 主符号


// CMRenderTest_MFCApp:
// 有关此类的实现，请参阅 MRenderTest_MFC.cpp
//

class CMRenderTest_MFCApp : public CWinAppEx
{
public:
	CMRenderTest_MFCApp();


// 重写
public:
	virtual BOOL InitInstance();
	virtual int ExitInstance();

// 实现

public:
	BOOL  m_bHiColorIcons;

	virtual void PreLoadState();
	virtual void LoadCustomState();
	virtual void SaveCustomState();

	afx_msg void OnAppAbout();
	DECLARE_MESSAGE_MAP()
};

extern CMRenderTest_MFCApp theApp;
