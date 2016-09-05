// DlgAlgoParam.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "libscene.h"
#include "DlgAlgoParam.h"
#include "NewWizDialog.h"
#include "afxdialogex.h"
#include "SPAPDocument.h"


// CDlgAlgoParam �Ի���

IMPLEMENT_DYNAMIC(CDlgAlgoParam, CNewWizPage)

CDlgAlgoParam::CDlgAlgoParam(CWnd* pParent /*=NULL*/)
	: CNewWizPage(CDlgAlgoParam::IDD, pParent)
{
	m_hConfig = NULL;
	m_hTree = NULL;
	m_nLastAlgoType = -1;
}

CDlgAlgoParam::~CDlgAlgoParam()
{
	if (m_hConfig)
	{
		scCfgDestroy(m_hConfig);
		m_hConfig = NULL;
	}
}

void CDlgAlgoParam::DoDataExchange(CDataExchange* pDX)
{
	CNewWizPage::DoDataExchange(pDX);
}


BEGIN_MESSAGE_MAP(CDlgAlgoParam, CNewWizPage)
	ON_WM_DESTROY()
END_MESSAGE_MAP()


// CDlgAlgoParam ��Ϣ�������

//////////////////////////////////////////////////////////////////////////
//Cfg�¼��ص�
int SC_CDECL fScCallBackCfgProEvent(void *, void *, void *)
{
	return 0;
}

//Cfg�洢�����ػص�
//�Ӵ洢ý����Config
//�������û�����
//����ֵ������Config��XML��ָ��
char* SC_CDECL fScCallBackLoadCfg(DWORD user)	
{
	return "";
}

//����Config�е�XML�����洢ý��
//������1.Ҫ�洢��XML��ָ��  2.XML�����ݵĴ�С  3.�û�����
//����ֵ������״̬
ScErr SC_CDECL fScCallBackSaveCfg(char *xml,unsigned int len,DWORD user)
{
	return SC_ErrSuccess;
}

//���ò�������
ScErr fPARAM_SetParamCallBack(HVIONTREE hTree, HPARAM hParam, const char* szParamPath, void* pValue, PARAM_TYPE type, void* pUserData)
{
	CDlgAlgoParam* pDlg = (CDlgAlgoParam*)pUserData;
	VALUETYPE vtype = SC_TypeUndef;
	switch (type)
	{
	case PARAM_LONG:
		vtype = SC_TypeUint32;
		break;
	case PARAM_FLOAT:
		vtype = SC_TypeFloat;
		break;
	case PARAM_STRING:
		vtype = SC_TypeString;
		break;
	case PARAM_ENUM:
		vtype = SC_TypeEnum;
		break;
	case PARAM_BOOL:
		vtype = SC_TypeBool;
		break;
	case PARAM_TIME:
		vtype = SC_TypeTime;
		break;
	default:
		break;
	}
	pDlg->OnSaveParam(szParamPath, pValue, vtype);
	return SC_ErrSuccess;
}

//�����������ԭ��
ScErr fPARAM_SaveParamCallBack(HVIONTREE hTree, HPARAM hParam, void* pUserData)
{
	return SC_ErrSuccess;
}

BOOL MBToUTF8(const char* pszSrc, char** pszDst)   
{   
	WCHAR *pszTemp;

	int len = MultiByteToWideChar(CP_ACP, 0, pszSrc, -1, NULL, 0);   
	pszTemp = new WCHAR[len+1];
	if (pszTemp == NULL)
		return FALSE;

	MultiByteToWideChar(CP_ACP, 0, pszSrc, -1, pszTemp, len); 

	len = WideCharToMultiByte(CP_UTF8, 0, pszTemp, -1, NULL, 0, NULL, NULL);
	*pszDst = new char[len+1];
	if (*pszDst == NULL)
	{
		delete[] pszTemp;
		return FALSE;
	}

	WideCharToMultiByte(CP_UTF8, 0, pszTemp, -1, *pszDst, len, NULL, NULL);  

	delete[] pszTemp;
	return TRUE;
}

void TrimSpaceAndTab(CString& strDst)
{
	// ȥ�껻�з�
	strDst.Replace("\r", "");
	strDst.Replace("\n", "");
	// ȥ���Ʊ��
	strDst.Replace("\t", "");
}

