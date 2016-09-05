#pragma once

#include "resource.h"

// ֧�ֵ����ͬʱ����ͨ����
#define MAX_PLAY_CHANNEL 32

class CPVSDialog
{
public:
	CPVSDialog(void);
	virtual ~CPVSDialog(void);

	enum { IDD = IDD_DIALOG_PVS };

	BOOL Create(HWND hParent, int nPlayWnd);
	BOOL Destroy();
	int Show(BOOL bShow);

	inline HWND GetHWnd() const{
		return this->m_hWnd;
	}
	inline HWND* GetPlayHWnd(){
		return this->m_hPlayWnds;
	}

protected:
	HWND m_hParent; // ��������
	HWND m_hWnd; // ������
	HWND m_hPlayWnds[MAX_PLAY_CHANNEL]; // ���Ŵ���������
};
