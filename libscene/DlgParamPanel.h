#pragma once

#include "resource.h"
#include "UserOPProvider.h"
#include "DlgSceneCalibration.h"
#include "DlgRoiSettings.h"
#include "SecurityNetAdapter.h"
#include "afxcmn.h"
#include "afxwin.h"
// CDlgParamPanel �Ի���

class CDlgParamPanel : public CDialog
{
	DECLARE_DYNAMIC(CDlgParamPanel)

public:
	CDlgParamPanel(CWnd* pParent = NULL);   // ��׼���캯��
	virtual ~CDlgParamPanel();

// �Ի�������
	enum { IDD = IDD_CHILD_SCENE_PARAM };

public:
	void InitObserver(const char *pszSceneID, UserOPObserver *pObs, ISceneProvider *pSceneProvider, CSecurityNetAdapter *pSecurityNetAdapter);

	// ����ROI�б�
	void SetRoiList(ROIList &rois);

	// ��ȡROI�б�
	void GetRoiList(ROIList &rois);

	// ���ô������ĳ����б�
	void SetLinkageScene(StringList &strlist);

	// ��ȡ����������
	void GetLinkageScene(StringList &strlist);

	//// ��ȡ�������ĳ����б�
	//void GetLinkageScene
	void OnFinishEditingScene();

private:
	// �����ṩ��
	string m_strCreatingSceneID;
	ISceneProvider *m_pSceneProvider;
	UserOPObserver *m_pObs; 
	CSecurityNetAdapter *m_pSecurityNetAdapter;

	// �궨��Ϣ����
	Calibration m_CalParam;

	// ROI�б���
	ROIList m_lsRoiList;

	// ������������
	StringList m_lsLinkageScene;

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnBnClickedBtnAddroi();
	//afx_msg void OnBnClickedBtnCalibration();
private:
	CListCtrl m_lcRoi;
public:
	virtual BOOL OnInitDialog();
	afx_msg void OnNMClickListRoi(NMHDR *pNMHDR, LRESULT *pResult);
	afx_msg void OnMiDeleteroi();
	afx_msg void OnNMRClickListRoi(NMHDR *pNMHDR, LRESULT *pResult);
	afx_msg void OnBnClickedBtnAddlinkage();
	CListBox m_lbLinkageScene;
};
