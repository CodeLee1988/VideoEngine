#pragma once


// CPresetSetting �Ի���
#include "resource.h"

class CPresetSetting : public CDialog
{
	DECLARE_DYNAMIC(CPresetSetting)

public:
	CPresetSetting(CWnd* pParent = NULL);   // ��׼���캯��
	virtual ~CPresetSetting();

// �Ի�������
	enum { IDD = IDD_PRESET };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnBnClickedBtnContinue();
	afx_msg void OnBnClickedBtnCancel();
	int m_nPreset;
};
