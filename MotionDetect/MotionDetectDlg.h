
// MotionDetectDlg.h : ͷ�ļ�
//

#pragma once


// CMotionDetectDlg �Ի���
class CMotionDetectDlg : public CDialogEx
{
// ����
public:
	CMotionDetectDlg(CWnd* pParent = NULL);	// ��׼���캯��

// �Ի�������
	enum { IDD = IDD_MOTIONDETECT_DIALOG };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV ֧��

private:
	void SetNoVideo(CWnd *p);
	/*
	 *	Description : current selected channel
	 */
	int nCurChl;

// ʵ��
protected:
	HICON m_hIcon;

	// ���ɵ���Ϣӳ�亯��
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnBnClickedButton1();
	afx_msg void OnBnClickedButton2();
	afx_msg void OnBnClickedButton3();
	afx_msg void OnBnClickedButton4();
	virtual BOOL PreTranslateMessage(MSG* pMsg);
	LRESULT OnPlayWndMenu(WPARAM wParam, LPARAM lParam);
	afx_msg void OnPlayFile();
	afx_msg void OnPlayStream();
};