void cfgRemoveAttriNode(CSPAPDocument* pDoc, SPAPNodePtr pParent)
{
	SPAPNodePtr child = pDoc->GetFirstChildNode(pParent);
	for (; child; child = pDoc->GetNextSiblingNode(child))
	{
		if (child->GetnodeType() == MSXML2::NODE_ELEMENT
			&& child->firstChild && child->firstChild->GetnodeType() == MSXML2::NODE_ELEMENT
			&& child->firstChild->firstChild && child->firstChild->firstChild->GetnodeType() != MSXML2::NODE_ELEMENT)
		{
			char szDefVal[512] = {0};
			SPAPNodePtr type = pDoc->FindNode_ByName(child, "AttribType");
			SPAPNodePtr info = pDoc->FindNode_ByName(child, "AttribInfo");
			SPAPNodePtr def = pDoc->FindNode_ByName(child, "AttribDefault");
			SPAPNodePtr range = pDoc->FindNode_ByName(child, "AttribRange");
			if (type)
				pDoc->RemoveChild(child, type);
			if (info)
				pDoc->RemoveChild(child, info);
			if (def)
			{
				pDoc->GetText(def, szDefVal);
				pDoc->RemoveChild(child, def);
			}
			if (range)
				pDoc->RemoveChild(child, range);

			if (strlen(szDefVal) > 0)
				pDoc->SetText(child, szDefVal);
		}
		else
		{
			cfgRemoveAttriNode(pDoc, child);
		}
	}
}

BOOL cfgGetValFromInfo(const CString& strInfo, CString& strVal)
{
	CSPAPDocument doc;
	if (!doc.LoadFromXML(strInfo))
		return FALSE;

	SPAPNodePtr root = doc.GetRootNode();
	if (root == NULL)
		return FALSE;

	cfgRemoveAttriNode(&doc, root);
	
	strVal = (const char*)doc.GetDocXml();
	return TRUE;
}

//////////////////////////////////////////////////////////////////////////
BOOL CDlgAlgoParam::OnInitDialog()
{
	CNewWizPage::OnInitDialog();

	// TODO:  �ڴ���Ӷ���ĳ�ʼ��
	
	return TRUE;  // return TRUE unless you set the focus to a control
	// �쳣: OCX ����ҳӦ���� FALSE
}

void CDlgAlgoParam::LoadValAndInfo(const char* val, int type, const char* inf)
{
	m_mapVal.RemoveAll();
	m_mapInf.RemoveAll();

	BOOL bSetVal = FALSE;
	CString strAlgoVal = val;
	// ȥ�������Ʊ��
	TrimSpaceAndTab(strAlgoVal);
	if (!strAlgoVal.IsEmpty())
	{
		m_mapVal[type] = strAlgoVal;
		bSetVal = TRUE;
	}

	CString strInfo = inf;
	if (strInfo.IsEmpty())
		return;

	CSPAPDocument doc;
	if (!doc.LoadFromXML(strInfo))
		return;

	SPAPNodePtr root = doc.GetRootNode();
	SPAPNodePtr algo = doc.FindNode_ByName(root, "algo");
	if (algo == NULL)
		return;

	SPAPNodePtr algoinfo = doc.GetFirstChildNode(algo);
	for (; algoinfo; algoinfo=doc.GetNextSiblingNode(algoinfo))
	{
		char szNodeName[512] = {0};
		doc.GetName(algoinfo, szNodeName);
		if (strcmp(szNodeName, "algoinfo"))
			continue;

		int nAlgoType = -1;
		if (!doc.GetAttributeValue(algoinfo, "type", nAlgoType))
			continue;

		SPAPNodePtr algo_value = doc.FindNode_ByName(algoinfo, "value");
		SPAPNodePtr algo_info = doc.FindNode_ByName(algoinfo, "info");
		if (algo_value == NULL || algo_info == NULL)
			continue;

		CString strAlgoInfo = (LPCTSTR)doc.GetCDATASectionData(algo_info);
		CString strXmlInfo = "<?xml version=\"1.0\" encoding=\"GBK\"?>";
		strXmlInfo += strAlgoInfo;
		// ȥ�������Ʊ��
		TrimSpaceAndTab(strXmlInfo);
		m_mapInf[nAlgoType] = strXmlInfo;

		if (bSetVal && nAlgoType == type)
			continue;
		
		// �㷨�б�Ϊ�գ�����������ȡĬ��ֵ
		strAlgoVal.Empty();
		strAlgoVal = (LPCTSTR)doc.GetCDATASectionData(algo_value);
		CString strXmlValue = "<?xml version=\"1.0\" encoding=\"GBK\"?>";
		strXmlValue += strAlgoVal;
		// ȥ�������Ʊ��
		TrimSpaceAndTab(strXmlValue);
		m_mapVal[nAlgoType] = strXmlValue;
	}
}

