#pragma once

#define VVRESULT_API extern "C" __declspec(dllexport)

typedef void* HVRM;	//����Ƶ�����������ģ�顱���

#define RES_Vncount 1	// ����ͳ�ƽ��
#define RES_Vnguard 2	// �¼�����
#define RES_Vnabbh 3	// �쳣��Ϊ����
#define RES_Vndiag 4	// ��Ƶ��Ͻ��
#define RES_Vnlpr 5		// ����ʶ����

VVRESULT_API HVRM VRM_Create(void* pParam, int nParamLength);
VVRESULT_API void VRM_Destroy(HVRM hvrm);	// Close the result manager
VVRESULT_API void VRM_Save(HVRM hvrm, int nResType, const void *pData, int nDataSize);	// Save data to result manager
VVRESULT_API int VRM_GetError(HVRM hvrm);	// Not implemented
VVRESULT_API void VRM_SetOptions(HVRM hvrm, LPCTSTR ctsDataName, LPCTSTR ctsData);
VVRESULT_API void VRM_GetData(HVRM hvrm, LPCTSTR ctsDataName, void **pData);

//VRM_Create::pParam�����ã�
//rmtype=tcp|ip=127.0.0.1|Port=2008
//rmtype=udp|ip=127.0.0.1|Port=6060
//rmtype=db|DBtype=0|dbserver=127.0.0.1|dbname=VionGuard.mdb|dbuser=admin|dbpass=
//rmtype=smtp|smtpserver=smtp.sina.com|account=vionql|password=vionql|from=vionql@sina.com|to=boozhidao@hotmail.com

//VRM_SetOptions �� ����xml�����ļ���·��
//VRM_SetOptions( _T("ConfigFilePath"), _T("d:\xxx\...\VionAppConfig.xml") );

// ���ݿ����ش����Ѿ�ע�͵� added by weil 20120810