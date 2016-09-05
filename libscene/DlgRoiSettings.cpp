
// DlgRoiSettings.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "DlgRoiSettings.h"
#include "afxdialogex.h"
#include "NewWizDialog.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CDlgRoiSettings �Ի���




CDlgRoiSettings::CDlgRoiSettings(CWnd* pParent /*=NULL*/)
	: CNewWizPage(CDlgRoiSettings::IDD, pParent)
{
	m_nLastSelFigure = -1;
}

void CDlgRoiSettings::DoDataExchange(CDataExchange* pDX)
{
	CNewWizPage::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_PICBOX, m_dcPicBox);
	DDX_Control(pDX, IDC_LIST_ROIS, m_lcRois);
}

BEGIN_MESSAGE_MAP(CDlgRoiSettings, CNewWizPage)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(IDC_RADIO_NONE, &CDlgRoiSettings::OnBnClickedRadioNone)
	ON_BN_CLICKED(IDC_RADIO_LINE, &CDlgRoiSettings::OnBnClickedRadioLine)
	ON_BN_CLICKED(IDC_RADIO_POLYGON, &CDlgRoiSettings::OnBnClickedRadioPolygon)
	ON_NOTIFY(NM_CLICK, IDC_LIST_ROIS, &CDlgRoiSettings::OnNMClickListRois)
	ON_NOTIFY(NM_RCLICK, IDC_LIST_ROIS, &CDlgRoiSettings::OnNMRClickListRois)
	ON_COMMAND(IDM_ROI_DELETE, &CDlgRoiSettings::OnROIDelete)
	ON_NOTIFY(NM_SETFOCUS, IDC_LIST_ROIS, &CDlgRoiSettings::OnNMSetfocusListRois)
	ON_BN_CLICKED(IDC_RADIO_LINE2, &CDlgRoiSettings::OnBnClickedRadioLine2)
	ON_BN_CLICKED(IDC_RADIO_POLYGON2, &CDlgRoiSettings::OnBnClickedRadioPolygon2)
END_MESSAGE_MAP()


// CDlgRoiSettings ��Ϣ�������

BOOL CDlgRoiSettings::OnInitDialog()
{
	CNewWizPage::OnInitDialog();

	// TODO: �ڴ���Ӷ���ĳ�ʼ������

	m_dcPicBox.SetDrawingParam(2, 0x00ff00, 0x0000ff);

	m_dcPicBox.SetDrawType(stSWLine);
	((CButton*)this->GetDlgItem(IDC_RADIO_LINE))->SetCheck(BST_CHECKED);

	m_lcRois.InsertColumn(0,"����",LVCFMT_LEFT,40); //������
	m_lcRois.InsertColumn(1,"����",LVCFMT_LEFT,80); //������
	m_lcRois.SetExtendedStyle(LVS_EX_FULLROWSELECT|LVS_EX_GRIDLINES);

	m_dcPicBox.SetNotify(this);

	return TRUE;  // ���ǽ��������õ��ؼ������򷵻� TRUE
}

void CDlgRoiSettings::OnSysCommand(UINT nID, LPARAM lParam)
{
	CNewWizPage::OnSysCommand(nID, lParam);
}

// �����Ի��������С����ť������Ҫ����Ĵ���
//  �����Ƹ�ͼ�ꡣ����ʹ���ĵ�/��ͼģ�͵� MFC Ӧ�ó���
//  �⽫�ɿ���Զ���ɡ�

void CDlgRoiSettings::OnPaint()
{
	if (IsIconic())
	{
		CPaintDC dc(this); // ���ڻ��Ƶ��豸������

		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

		// ʹͼ���ڹ����������о���
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// ����ͼ��
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CNewWizPage::OnPaint();
	}
}

//���û��϶���С������ʱϵͳ���ô˺���ȡ�ù��
//��ʾ��
HCURSOR CDlgRoiSettings::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}

