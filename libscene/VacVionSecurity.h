// VacVionCount.h : VacVionCount DLL ����ͷ�ļ�
//

#pragma once

#ifndef __AFXWIN_H__
	#error "�ڰ������ļ�֮ǰ������stdafx.h�������� PCH �ļ�"
#endif


// CVacVionCountApp
// �йش���ʵ�ֵ���Ϣ������� VacVionCount.cpp
//

class CVacVionCountApp : public CWinApp
{
public:
	CVacVionCountApp();

// ��д
public:
	virtual BOOL InitInstance();

	DECLARE_MESSAGE_MAP()
};
