
// CalendarUI.h : PROJECT_NAME Ӧ�ó������ͷ�ļ�
//

#pragma once

#ifndef __AFXWIN_H__
	#error "�ڰ������ļ�֮ǰ������stdafx.h�������� PCH �ļ�"
#endif

#include "resource.h"		// ������


// CCalendarUIApp: 
// �йش����ʵ�֣������ CalendarUI.cpp
//

class CCalendarUIApp : public CWinApp
{
public:
	CCalendarUIApp();

// ��д
public:
	virtual BOOL InitInstance();

// ʵ��

	DECLARE_MESSAGE_MAP()
};

extern CCalendarUIApp theApp;
