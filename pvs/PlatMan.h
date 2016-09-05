#pragma once

#include "PlatformInterface.h"

typedef IPlatformInterface* (CALLBACK *PCreateVmo)();
typedef void (CALLBACK *PDestroyVmo)(IPlatformInterface*);

enum LogType
{
	LT_MSG, // ��Ϣ
	LT_ERR  // ����
};
typedef void (CALLBACK *POutputLog)(LPCTSTR,LogType,DWORD);

class VendorModule
{
public:
	HMODULE hModule; // ģ����
	PCreateVmo pCreateVmo;
	PDestroyVmo pDestroyVmo;
	IPlatformInterface* pPlatform;
	TCHAR szModuleFileName[MAX_PATH]; // ģ��·��
	BOOL bAbsModuleFilePath; // ģ��·���Ƿ��Ǿ���·��
	TCHAR szModuleEnvDir[MAX_PATH]; // ģ����ػ���Ŀ¼
	BOOL bAbsModuleEnvDir; // ģ����ػ���Ŀ¼�Ƿ��Ǿ���Ŀ¼
	BOOL bFreeLib;

	VendorModule()
	{
		this->hModule = NULL;
		this->pCreateVmo = NULL;
		this->pDestroyVmo = NULL;
		this->pPlatform = NULL;
		this->szModuleFileName[0] = _T('\0');
		this->bAbsModuleFilePath = FALSE; // Ĭ�����·��
		this->szModuleEnvDir[0] = _T('\0');
		this->bAbsModuleEnvDir = FALSE; // Ĭ�����·��
		this->bFreeLib = TRUE;
	}
	~VendorModule()
	{
		this->Unload();
	}

	inline IPlatformInterface* CreateVmo()
	{
		if (!this->pPlatform && this->pCreateVmo)
			this->pPlatform = this->pCreateVmo();

		return this->pPlatform;
	}
	inline void DestroyVmo()
	{
		if (this->pDestroyVmo)
		{
			this->pDestroyVmo(this->pPlatform);
			this->pPlatform = NULL;
		}
	}

	void Unload()
	{
		this->pCreateVmo = NULL;
		this->pDestroyVmo = NULL;

		if (this->hModule)
		{
			// ��ע�⡿���������ΰ껽ӿڣ���Ҫ����FreeLibrary�������������FreeLibrary��
			// ��ע�⡿��������д󻪵Ľӿڣ�����FreeLibrary��������һ��ʱ��
			if (this->bFreeLib)
				::FreeLibrary(this->hModule);
			this->hModule = NULL;
		}
	}
};

#include <list>
using std::list;

typedef list<VendorModule*> VendorModulePtrList;

// ������س���ģ����
class CPlatMan
{
public:
	CPlatMan(void);
	~CPlatMan(void);

	void LoadVendorModules();
	void InitVendorModules(IPlatformNotify *pTrdNotify, HWND hMainWnd, HWND hPlayWnds[], int nPlayCount);
	void UninitVendorModules();
	void SetOutputLogCallback(POutputLog pfn, DWORD user = 0);

private:
	BOOL GetModuleFileList(LPCTSTR lpszVendorPluginMapFile);
	BOOL LoadModule(VendorModule* pvm);

	void OutputErrorMsg(LogType type, LPCTSTR lpszFormat, ...);

private:
	VendorModulePtrList m_lstVendorModulePtr;
	POutputLog m_pOutputLog;
	DWORD m_dwOutputLogUser;
	TCHAR m_szCurrentPath[MAX_PATH];
};
