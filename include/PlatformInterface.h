#ifndef __PLATFORMINTERFACE_H__
#define __PLATFORMINTERFACE_H__

#include "PlatformNotify.h"
#include "PvsDef.h"
#ifdef _LINUX
#include <SCFileUtils.h>
#endif

#define PLAT_RESULT long
#define PLAT_OK		0
#define PLAT_FAILED	1

#define PLAT_BOOL   long
#define PLAT_TRUE   1
#define PLAT_FALSE  0

// nOpCode����
#define PVS_DEVICE_ADD  	1 // ����豸
#define PVS_DEVICE_MODIFY	2 // �޸��豸
#define PVS_DEVICE_DELETE	3 // ɾ���豸
#define PVS_CAMERA_MODIFY   4 // �޸���ƵԴ
#define PVS_CAMERA_DELETE   5 // ɾ����ƵԴ


// Vendor
#define MAX_VENDOR_LEN  MAX_NAME_LEN

// Common type
#define PVS_PTZ_CONTROL			     375
#define PVS_SAVE_RECORD_FILE         378 // SaveRecord
#define PVS_SAVE_RECORD_BY_TIME		 379
#define PVS_RECORD_BUFFER_TIMESPAN	 380
#define PVS_DEVICE_CHANGED           390 // DeviceChanged
#define PVS_DEVICE_UPDATE			 391
#define PVS_GET_DEVICE_CONFIG		 400 // TCHAR*
#define PVS_SET_DEVICE_CONFIG		 401 // const TCHAR*
#define PVS_GET_CAMERA_STATUS		 402 // PVS_CameraStatus*
#define PVS_ADD_REAL_CHANNEL	     403 // PVS_RealPlay
#define PVS_TurnOn_PrintInfo         404  //tunrnONPrintInfo
#define PVS_Capture_Get				 405 //�����ץͼ
#define PVS_OneHa64_Get 			 406//��ȡһ��H264ͼ

//////////////////////////////////////////////////////////////////////////
#pragma pack(push)
#pragma pack(4)

// Save Record File
struct SaveRecord
{
	node::PCameraNode cam; // ����ڵ�
	char file[MAX_PATH]; // �ļ�·����
	bool stop; // ֹͣ¼��
};

// �豸�޸�
struct ChannelChanged
{
	char id[MAX_NAME_LEN]; // ͨ��ID
	char name[MAX_NAME_LEN]; // ͨ������
	int channel; // ͨ����
    char playid[MAX_NAME_LEN];
    char szPlayContext[MAX_NAME_LEN]; // ���Ų���
	ChannelChanged* next; // ��һ��ͨ��

	ChannelChanged()
	{
		next = NULL;
        memset(playid, 0, MAX_NAME_LEN);
	}
	~ChannelChanged()
	{
		if (next)
		{
			delete next;
			next = NULL;
		}
	}
};
struct DeviceChanged
{
	int mode; // �޸Ķ����� ��nOpCode���壩
	char ip[MAX_IP_LEN]; // IP
	char name[MAX_NAME_LEN]; // ����
	int port; // �˿�
	char user[MAX_NAME_LEN]; // �û�
	char pass[MAX_NAME_LEN]; // ����
	char szExpand[2048];
	ChannelChanged* channels; // ͨ������
	DeviceChanged* next; // ��һ���豸

	DeviceChanged()
	{
		mode = -1;
		ip[0] = '\0';
		name[0] = '\0';
		port = -1;
		user[0] = '\0';
		pass[0] = '\0';
		szExpand[0] = '\0';
		channels = NULL;
		next = NULL;
	}
	~DeviceChanged()
	{
		mode = -1;
		ip[0] = '\0';
		name[0] = '\0';
		port = -1;
		user[0] = '\0';
		pass[0] = '\0';
		szExpand[0] = '\0';

		if (channels)
		{
			delete channels;
			channels = NULL;
		}
		if (next)
		{
			delete next;
			next = NULL;
		}
	}
};

#pragma pack(pop)

//////////////////////////////////////////////////////////////////////////

class IPlatformInterface
{
public:
	IPlatformInterface(LPCTSTR lpszVendorID)
		: m_pTrdNotify(NULL)
	{ 
		this->m_pVendorNode = new node::VendorNode;
		this->m_pVendorNode->hVendor = this;
		_tcscpy(m_pVendorNode->szID, lpszVendorID);
		_tcslwr(m_pVendorNode->szID); // Convert the string to lowercase.
		_tcscpy(m_pVendorNode->szName, lpszVendorID);
		_tcsupr(m_pVendorNode->szName); // Convert the string to uppercase.

		m_hVendorModule = NULL;
		m_szVendorPath[0] = _T('\0');
	}
	virtual ~IPlatformInterface()
	{
		if (this->m_pVendorNode != NULL)
		{
			delete this->m_pVendorNode;
			this->m_pVendorNode = NULL;
		}
	}

public:
	// ����ȫ�ֵ���һ�εĿ��ʼ������
	// ������pTrdNotify �C ֪ͨ����ӿڶ���ָ�룻
	//  	 hMainWnd �C �����洰�ھ����
	//  	 hPlayWnds �C ���Ŵ��ھ����
	//	     nPlayCount �C ���Ŵ��ڸ�����
	virtual PLAT_RESULT Initialize(IPlatformNotify *pTrdNotify, HWND hMainWnd, HWND hPlayWnds[], int nPlayCount) = 0;
	// ����ȫ�ֵ���һ�εĿⷴ��ʼ������
	virtual PLAT_RESULT UnInitialize() = 0;
	// ���³�ʼ��
	virtual PLAT_RESULT Reinitialize() = 0;