//////////////////////////////////////////////////////////////////////////
void CDlgRoiSettings::SetBackgroundPicture(Gdiplus::Bitmap* pImage)
{
	m_dcPicBox.SetBackgroundPicture(pImage);
}

void CDlgRoiSettings::SetRois(const ROIList& lsROIs)
{
	m_lsRois = lsROIs;

	FigureVector lstFigs;
	ROIList::const_iterator itrRoi = lsROIs.begin();
	for (; itrRoi != lsROIs.end(); ++itrRoi)
	{
		Figure fig;
		fig.type = (ShapeType)itrRoi->nROIType;
		fig.nLineWidth = 2;
		fig.crLineColor = 0x00ff00;

		ScPointFList::const_iterator itrPoint = itrRoi->lsPoints.begin();
		for (; itrPoint != itrRoi->lsPoints.end(); ++itrPoint)
		{
			POINTF pt;
			// ת����PICBOX������
			pt.x = itrPoint->x;
			pt.y = itrPoint->y;
			fig.points.push_back(pt);
		}

		this->InsertROIItem(&(*itrRoi));

		lstFigs.push_back(fig);
	}

	m_dcPicBox.SetFigures(lstFigs);
}

void CDlgRoiSettings::OnSetActive()
{
	CString strStep;
	strStep.Format("��%d��������ROI", m_nIndex);
	m_pParent->SetWindowTextA(strStep);

	m_lcRois.DeleteAllItems();

	Scene* pScene = m_pParent->GetScene();

	Gdiplus::Bitmap* pImage = m_pParent->GetPicture();
	this->SetBackgroundPicture(pImage);

	this->SetRois(pScene->lsROIs);
}

LRESULT CDlgRoiSettings::OnWizardBack()
{
	// ����궨����
	Scene* pScene = m_pParent->GetScene();
	pScene->lsROIs = m_lsRois;

	return 0;
}

LRESULT CDlgRoiSettings::OnWizardNext()
{
	if (this->SaveROI())
		return 0;
	return -1;// ���ڵ�ǰҳ
}

BOOL CDlgRoiSettings::OnWizardFinish()
{
	this->SaveROI();
	return TRUE;
}


BOOL CDlgRoiSettings::SaveROI()
{
	if (m_lsRois.size() == 0)
	{
		if (IDOK == MessageBox("δ���ROI��������ȫ����⡣", "��ʾ", MB_OKCANCEL))
		{
			// ���һ��ȫ����ROI
		}
		else
		{
			return FALSE;
		}
	}

	Scene* pScene = m_pParent->GetScene();

	// ����궨����
	pScene->lsROIs = m_lsRois;

	return TRUE;
}

void CDlgRoiSettings::OnFigureUpdate(FigureVector *lstFigs)
{
	m_lsRois.clear();
	m_lcRois.DeleteAllItems();

	FigureVector::const_iterator itrFig = lstFigs->begin();
	for (; itrFig != lstFigs->end(); ++itrFig)
	{
		ROI roi;
		roi.nROIType = itrFig->type;
		//if (itrFig->type == stSWLine)
		//	roi.nROIType = stSWLine;
		//else if (itrFig->type == stPolygonOut)
		//	roi.nROIType = stPolygonOut;

		PointVector::const_iterator itrPoint = itrFig->points.begin();
		for (; itrPoint != itrFig->points.end(); ++itrPoint)
		{
			ScPointF ptf;
			ptf.x = 1.0f*itrPoint->x;
			ptf.y = 1.0f*itrPoint->y;
			roi.lsPoints.push_back(ptf);
		}

		this->InsertROIItem(&roi);

		m_lsRois.push_back(roi);
	}
}

