// LinkagePage.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "LinkagePage.h"
#include "NewWizDialog.h"
#include "afxdialogex.h"
#include <map>


// CLinkagePage �Ի���

IMPLEMENT_DYNAMIC(CLinkagePage, CNewWizPage)

CLinkagePage::CLinkagePage(CWnd* pParent /*=NULL*/)
	: CNewWizPage(CLinkagePage::IDD, pParent)
{
	m_pLastSelScene = NULL;
}

CLinkagePage::~CLinkagePage()
{
}

void CLinkagePage::DoDataExchange(CDataExchange* pDX)
{
	CNewWizPage::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_LIST_ALLSCENE, m_lbAllScenes);
	DDX_Control(pDX, IDC_LIST_LINKAGESCENE, m_lbLinkageScenes);
	DDX_Control(pDX, IDC_BITMAP, m_dcPicBox);
	DDX_Control(pDX, IDC_COMBO_FUZZYSEARCH, m_cbbFilter);
}


BEGIN_MESSAGE_MAP(CLinkagePage, CNewWizPage)
	ON_LBN_SELCHANGE(IDC_LIST_ALLSCENE, &CLinkagePage::OnLbnSelchangeListAllscene)
	ON_LBN_DBLCLK(IDC_LIST_ALLSCENE, &CLinkagePage::OnLbnDblclkListAllscene)
	ON_LBN_SELCHANGE(IDC_LIST_LINKAGESCENE, &CLinkagePage::OnLbnSelchangeListLinkagescene)
	ON_LBN_DBLCLK(IDC_LIST_LINKAGESCENE, &CLinkagePage::OnLbnDblclkListLinkagescene)
	ON_WM_PAINT()
	ON_CBN_EDITCHANGE(IDC_COMBO_FUZZYSEARCH, &CLinkagePage::OnCbnEditchangeComboFuzzysearch)
	ON_CBN_SELCHANGE(IDC_COMBO_FUZZYSEARCH, &CLinkagePage::OnCbnSelchangeComboFuzzysearch)
END_MESSAGE_MAP()


// CLinkagePage ��Ϣ�������

BOOL CLinkagePage::FindSceneByID(Scene** scene, const char* id)
{
	if (scene == NULL || id == NULL)
		return FALSE;

	SceneList* pSceneList = m_pParent->GetSceneList();
	SceneList::iterator itrScene = pSceneList->begin();
	for (; itrScene != pSceneList->end(); ++itrScene)
	{
		if (strcmp(itrScene->sID.c_str(), id) == 0)
		{
			*scene = &(*itrScene);
			return TRUE;
		}
	}
	return FALSE;
}

void CLinkagePage::OnSetActive()
{
	m_pParent->SetWindowTextA("���Ĳ�����������");

	m_pLastSelScene = NULL;

	Scene* pScene = m_pParent->GetScene();
	SceneList* pSceneList = m_pParent->GetSceneList();

	m_lbAllScenes.ResetContent();
	m_lbLinkageScenes.ResetContent();

	int nRow = m_lbAllScenes.AddString(pScene->sSceneName.c_str());
	m_lbAllScenes.SetItemData(nRow, (DWORD_PTR)pScene);

	SceneList::iterator itrScene = pSceneList->begin();
	for (; itrScene != pSceneList->end(); ++itrScene)
	{
		if (pScene->sID != itrScene->sID)
		{
			nRow = m_lbAllScenes.AddString(itrScene->sSceneName.c_str());
			m_lbAllScenes.SetItemData(nRow, (DWORD_PTR)&(*itrScene));
		}
	}

	StringList::iterator itrLink = pScene->lsLinkageScene.begin();
	for (itrLink; itrLink != pScene->lsLinkageScene.end(); ++itrLink)
	{
		Scene* secne = NULL;
		if (this->FindSceneByID(&secne, itrLink->c_str()))
		{
			nRow = m_lbLinkageScenes.AddString(secne->sSceneName.c_str());
			m_lbLinkageScenes.SetItemData(nRow, (DWORD_PTR)secne);
		}
	}

	//////////////////////////////////////////////////////////////////////////
	this->SetScene(pScene);
}

LRESULT CLinkagePage::OnWizardBack()
{
	if (this->SaveLinkageScene())
		return 0;
	return -1;
}

LRESULT CLinkagePage::OnWizardNext()
{
	if (this->SaveLinkageScene())
			return 0;
	return -1;
}

BOOL CLinkagePage::SaveLinkageScene()
{
	Scene* pScene = m_pParent->GetScene();
	pScene->lsLinkageScene.clear();

	int nCount = m_lbLinkageScenes.GetCount();
	for (int i=0; i<nCount; i++)
	{
		Scene *pScene = (Scene *)m_lbLinkageScenes.GetItemData(i);
		pScene->lsLinkageScene.push_back(pScene->sID);
	}

	return TRUE;
}

