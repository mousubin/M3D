
// MRenderTest_MFC.h : MRenderTest_MFC Ӧ�ó������ͷ�ļ�
//
#pragma once

#ifndef __AFXWIN_H__
	#error "�ڰ������ļ�֮ǰ������stdafx.h�������� PCH �ļ�"
#endif

#include "resource.h"       // ������


// CMRenderTest_MFCApp:
// �йش����ʵ�֣������ MRenderTest_MFC.cpp
//

class CMRenderTest_MFCApp : public CWinAppEx
{
public:
	CMRenderTest_MFCApp();


// ��д
public:
	virtual BOOL InitInstance();
	virtual int ExitInstance();

// ʵ��

public:
	BOOL  m_bHiColorIcons;

	virtual void PreLoadState();
	virtual void LoadCustomState();
	virtual void SaveCustomState();

	afx_msg void OnAppAbout();
	DECLARE_MESSAGE_MAP()
};

extern CMRenderTest_MFCApp theApp;