void CDlgRoiSettings::InsertROIItem(const ROI* pROI)
{
	int nRow = m_lcRois.GetItemCount();
	m_lcRois.InsertItem(nRow, "new");
	char szItemText[32] = {0};
	sprintf(szItemText, "%d", (int)pROI->lsPoints.size());
	m_lcRois.SetItemText(nRow, 0, szItemText);
	
	if ((int)pROI->nROIType == 0)
		m_lcRois.SetItemText(nRow, 1, "������");
	else if ((int)pROI->nROIType == 1)
		m_lcRois.SetItemText(nRow, 1, "˫����");
	else if ((int)pROI->lsPoints.size() > 2)
		m_lcRois.SetItemText(nRow, 1, "������ڵ���");
	else 
		m_lcRois.SetItemText(nRow, 1, "������⵽��");
}

void CDlgRoiSettings::OnBnClickedRadioNone()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	m_dcPicBox.SetDrawType(stNone);
}


void CDlgRoiSettings::OnBnClickedRadioLine()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	m_dcPicBox.SetDrawType(stSWLine);
}


void CDlgRoiSettings::OnBnClickedRadioPolygon()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	m_dcPicBox.SetDrawType(stPolygonOut);
}

void CDlgRoiSettings::SelectFigure(int nFigure)
{
	if (nFigure != -1)
	{
		m_dcPicBox.SetFigureAttributes(nFigure, 4, 0xff00ff, FAC_LINE_WIDTH|FAC_LINE_COLOR);
	}

	if (nFigure != m_nLastSelFigure)
	{
		m_dcPicBox.RestoreFigureAttributes(m_nLastSelFigure);
		m_nLastSelFigure = nFigure;
	}
}

void CDlgRoiSettings::OnNMClickListRois(NMHDR *pNMHDR, LRESULT *pResult)
{
	LPNMITEMACTIVATE pNMItemActivate = reinterpret_cast<LPNMITEMACTIVATE>(pNMHDR);
	// TODO: �ڴ���ӿؼ�֪ͨ����������

	*pResult = 0;

	int nItemIndex = pNMItemActivate->iItem;
	this->SelectFigure(nItemIndex);
}


void CDlgRoiSettings::OnNMRClickListRois(NMHDR *pNMHDR, LRESULT *pResult)
{
	LPNMITEMACTIVATE pNMItemActivate = reinterpret_cast<LPNMITEMACTIVATE>(pNMHDR);
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	*pResult = 0;

	int nItemIndex = pNMItemActivate->iItem;

	this->SelectFigure(nItemIndex);

	if (nItemIndex == -1)
		return;

	CMenu menu;
	if (!menu.LoadMenu(IDR_MENU_MAIN))
		return;

	CPoint curpos;
	GetCursorPos(&curpos);

	menu.GetSubMenu(0)->TrackPopupMenu(TPM_RIGHTBUTTON, curpos.x, curpos.y, this);
	menu.DestroyMenu();
}


void CDlgRoiSettings::OnROIDelete()
{
	// TODO: �ڴ���������������
	int nItemSel = m_lcRois.GetNextItem(-1, LVNI_SELECTED);
	if (nItemSel == -1)
		return;

	this->SelectFigure(-1);

	m_lcRois.DeleteItem(nItemSel);
	m_dcPicBox.DeleteFigure(nItemSel);

	ROIList::iterator itrROI = m_lsRois.begin();
	for (int i=0; itrROI != m_lsRois.end(); ++i, ++itrROI)
	{
		if (i == nItemSel)
		{
			m_lsRois.erase(itrROI);
			break;
		}
	}
}


void CDlgRoiSettings::OnNMSetfocusListRois(NMHDR *pNMHDR, LRESULT *pResult)
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	*pResult = 0;

	int nItemSel = m_lcRois.GetNextItem(-1, LVNI_SELECTED);
	this->SelectFigure(nItemSel);
}


void CDlgRoiSettings::OnBnClickedRadioLine2()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	m_dcPicBox.SetDrawType(stTWLine);
}


void CDlgRoiSettings::OnBnClickedRadioPolygon2()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	m_dcPicBox.SetDrawType(stPolygonIn);
}
