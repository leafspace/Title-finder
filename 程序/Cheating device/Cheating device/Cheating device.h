
// Cheating device.h : PROJECT_NAME Ӧ�ó������ͷ�ļ�
//

#pragma once

#ifndef __AFXWIN_H__
	#error "�ڰ������ļ�֮ǰ������stdafx.h�������� PCH �ļ�"
#endif

#include "resource.h"		// ������


// CCheatingdeviceApp: 
// �йش����ʵ�֣������ Cheating device.cpp
//

class CCheatingdeviceApp : public CWinApp
{
public:
	CCheatingdeviceApp();

// ��д
public:
	virtual BOOL InitInstance();

// ʵ��

	DECLARE_MESSAGE_MAP()
};

extern CCheatingdeviceApp theApp;