// DlgParamPanel.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "VacVionSecurity.h"
#include "DlgParamPanel.h"
#include "afxdialogex.h"
#include "DlgLinkageScene.h"


// CDlgParamPanel �Ի���

IMPLEMENT_DYNAMIC(CDlgParamPanel, CDialog)

CDlgParamPanel::CDlgParamPanel(CWnd* pParent /*=NULL*/)
	: CDialog(CDlgParamPanel::IDD, pParent)
{

}

CDlgParamPanel::~CDlgParamPanel()
{
}

void CDlgParamPanel::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_LIST_ROI, m_lcRoi);
	DDX_Control(pDX, IDC_LIST_LINKAGESCENE, m_lbLinkageScene);
}


BEGIN_MESSAGE_MAP(CDlgParamPanel, CDialog)
	ON_BN_CLICKED(IDC_BTN_ADDROI, &CDlgParamPanel::OnBnClickedBtnAddroi)
	ON_NOTIFY(NM_CLICK, IDC_LIST_ROI, &CDlgParamPanel::OnNMClickListRoi)
	ON_COMMAND(ID_MI_DELETEROI, &CDlgParamPanel::OnMiDeleteroi)
	ON_NOTIFY(NM_RCLICK, IDC_LIST_ROI, &CDlgParamPanel::OnNMRClickListRoi)
	ON_BN_CLICKED(IDC_BTN_ADDLINKAGE, &CDlgParamPanel::OnBnClickedBtnAddlinkage)
END_MESSAGE_MAP()


// CDlgParamPanel ��Ϣ�������

void CDlgParamPanel::InitObserver(const char *pszSceneID, UserOPObserver *pObs, ISceneProvider *pSceneProvider, CSecurityNetAdapter *pSecurityNetAdapter)
{
	m_strCreatingSceneID = pszSceneID;
	m_pObs = pObs;
	m_pSceneProvider = pSceneProvider;
	m_pSecurityNetAdapter = pSecurityNetAdapter;
}

// ��ȡROI�б�
void CDlgParamPanel::SetRoiList(ROIList &rois)
{
	// m_lsRoiList = rois;
	
	int nIndex = 0;
	m_lcRoi.DeleteAllItems();
	ROIList::iterator itr = rois.begin();
	for (; itr!=rois.end(); itr++)
	{
		char szRoiType[32] = {0};
		if (itr->nROIType == emRTLine)
		{
			strcpy(szRoiType, "�߶�");
		}
		else if (itr->nROIType == emRTPolygon)
		{
			strcpy(szRoiType, "�����");
		}

		ROI *pRoiData = new ROI;
		pRoiData->lsPoints = itr->lsPoints;
		pRoiData->nROIType = itr->nROIType;

		int nRow = m_lcRoi.InsertItem(0, szRoiType);

		char szIndex[8] = {0};
		sprintf(szIndex, "%d", nIndex);
		m_lcRoi.SetItemText(nRow, 0, (LPCTSTR)szIndex);
		m_lcRoi.SetItemText(nRow, 1, (LPCTSTR)szRoiType);
		m_lcRoi.SetItemData(nRow, (DWORD_PTR)pRoiData);
	}
}

void CDlgParamPanel::GetRoiList(ROIList &rois)
{
	int nCount = m_lcRoi.GetItemCount();
	for (int i=0; i<nCount; i++)
	{
		ROI * pRoiData = (ROI *)m_lcRoi.GetItemData(i);
		rois.push_back(*pRoiData);
	}
}


// ��ȡ�������ĳ����б�
void CDlgParamPanel::SetLinkageScene(StringList &strlist)
{

}

void CDlgParamPanel::GetLinkageScene(StringList &strlist)
{
	strlist = m_lsLinkageScene;
}

void CDlgParamPanel::OnFinishEditingScene()
{
	m_lsLinkageScene.clear();
	m_lbLinkageScene.ResetContent();

	m_lsRoiList.clear();
	m_lcRoi.DeleteAllItems();
}


void CDlgParamPanel::OnBnClickedBtnAddroi()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	//CDlgRoiSettings dlgRoiSetting;
	//if (IDOK == dlgRoiSetting.DoModal())
	//{
	//	// 
	//	m_lsRoiList.clear();
	//	dlgRoiSetting.GetRois(m_lsRoiList);

	//	m_lcRoi.DeleteAllItems();
	//}
}


//void CDlgParamPanel::OnBnClickedBtnCalibration()
//{
//	// TODO: �ڴ���ӿؼ�֪ͨ����������
//	CDlgSceneCalibration dlgSceneCal;
//	dlgSceneCal.InitVideoProvider(m_pVideoProvider);
//	// dlgSceneCal.InitBackground();
//	if (IDOK == dlgSceneCal.DoModal())
//	{
//		// ��ɱ궨��
//		m_CalParam = dlgSceneCal.cparam;
//	}
//}


