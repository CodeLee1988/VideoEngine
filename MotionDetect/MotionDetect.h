
// MotionDetect.h : PROJECT_NAME Ӧ�ó������ͷ�ļ�
//

#pragma once

#ifndef __AFXWIN_H__
	#error "�ڰ������ļ�֮ǰ������stdafx.h�������� PCH �ļ�"
#endif

#include "resource.h"		// ������


// CMotionDetectApp:
// �йش����ʵ�֣������ MotionDetect.cpp
//

class CMotionDetectApp : public CWinApp
{
public:
	CMotionDetectApp();

// ��д
public:
	virtual BOOL InitInstance();

// ʵ��

	DECLARE_MESSAGE_MAP()
};

extern CMotionDetectApp theApp;