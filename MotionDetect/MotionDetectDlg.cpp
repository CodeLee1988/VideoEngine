
// MotionDetectDlg.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "MotionDetect.h"
#include "MotionDetectDlg.h"
#include "afxdialogex.h"

#define WM_PLAYWNDMENU	WM_USER+100

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// ����Ӧ�ó��򡰹��ڡ��˵���� CAboutDlg �Ի���

class CAboutDlg : public CDialogEx
{
public:
	CAboutDlg();

// �Ի�������
	enum { IDD = IDD_ABOUTBOX };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

// ʵ��
protected:
	DECLARE_MESSAGE_MAP()
};

CAboutDlg::CAboutDlg() : CDialogEx(CAboutDlg::IDD)
{
}

void CAboutDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CAboutDlg, CDialogEx)
END_MESSAGE_MAP()


// CMotionDetectDlg �Ի���



CMotionDetectDlg::CMotionDetectDlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(CMotionDetectDlg::IDD, pParent)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CMotionDetectDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CMotionDetectDlg, CDialogEx)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_MESSAGE(WM_PLAYWNDMENU, &CMotionDetectDlg::OnPlayWndMenu)
	ON_BN_CLICKED(IDC_BUTTON1, &CMotionDetectDlg::OnBnClickedButton1)
	ON_BN_CLICKED(IDC_BUTTON2, &CMotionDetectDlg::OnBnClickedButton2)
	ON_BN_CLICKED(IDC_BUTTON3, &CMotionDetectDlg::OnBnClickedButton3)
	ON_BN_CLICKED(IDC_BUTTON4, &CMotionDetectDlg::OnBnClickedButton4)
	ON_COMMAND(ID_PLAY_FILE, &CMotionDetectDlg::OnPlayFile)
	ON_COMMAND(ID_PLAY_STREAM, &CMotionDetectDlg::OnPlayStream)
END_MESSAGE_MAP()


// CMotionDetectDlg ��Ϣ�������

BOOL CMotionDetectDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// ��������...���˵�����ӵ�ϵͳ�˵��С�

	// IDM_ABOUTBOX ������ϵͳ���Χ�ڡ�
	ASSERT((IDM_ABOUTBOX & 0xFFF0) == IDM_ABOUTBOX);
	ASSERT(IDM_ABOUTBOX < 0xF000);

	CMenu* pSysMenu = GetSystemMenu(FALSE);
	if (pSysMenu != NULL)
	{
		BOOL bNameValid;
		CString strAboutMenu;
		bNameValid = strAboutMenu.LoadString(IDS_ABOUTBOX);
		ASSERT(bNameValid);
		if (!strAboutMenu.IsEmpty())
		{
			pSysMenu->AppendMenu(MF_SEPARATOR);
			pSysMenu->AppendMenu(MF_STRING, IDM_ABOUTBOX, strAboutMenu);
		}
	}

	// ���ô˶Ի����ͼ�ꡣ��Ӧ�ó��������ڲ��ǶԻ���ʱ����ܽ��Զ�
	//  ִ�д˲���
	SetIcon(m_hIcon, TRUE);			// ���ô�ͼ��
	SetIcon(m_hIcon, FALSE);		// ����Сͼ��

	// TODO: �ڴ���Ӷ���ĳ�ʼ������

	return TRUE;  // ���ǽ��������õ��ؼ������򷵻� TRUE
}

void CMotionDetectDlg::OnSysCommand(UINT nID, LPARAM lParam)
{
	if ((nID & 0xFFF0) == IDM_ABOUTBOX)
	{
		CAboutDlg dlgAbout;
		dlgAbout.DoModal();
	}
	else
	{
		CDialogEx::OnSysCommand(nID, lParam);

		SetNoVideo(GetDlgItem(IDC_VIDEO));
	}
}

