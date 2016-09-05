// HomographyDlg.h : header file
//

#pragma once

#include <vector>
#include <list>
#include "afxcmn.h"
#include "afxwin.h"
//#include "SecurityDef.h"
#include "NewWizDialog.h"
#include "NewWizPage.h"
#include "DrawCalibrationResult.h"
using namespace std;


enum CaliStep
{
	CaliStep_None = 0,
	CaliStep_Head_P1,
};

// CDlgAbbhParam �Ի���
class CDlgSceneCalibration : public CNewWizPage
{
	DECLARE_DYNAMIC(CDlgSceneCalibration)
	// ����
public:
	CDlgSceneCalibration(CWnd* pParent = NULL);	// ��׼���캯��
	virtual ~CDlgSceneCalibration();

	enum { IDD = IDW_CALIBRATION };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV ֧��


	DECLARE_MESSAGE_MAP()

public:
	HICON m_hIcon;

	// ��дCNewWizPage
	void OnSetActive();
	LRESULT OnWizardBack();
	LRESULT OnWizardNext();

protected:
	// ���ɵ���Ϣӳ�亯��
	afx_msg HCURSOR OnQueryDragIcon();

	virtual BOOL OnInitDialog();

	void UpdateCalibSliderCtrl();
	void UpdateCalibValue();

	CButton m_NextBtn;
	CButton m_PrevBtn;
	CButton m_OkBtn;
	CButton m_CancelBtn;

	//////////////////////////////////////////////////////////////////////////
public:	// Output
	list<POINT> m_listTopPoints;		// ��ͼ���е�����
	list<POINT> m_listBottomPoints;
	//////////////////////////////////////////////////////////////////////////

private:
	void DrawCalibImage();
	void SaveCalibration();

private:
	CStatic m_ctlBitmap;

	Gdiplus::Bitmap* m_pCalibBmp;

	BOOL m_bShow3DBox;
	float m_xBox;
	float m_yBox;
	float m_fBoxLength; // ���ӳ�
	float m_fBoxWidth; // ���ӿ�
	float m_fBoxHeight; // ���Ӹ�

	POINT  m_ptCurHumanTop;				// ��ͼ���е�����
	POINT  m_ptCurHumanBottom;
	CaliStep m_nLabelStep;
	int m_nHumanNumControl;
public:
	afx_msg void OnLButtonDown(UINT nFlags, CPoint point);
	afx_msg void OnRButtonDown(UINT nFlags, CPoint point);
	afx_msg void OnMouseMove(UINT nFlags, CPoint point);
	afx_msg void OnBnClickedBtnPrev();
	afx_msg void OnBnClickedBtnNext();
	
	afx_msg void OnLButtonUp(UINT nFlags, CPoint point);
	afx_msg void OnVScroll(UINT nSBCode, UINT nPos, CScrollBar* pScrollBar);
	afx_msg void OnNMCustomdrawSliderTheta(NMHDR *pNMHDR, LRESULT *pResult);
	afx_msg void OnNMCustomdrawSliderX(NMHDR *pNMHDR, LRESULT *pResult);
	afx_msg void OnNMCustomdrawSliderD(NMHDR *pNMHDR, LRESULT *pResult);
	afx_msg void OnNMCustomdrawSliderF(NMHDR *pNMHDR, LRESULT *pResult);

	CSliderCtrl m_ctrlSliderX;
	CSliderCtrl m_ctrlSliderD;
	CSliderCtrl m_ctrlSliderF;
	CSliderCtrl m_ctrlSintheta;

	float m_fPanAngle;
	float m_fCameraHeight;
	float m_fFocalLength;
	float m_fTiltAngle;
	float m_fCCDWidth;
	float m_fCCDHeight;

	afx_msg void OnLButtonDblClk(UINT nFlags, CPoint point);
	afx_msg void OnCbnSelchangeComboCcd();
	afx_msg void OnPaint();
	afx_msg void OnEnChangeEditX();
	afx_msg void OnEnChangeEditD();
	afx_msg void OnEnChangeEditF();
	afx_msg void OnEnChangeEditSintheta();
	float m_fPeopleHeight;
	afx_msg void OnEnChangeEdtPeopleHeight();
	BOOL m_bStretch;
	afx_msg void OnBnClickedChkStretch();
	BOOL m_bShowVerticalLine;
	afx_msg void OnBnClickedChkShowVerticalLine();
	afx_msg void OnBnClickedShow3DBox();
	afx_msg void OnEnChangeEdtBoxLength();
	afx_msg void OnEnChangeEdtBoxWidth();
	afx_msg void OnEnChangeEdtBoxHeight();
};