BOOL CDlgParamPanel::OnInitDialog()
{
	CDialog::OnInitDialog();

	// TODO:  �ڴ���Ӷ���ĳ�ʼ��
	m_lcRoi.InsertColumn(0,(LPCTSTR)"���",LVCFMT_LEFT,60); //������
	m_lcRoi.InsertColumn(1,(LPCTSTR)"����",LVCFMT_LEFT,120);

	// int nIndex = 0;
	//ROIList::iterator itr = m_lsRoiList.begin();
	//for (; itr!=m_lsRoiList.end(); itr++)
	//{
	//	int nRow = m_lcRoi.InsertItem(0, "new roi");
	//	char szText[32] = {0};
	//	sprintf(szText, "%d", nIndex);
	//	m_lcRoi.SetItemText(nRow, 0, szText);
	//}

	m_lcRoi.SetExtendedStyle(LVS_EX_FULLROWSELECT|LVS_EX_GRIDLINES);

	return TRUE;  // return TRUE unless you set the focus to a control
	// �쳣: OCX ����ҳӦ���� FALSE
}


void CDlgParamPanel::OnNMClickListRoi(NMHDR *pNMHDR, LRESULT *pResult)
{
	LPNMITEMACTIVATE pNMItemActivate = reinterpret_cast<LPNMITEMACTIVATE>(pNMHDR);
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	int nRow = m_lcRoi.GetNextItem(-1, LVNI_SELECTED);

	if (nRow != -1)
	{
		ROI *pRoiSel = (ROI*)m_lcRoi.GetItemData(nRow);
		if (m_pObs)
		{
			m_pObs->OnRoiSelectedChanged(pRoiSel);
		}
	}

	*pResult = 0;
}


void CDlgParamPanel::OnMiDeleteroi()
{
	// TODO: �ڴ���������������
	int nItemIndex = m_lcRoi.GetNextItem(-1,LVNI_SELECTED);

	if (nItemIndex != -1)
	{
		ROI * pRoiData = (ROI*)m_lcRoi.GetItemData(nItemIndex);

		if (pRoiData)
		{
			delete pRoiData;
			pRoiData = NULL;
		}
		m_lcRoi.DeleteItem(nItemIndex);

		// ��ROI��ȡ���б���
		ROIList RoisAfterDel;
		int nCount = m_lcRoi.GetItemCount();
		for (int i=0; i<nCount; i++)
		{
			ROI * pRoiData = (ROI *)m_lcRoi.GetItemData(i);
			RoisAfterDel.push_back(*pRoiData);
		}

		// ֪ͨ�б����
		// m_pObs->OnRoiListChanged(RoisAfterDel);
	}
}


void CDlgParamPanel::OnNMRClickListRoi(NMHDR *pNMHDR, LRESULT *pResult)
{
	LPNMITEMACTIVATE pNMItemActivate = reinterpret_cast<LPNMITEMACTIVATE>(pNMHDR);
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	CMenu muPlay;
	muPlay.LoadMenuA(IDR_MENU_MAIN);
	CPoint mup;
	GetCursorPos(&mup);
	NM_LISTVIEW* pNMListView = (NM_LISTVIEW*)pNMHDR;

	if (pNMListView->iItem != -1)
	{
		muPlay.GetSubMenu(2)->TrackPopupMenu(TPM_RIGHTBUTTON, mup.x, mup.y, this);
		muPlay.DestroyMenu();
	}

	*pResult = 0;
}


void CDlgParamPanel::OnBnClickedBtnAddlinkage()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	CDlgLinkageScene dlg;
	dlg.Init(m_strCreatingSceneID.c_str(), m_pSecurityNetAdapter);
	if (dlg.DoModal() == IDOK)
	{
		// ȷ�����
		StringList::iterator itr = m_lsLinkageScene.begin();

		BOOL bFound = FALSE;
		for (; itr!=m_lsLinkageScene.end(); itr++)
		{
			if (strcmp(itr->c_str(), dlg.m_strLinkageSceneID.c_str()) == 0)
			{
				// 
				bFound = TRUE;
				break;
			}
		}

		if (!bFound)
			m_lsLinkageScene.push_back(dlg.m_strLinkageSceneID);

		m_lbLinkageScene.ResetContent();
		StringList::iterator itrLS = m_lsLinkageScene.begin();
		for (; itrLS != m_lsLinkageScene.end(); itrLS++)
		{
			m_lbLinkageScene.InsertString(0, itrLS->c_str());
		}
		// m_pObs->OnLinkageSceneChanged(m_lsLinkageScene);
	}
}