	// ���¼����豸�б�
	virtual PLAT_RESULT ReloadDevice() = 0;

	// ��¼��������Ҫʱ��д
	virtual PLAT_RESULT Login(LPCTSTR lpszDevice = NULL)
	{
		return PLAT_OK;
	}
	// �˳���������Ҫʱ��д
	virtual PLAT_RESULT Logout(LPCTSTR lpszDevice = NULL)
	{
		return PLAT_OK;
	}

	// ��ʼԤ��
	virtual PLAT_RESULT StartDecodeFrame(node::PCameraNode pCamNode, void* pvUser, int bMode=0) = 0;
	// ֹͣԤ��
	virtual PLAT_RESULT StopDecodeFrame(node::PCameraNode pCamNode) = 0;

	// �ͷ�pvs��Դ
	virtual PLAT_RESULT ReleasePVSResource(node::PCameraNode, ResourceHandle hResrc)
	{
		return PLAT_FAILED;
	}

	// �豸�ӿڶ��У�ƽ̨�ӿ�û��
	// ����µ��豸pOriginalNode����
	// ����������޸ķ���PLAT_FAILED����
	virtual PLAT_RESULT SynchDevice(long nOpCode/*������*/, node::PBaseNode pOriginalNode/*ԭ�ڵ�����*/, node::PBaseNode pNode/*��ӻ��޸ĵ��豸��ʱ�ڵ�����*/)
	{ 
		return PLAT_FAILED;
	}

	// ͨ�ýӿ�
	virtual long CommonProc(
		long nType,
		void* pData){ return 0; }

	// �ж��Ƿ��Ǹõ�����ģ��ʵ�ֵĽӿ�
	// ����PLAT_TRUE-�ǣ�PLAT_FALSE-��
	virtual PLAT_BOOL IsTheVendor(LPCTSTR lpszVendorName)
	{
		if (lpszVendorName == NULL || _tcslen(lpszVendorName) == 0)
			return PLAT_FALSE;

		TCHAR szVendor[MAX_VENDOR_LEN];
		_tcscpy(szVendor, lpszVendorName);
		_tcslwr(szVendor); // TRUE- an error occurred
		if (_tcscmp(szVendor, m_pVendorNode->szID) == 0)
			return PLAT_TRUE;
		else
			return PLAT_FALSE;
	}

	// ��ȡʵ�ֽӿڵĵ�����ģ������
	// ����nSize���ַ������С�������С���򷵻�PLAT_FALSE������nSize����ʵ����Ҫ�Ĵ�С
	// ����PLAT_TRUE-�ɹ���PLAT_FALSE-ʧ��
	inline PLAT_BOOL GetTheVendorID(LPTSTR lpszVendorID, int& nSize)
	{
		int len = (int)_tcslen(m_pVendorNode->szID);
		if (lpszVendorID == NULL || nSize <= len)
		{
			nSize = len+1;
			return PLAT_FALSE;
		}

		_tcsnset(lpszVendorID, 0, nSize);
		_tcsncpy(lpszVendorID, m_pVendorNode->szID, len);
		lpszVendorID[len] = _T('\0');

		return PLAT_TRUE;
	}

	// ��ȡʵ�ֽӿڵĵ�����ģ������
	// ����nSize���ַ������С�������С���򷵻�PLAT_FALSE������nSize����ʵ����Ҫ�Ĵ�С
	// ����PLAT_TRUE-�ǣ�PLAT_FALSE-��
	inline PLAT_BOOL GetTheVendorName(LPTSTR lpszVendorName, int& nSize)
	{
		int len = (int)_tcslen(m_pVendorNode->szName);
		if (lpszVendorName == NULL || nSize <= len)
		{
			nSize = len+1;
			return PLAT_FALSE;
		}

		_tcsnset(lpszVendorName, 0, nSize);
		_tcsncpy(lpszVendorName, m_pVendorNode->szName, len);
	}

	inline void OutputLog(LPCTSTR pszLog, LPCTSTR FuncName=_T(""), LPCTSTR FileName=_T(""), long Line=__LINE__, long Level=LEV_INFO)
	{
		if (m_pTrdNotify != NULL)
			m_pTrdNotify->OnOutputLog(pszLog, FuncName, FileName, Line, Level);
	}

	// ��ȡ���ҽڵ�����
	inline node::PVendorNode GetVendorNode() const
	{
		return this->m_pVendorNode;
	}

	void SetModuleHanle(HMODULE hModule)
	{
		if (this->m_hVendorModule)
			return;

		this->m_hVendorModule = hModule;

#ifdef _LINUX
		scGetModulePath(m_szVendorPath);
		_tcscat(m_szVendorPath, _T("/vmplugins/"));
#else
		TCHAR szCurrModuleFileName[MAX_PATH] = {0};
		TCHAR szDir[MAX_PATH] = {0};
		TCHAR szDrv[MAX_PATH] = {0};

		GetModuleFileName(hModule, szCurrModuleFileName, MAX_PATH);
		_tsplitpath(szCurrModuleFileName, szDrv, szDir, NULL, NULL);
		// ��ǰģ��·��
		_tmakepath(m_szVendorPath, szDrv, szDir, NULL, NULL);
#endif
	}

	inline LPCTSTR GetCurrentModulePath() const
	{
		return m_szVendorPath;
	}

protected:
	IPlatformNotify *m_pTrdNotify;
	node::PVendorNode m_pVendorNode; // ���ҽڵ����ݣ�ֻ��һ��
	HMODULE m_hVendorModule; // ����ģ����
	TCHAR m_szVendorPath[MAX_PATH]; // ����ģ��·��
};

//////////////////////////////////////////////////////////////////////////

#endif
