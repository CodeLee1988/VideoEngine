// PresetSetting.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "VacVionSecurity.h"
#include "PresetSetting.h"
#include "afxdialogex.h"


// CPresetSetting �Ի���

IMPLEMENT_DYNAMIC(CPresetSetting, CDialog)

CPresetSetting::CPresetSetting(CWnd* pParent /*=NULL*/)
	: CDialog(CPresetSetting::IDD, pParent)
	, m_nPreset(0)
{

}

CPresetSetting::~CPresetSetting()
{
}

void CPresetSetting::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Text(pDX, IDC_EDIT_PRESET, m_nPreset);
}


BEGIN_MESSAGE_MAP(CPresetSetting, CDialog)
	ON_BN_CLICKED(IDC_BTN_CONTINUE, &CPresetSetting::OnBnClickedBtnContinue)
	ON_BN_CLICKED(IDC_BTN_CANCEL, &CPresetSetting::OnBnClickedBtnCancel)
END_MESSAGE_MAP()


// CPresetSetting ��Ϣ�������


void CPresetSetting::OnBnClickedBtnContinue()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	UpdateData();
	OnOK();
}


void CPresetSetting::OnBnClickedBtnCancel()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	OnCancel();
}