void CLinkagePage::SetScene(Scene* pScene)
{
	if (pScene == NULL && pScene == m_pLastSelScene)
		return;

	m_pLastSelScene = pScene;

	Scene* theScene = m_pParent->GetScene();

	if (pScene->sID == theScene->sID)
	{
		// �༭�ĳ���
		m_dcPicBox.SetBackgroundPicture(m_pParent->GetPicture());
	}
	else
	{
		CString strPathName;
		if (m_pParent->GetPicBySceneID(strPathName, pScene->sID.c_str()))
		{
			m_dcPicBox.SetBackgroundPicture(strPathName.GetString(), "jpeg");
		}
		else
		{
			m_dcPicBox.SetBackgroundPicture(NULL);
		}
	}

	FigureVector lstFigs;
	ROIList::const_iterator itrRoi = pScene->lsROIs.begin();
	for (; itrRoi != pScene->lsROIs.end(); ++itrRoi)
	{
		Figure fig;
		fig.type = (ShapeType)itrRoi->nROIType;
		fig.nLineWidth = 2;
		fig.crLineColor = 0x00ff00;

		ScPointFList::const_iterator itrPoint = itrRoi->lsPoints.begin();
		for (; itrPoint != itrRoi->lsPoints.end(); ++itrPoint)
		{
			POINTF pt;
			pt.x = 1.0f*itrPoint->x;
			pt.y = 1.0f*itrPoint->y;
			fig.points.push_back(pt);
		}

		lstFigs.push_back(fig);
	}

	m_dcPicBox.SetFigures(lstFigs);
}

BOOL CLinkagePage::AddLinkageScene(const Scene* pScene)
{
	Scene* theScene = m_pParent->GetScene();
	if (pScene == NULL)
		return FALSE;

	// �ж��Ƿ��Ǳ���
	if (theScene->sID == pScene->sID)
		return FALSE;

	// ���˵��ظ���
	int nCount = m_lbLinkageScenes.GetCount();
	for (int i=0; i<nCount; i++)
	{
		Scene* scene = (Scene *)m_lbLinkageScenes.GetItemData(i);
		if (scene->sID == pScene->sID)
			return FALSE;
	}

	int nNewRow = m_lbLinkageScenes.AddString(pScene->sSceneName.c_str());
	m_lbLinkageScenes.SetItemData(nNewRow, (DWORD_PTR)pScene);
	return TRUE;
}

BOOL CLinkagePage::DelCurSelLinkageScene()
{
	int nItem = m_lbLinkageScenes.GetCurSel();
	if (nItem == -1)
		return FALSE;

	m_lbLinkageScenes.DeleteString(nItem);
	return TRUE;
}

void CLinkagePage::OnLbnSelchangeListAllscene()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������

	// ��ʾѡ�г����Ľ�ͼ
	int nRow = m_lbAllScenes.GetCurSel();
	Scene* pScene = (Scene*)m_lbAllScenes.GetItemData(nRow);
	this->SetScene(pScene);
}

void CLinkagePage::OnLbnDblclkListAllscene()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������

	// ��ѡ�г�����ӵ������������б�
	int nRow = m_lbAllScenes.GetCurSel();
	Scene* pScene = (Scene*)m_lbAllScenes.GetItemData(nRow);

	this->AddLinkageScene(pScene);
}

void CLinkagePage::OnLbnSelchangeListLinkagescene()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������

	// ��ʾѡ�г����Ľ�ͼ
	int nItemSel = m_lbLinkageScenes.GetCurSel();
	Scene* pScene = (Scene *)m_lbLinkageScenes.GetItemData(nItemSel);
	this->SetScene(pScene);
}

void CLinkagePage::OnLbnDblclkListLinkagescene()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������

	// ��ѡ�г����ӱ����������б���ɾ��
	this->DelCurSelLinkageScene();
}

void CLinkagePage::OnPaint()
{
	CPaintDC dc(this); // device context for painting
	// TODO: �ڴ˴������Ϣ����������

	// ��Ϊ��ͼ��Ϣ���� CNewWizPage::OnPaint()
}


BOOL CLinkagePage::OnInitDialog()
{
	CNewWizPage::OnInitDialog();

	// TODO:  �ڴ���Ӷ���ĳ�ʼ��

	return TRUE;  // return TRUE unless you set the focus to a control
	// �쳣: OCX ����ҳӦ���� FALSE
}


void CLinkagePage::OnCbnEditchangeComboFuzzysearch()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	std::map<int,CString> mapItem;

	CString strFilter;
	m_cbbFilter.GetWindowText(strFilter);
	if (!strFilter.IsEmpty())
	{
		int count = m_lbAllScenes.GetCount();
		for (int i=0; i<count; ++i)
		{
			CString strItem;
			m_lbAllScenes.GetText(i, strItem);

			if (strItem.Find(strFilter, 0) != -1)
			{
				mapItem[i] = strItem;
			}
		}
	}

	int cbbCount = m_cbbFilter.GetCount();
	for (int k=0; k<cbbCount; ++k)
	{
		m_cbbFilter.DeleteString(0);
	}

	std::map<int,CString>::const_iterator itrItem = mapItem.begin();
	for (; itrItem != mapItem.end(); ++itrItem)
	{
		int nItem = m_cbbFilter.AddString(itrItem->second);
		m_cbbFilter.SetItemData(nItem, (DWORD_PTR)itrItem->first);
	}

	//cbbCount = m_cbbFilter.GetCount();

	//if (cbbCount > 0)
	//	m_cbbFilter.ShowDropDown();
	//else
	//	m_cbbFilter.ShowDropDown(FALSE);
}


void CLinkagePage::OnCbnSelchangeComboFuzzysearch()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	CString strName;
	int nCurSel = m_cbbFilter.GetCurSel();
	m_cbbFilter.GetLBText(nCurSel, strName);
	int nItem = (int)m_cbbFilter.GetItemData(nCurSel);
	
	nCurSel = m_lbAllScenes.GetCurSel();
	m_lbAllScenes.SetFocus();
	m_lbAllScenes.SetCurSel(nItem);

	if (nCurSel != nItem)
		this->OnLbnSelchangeListAllscene();
}