void CDlgAlgoParam::SaveValue()
{
	if (m_hTree)
	{
		VT_SaveConfig(m_hTree);

		int nValLen = 0;
		char* pVal = scCfgGetValStream(m_hConfig, &nValLen);
		if (pVal)
		{
			CString strVal = pVal;
			m_mapVal[m_pParent->GetScene()->nAlgoType] = strVal;
			m_pParent->GetScene()->sAlgoParamlist = pVal;

			scCfgFreeValStream(m_hConfig);
		}
		else
		{
			m_mapVal[m_pParent->GetScene()->nAlgoType] = "";
			m_pParent->GetScene()->sAlgoParamlist = "";
		}
	}
}

void CDlgAlgoParam::OnSetActive()
{
	CString strStep;
	strStep.Format("��%d�����㷨����", m_nIndex);
	m_pParent->SetWindowTextA(strStep);

	if (m_nLastAlgoType != m_pParent->GetScene()->nAlgoType)
	{
		m_nLastAlgoType = m_pParent->GetScene()->nAlgoType;

		ScErr err;
		// SCConfig���ڴ�й¶420bytes
		if (m_hConfig)
		{
			scCfgDestroy(m_hConfig);
			m_hConfig = NULL;
		}
		m_hConfig = scCfgCreate("", NULL);

		CString strVal = m_mapVal[m_nLastAlgoType];
		CString strInfo = m_mapInf[m_nLastAlgoType];
		err = scCfgLoadValStream(m_hConfig, (char*)strVal.GetString());
		err = scCfgLoadAddStream(m_hConfig, (char*)strInfo.GetString());

		CRect rect;
		this->GetClientRect(&rect);

		if (m_hTree)
		{
			VT_Destroy(m_hTree);
			m_hTree = NULL;
		}

		m_hTree = VT_Create(fPARAM_SaveParamCallBack, fPARAM_SetParamCallBack, rect, this, IDC_TREE_CONFIG);
		VT_SetParam(m_hTree, (HSCConfig)m_hConfig, this);
	}
}

LRESULT CDlgAlgoParam::OnWizardBack()
{
	this->SaveValue();
	return 0;
}

BOOL CDlgAlgoParam::OnWizardFinish()
{
	this->SaveValue();
	return TRUE;
}

void CDlgAlgoParam::OnDestroy()
{
	CNewWizPage::OnDestroy();

	// TODO: �ڴ˴������Ϣ����������
	if (m_hTree)
	{
		VT_Destroy(m_hTree);
		m_hTree = NULL;
	}
}

BOOL CDlgAlgoParam::OnSaveParam(const char* key, void* val, VALUETYPE type)
{
	if (m_hConfig == NULL || key == NULL || val == NULL)
		return FALSE;

	switch (type)
	{
	case SC_TypeUint32:
		scCfgSetAttribValue_int(m_hConfig, key, *((int*)val));
		break;
	case SC_TypeFloat:
		scCfgSetAttribValue_float(m_hConfig, key, *((float*)val));
		break;
	case SC_TypeString:
		scCfgSetAttribValue_string(m_hConfig, key, *((char**)val));
		break;
	case SC_TypeEnum:
		scCfgSetAttribValue_enum(m_hConfig, key, *((int*)val));
		break;
	case SC_TypeBool:
		scCfgSetAttribValue_bool(m_hConfig, key, *((int*)val));
		break;
	case SC_TypeTime:
		scCfgSetAttribValue_time(m_hConfig, key, *((ScSystemTime**)val));
		break;
	default:
		return FALSE;
	}
	return TRUE;
}