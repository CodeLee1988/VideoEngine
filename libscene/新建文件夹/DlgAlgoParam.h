#pragma once

#include "NewWizPage.h"
//#include "SCConfig.h"
//#include "VIONTREEDEF.h"

typedef CMap<int,int&,CString,CString&> CMapIntToString;

// CDlgAlgoParam �Ի���

class CDlgAlgoParam : public CNewWizPage
{
	DECLARE_DYNAMIC(CDlgAlgoParam)

public:
	CDlgAlgoParam(CWnd* pParent = NULL);   // ��׼���캯��
	virtual ~CDlgAlgoParam();

// �Ի�������
	enum { IDD = IDW_ALGOPARAM };

	//HSCConfig m_hConfig;
	//HVIONTREE m_hTree;
	CMapIntToString m_mapVal;
	CMapIntToString m_mapInf;
	int m_nLastAlgoType;

	void LoadValAndInfo(const char* val, int type, const char* inf);
	BOOL OnSaveParam(const char* key, void* val, VALUETYPE type);
	void SaveValue();

	virtual void OnSetActive();
	virtual LRESULT OnWizardBack();
	virtual BOOL OnWizardFinish();

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

	DECLARE_MESSAGE_MAP()
public:
	virtual BOOL OnInitDialog();
	afx_msg void OnDestroy();
};