// �����Ի��������С����ť������Ҫ����Ĵ���
//  �����Ƹ�ͼ�ꡣ����ʹ���ĵ�/��ͼģ�͵� MFC Ӧ�ó���
//  �⽫�ɿ���Զ���ɡ�

void CMotionDetectDlg::OnPaint()
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
		CDialogEx::OnPaint();
	}
}

//���û��϶���С������ʱϵͳ���ô˺���ȡ�ù��
//��ʾ��
HCURSOR CMotionDetectDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}


void CMotionDetectDlg::OnBnClickedButton1()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
}


void CMotionDetectDlg::OnBnClickedButton2()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
}


void CMotionDetectDlg::OnBnClickedButton3()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
}


void CMotionDetectDlg::OnBnClickedButton4()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
}


BOOL CMotionDetectDlg::PreTranslateMessage(MSG* pMsg)
{
	// TODO: �ڴ����ר�ô����/����û���
	if (pMsg->message == WM_RBUTTONDOWN)
	{
		// �Ҽ������������˵�
		SendMessage(WM_PLAYWNDMENU, (WPARAM)this, 0);
	}

	return CDialogEx::PreTranslateMessage(pMsg);
}


void CMotionDetectDlg::SetNoVideo(CWnd *p)
{
	RECT rect;
	HFONT hFontOld;

	CDC *pDC = p->GetDC();

	p->GetClientRect(&rect);
	//ScreenToClient(&rect);

	// ��������
	LOGFONT lf;
	memset(&lf, 0, sizeof(LOGFONT));
	lf.lfQuality = CLEARTYPE_QUALITY;
	lf.lfHeight = (rect.bottom - rect.top)/8;	// �ȽϺ��ʵ������С���벥�Ŵ���ߴ�����Ӧ
	lf.lfWidth = (rect.right - rect.left)/26;	// 
	lf.lfWeight = FW_BOLD;
	HFONT hFontNew = CreateFontIndirect(&lf);

	pDC->SetTextColor(RGB(76, 65, 47));
	pDC->SetBkMode(TRANSPARENT);
	pDC->FillSolidRect(&rect, RGB(10, 10, 10));

	hFontOld = (HFONT)SelectObject(pDC->m_hDC, hFontNew);

	CSize sizeNoVideoStr = pDC->GetTextExtent("NO VIDEO");

	TextOut(pDC->m_hDC, 
		(rect.right - rect.left)/2-sizeNoVideoStr.cx/2, 
		(rect.bottom - rect.top)/2-sizeNoVideoStr.cy/2, 
		"NO VIDEO", 
		8);

	SelectObject(pDC->m_hDC, hFontOld);
	DeleteObject(hFontNew);

	ReleaseDC(pDC);
}

LRESULT CMotionDetectDlg::OnPlayWndMenu(WPARAM wParam, LPARAM lParam)
{
	CPoint point;
	GetCursorPos(&point);
	CPoint pointInTree = point;
	ScreenToClient(&pointInTree);

	RECT rt;
	GetDlgItem(IDC_VIDEO)->GetWindowRect(&rt);
	ScreenToClient(&rt);
	if (PtInRect(&rt, pointInTree))
	{
		CMenu menu;
		menu.LoadMenu(IDR_MENU_MAIN);
		menu.GetSubMenu(0)->TrackPopupMenu(TPM_LEFTALIGN | 
			TPM_RIGHTBUTTON, point.x, point.y, this, NULL);
	}

	return 0;
}

void CMotionDetectDlg::OnPlayFile()
{
	// TODO: �ڴ���������������
	CString s;
	CFileDialog dlgFile(TRUE, NULL, NULL, OFN_HIDEREADONLY, _T("Describe Files (*.cfg)|*.cfg|All Files (*.*)|*.*||"), NULL);

	if (IDOK == dlgFile.DoModal())
	{
		/*
		 *	Description : play file
		 */
	}
}


void CMotionDetectDlg::OnPlayStream()
{
	// TODO: �ڴ���������������
}
