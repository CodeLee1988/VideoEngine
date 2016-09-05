//////////////////////////////////////////////////////////////////////////
// �����İ��Ƽ���չ���޹�˾ 2008-02-09
// VionVision 
//////////////////////////////////////////////////////////////////////////
// ��Ҫ���ݣ������������ͳ�ƽ�����Ĳ�νṹ�����Ͽ� + �����/����ͳ�ƽ��
//////////////////////////////////////////////////////////////////////////

#pragma once

#define ID_MAX_LENGTH 128	//

#define VDSRC_Analog	1	// ģ����·��ƵԴ����Ƶֱ�ӽ���ɼ�����
#define VDSRC_Digital	2	// ������·��ƵԴ
#define VDSRC_AnalogDigital	3	// �����������ɼ�������ƵԴ
#define VDSRC_ServerFile 4	// λ����Ƶ�������ϵ�¼���ļ�
#define VDSRC_Unknown	-1		// δ֪

//////////////////////////////////////////////////////////////////////////
#define VasStatus_OffLine	0	// 0 - ����״̬
#define VasStatus_OnLine	1	// 1 - ����״̬

//////////////////////////////////////////////////////////////////////////
// 1:����;2:�Ѿ���������ͷ������û�����;3:�����������򵫱���ͣ;4:���˹������˹��������ڷ���
#define VAStatus_OffLine	-1	// -1 - ����״̬
#define VAStatus_NoSrc	1		// 1 - ����
#define VAStatus_HasSrc	2		// 2 - �Ѿ���������ͷ������û�����
#define VAStatus_Paused		3	// 3 - �����������򵫱���ͣ	
#define VAStatus_Working	4	// 4 - ���˹������˹��������ڷ���
#define VAStatus_LostFrame 100	// 100 - ��Ƶ��ʧ


// ��Ƶ���������� VAServer
struct vvtagVAServer
{
	TCHAR szID[ID_MAX_LENGTH];
	TCHAR szNIC[ID_MAX_LENGTH];	// ������ַ
	TCHAR szIP[ID_MAX_LENGTH];	// IP
	int   nLocalPort;
	TCHAR szRemark[ID_MAX_LENGTH];
	int  nConnected;			// 0 - δ���ӣ� 1 - ������
	// ��ʼ��
	vvtagVAServer() { Init(); }
	void Init(){
		memset( szID, 0, sizeof(szID) );
		memset( szNIC, 0, sizeof(szNIC) );
		memset( szIP, 0, sizeof(szIP) );
		nLocalPort = 2005;
		memset( szRemark, 0, sizeof(szRemark) );
		nConnected = 0;
	}

	vvtagVAServer& operator=(const vvtagVAServer & other)   
	{
		if(&other == this)
			return *this;
		memcpy( szID, other.szID, sizeof(szID) );
		memcpy( szNIC, other.szNIC, sizeof(szNIC) );
		memcpy( szIP, other.szIP, sizeof(szIP) );
		nLocalPort = other.nLocalPort;
		memcpy( szRemark, other.szRemark, sizeof(szRemark) );
		nConnected = other.nConnected;
		return *this;
	}
};

// ��Ƶ������ VA�� Video Analyzer
struct vvtagVA
{
	TCHAR szID[ID_MAX_LENGTH];	// VA��ʶ
	TCHAR szIP[ID_MAX_LENGTH];	// 
	TCHAR szNIC[ID_MAX_LENGTH];	// ������ַ
	TCHAR szVAServerID[ID_MAX_LENGTH];
	int nSeatNum;				// ��Ƶ�������
	int nStatus;

	//////////////////////////////////////////////////////////////////////////
	// ��ƵԴ��Ϣ
	TCHAR szVideoSrcName[ID_MAX_LENGTH];	// ��ƵԴ����
	TCHAR szVideoSrcCode[ID_MAX_LENGTH];	// ����ͷID
	TCHAR szVideoSrcValue[ID_MAX_LENGTH];	// ��ƵԴ·�����磺DaHeng CG Driver1��
	int nVideoSrcType;			// ��ƵԴ���ͣ�1-ģ����·��ƵԴ���ɼ�������2-������·��ƵԴ��3-����+ģ��

	// �����õ���Ƶ��������
	int nActiveAnalyzeCount;		// �����õ���Ƶ�������͵ĸ���
	int narrActAnalyzeTypeCode[30];	// �����õ���Ƶ�������͵ı�ʶ���絥��Խ�磬 ������������������ͳ��

	SYSTEMTIME stAnalyzeStartTime;	// �ϴΡ����ù��򡱵�ʱ��

	// ֧�ֵ���Ƶ��������
	int nAnalyzeTypeCount;
	int narrAnalyzeTypeCode[50];

	// ��ʼ��
	vvtagVA() { Init(); }
	void Init(){
				//---������Ϣ
				memset( szID, 0, sizeof(szID) );
				memset( szIP, 0, sizeof(szIP) );
				memset( szNIC, 0, sizeof(szNIC) );
				memset( szVAServerID, 0, sizeof(szVAServerID) );
				nSeatNum = -1;
				nStatus = -1;

				// ��ƵԴ��Ϣ
				memset( szVideoSrcName, 0, sizeof(szVideoSrcName) );	// ��ƵԴ����
				memset( szVideoSrcCode, 0, sizeof(szVideoSrcCode) );
				memset( szVideoSrcValue, 0, sizeof(szVideoSrcValue) );
				nVideoSrcType=VDSRC_Analog;

				// �����õ���Ƶ��������
				nActiveAnalyzeCount = 0;
				memset( narrActAnalyzeTypeCode, 0, sizeof(narrActAnalyzeTypeCode) );

				memset( &stAnalyzeStartTime, 0, sizeof(stAnalyzeStartTime) );

				// ֧�ֵ���Ƶ��������
				nAnalyzeTypeCount = 0;
				memset( narrAnalyzeTypeCode, 0, sizeof(narrAnalyzeTypeCode) );

	};

	vvtagVA& operator=(const vvtagVA & other)   
	{
		if(&other == this)
			return *this;
		memcpy( szID, other.szID, sizeof(szID) );
		memcpy( szIP, other.szIP, sizeof(szIP) );
		memcpy( szNIC, other.szNIC, sizeof(szNIC) );
		memcpy( szVAServerID, other.szVAServerID, sizeof(szVAServerID) );
		nSeatNum = other.nSeatNum;
		nStatus = other.nStatus;

		// ��ƵԴ��Ϣ
		memcpy( szVideoSrcName, other.szVideoSrcName, sizeof(szVideoSrcName) );	// ��ƵԴ����
		memcpy( szVideoSrcCode, other.szVideoSrcCode, sizeof(szVideoSrcCode) );
		memcpy( szVideoSrcValue, other.szVideoSrcValue, sizeof(szVideoSrcValue) );
		nVideoSrcType = other.nVideoSrcType;

		// �����õ���Ƶ��������
		nActiveAnalyzeCount = other.nActiveAnalyzeCount;
		memcpy( narrActAnalyzeTypeCode, other.narrActAnalyzeTypeCode, sizeof(narrActAnalyzeTypeCode) );

		stAnalyzeStartTime = other.stAnalyzeStartTime;

		// ֧�ֵ���Ƶ��������
		nAnalyzeTypeCount = other.nAnalyzeTypeCount;
		memcpy( narrAnalyzeTypeCode, other.narrAnalyzeTypeCode, sizeof(narrAnalyzeTypeCode) );
		return *this;
	}
};

// ����������һ��ֻ��szParamValue�б����ַ�����
struct vvtagFixLengthParam
{
	TCHAR szParamName[10][ID_MAX_LENGTH];
	TCHAR szParamValue[10][ID_MAX_LENGTH];
	int nParamCount;
	vvtagFixLengthParam() { Init(); }
	void Init() 
	{ 
		memset( szParamName, 0, sizeof(szParamName) );
		memset( szParamValue, 0, sizeof(szParamValue) );
		nParamCount = 0;
	}

	// ���ʹ��UniqueSetValue��UniqueGetValue����������szParamName��szParamValue��˵�������������е�ֵ��Ψһ��

	void UniqueSetValue( LPCTSTR szItemName, const void* cpValueBuf, long nBufSize)
	{
		int nCopyCount = nBufSize;
		if( nBufSize>ID_MAX_LENGTH )
			nCopyCount = ID_MAX_LENGTH;

		BOOL bExist = FALSE;
		for (int i=0; i<10; i++)
		{
			if( _tcscmp(szItemName, szParamName[i])==0 )
			{
				memcpy(szParamValue[i], cpValueBuf, nCopyCount);
				szParamValue[i][ID_MAX_LENGTH-1] = '\0';
				bExist = TRUE;
				break;
			}
		}
		if( !bExist && nParamCount<10 )
		{
			_tcscpy(szParamName[nParamCount], szItemName);
			memcpy(szParamValue[nParamCount], cpValueBuf, nCopyCount);
			szParamValue[nParamCount][ID_MAX_LENGTH-1] = '\0';
			nParamCount++;
		}
	}

	BOOL UniqueGetValue( LPCTSTR szItemName, IN OUT void* pValueBuf, IN long nValueSize)
	{
		int nCopyCount = nValueSize;
		if( nValueSize>ID_MAX_LENGTH )
			nCopyCount = ID_MAX_LENGTH;

		BOOL bExist = FALSE;
		for (int i=0; i<10; i++)
		{
			if( _tcscmp(szItemName, szParamName[i])==0 )
			{
				memcpy(pValueBuf, szParamValue[i], nCopyCount);
				bExist = TRUE;
				break;
			}
		}
		return bExist;
	}
};

// ����������
struct vvtagVarLengthParam 
{
	TCHAR szN1[ID_MAX_LENGTH];
	BYTE szV1[ID_MAX_LENGTH];

	TCHAR szN2[ID_MAX_LENGTH];
	BYTE szV2[ID_MAX_LENGTH];

	TCHAR szN3[ID_MAX_LENGTH];
	BYTE szV3[ID_MAX_LENGTH];

	TCHAR szBytesName[ID_MAX_LENGTH];
	unsigned int unBinarySize;	//
	BYTE *bypBinaryBuf;			//

	vvtagVarLengthParam() { Init(); }
	void Init() 
	{ 
		memset( szN1, 0, sizeof(szN1) );
		memset( szV1, 0, sizeof(szV1) );

		memset( szN2, 0, sizeof(szN2) );
		memset( szV2, 0, sizeof(szV2) );

		memset( szN3, 0, sizeof(szN3) );
		memset( szV3, 0, sizeof(szV3) );

		memset( szBytesName, 0, sizeof(szBytesName) );
		unBinarySize = 0;
		bypBinaryBuf = NULL;
	}
	void UnInit()
	{
		if ( NULL != bypBinaryBuf )
		{
			delete bypBinaryBuf;
			bypBinaryBuf = NULL;
		}
	}
};

// ��־�ṹ��
struct vvtagLog
{
	TCHAR szID[ID_MAX_LENGTH];
	TCHAR szLogTypeName[ID_MAX_LENGTH];
	TCHAR szSource[ID_MAX_LENGTH];
	TCHAR szCreater[ID_MAX_LENGTH];
	TCHAR szLogText[ID_MAX_LENGTH];

	SYSTEMTIME stLogTime;
	int nLogTypeID;

	vvtagLog() { Init(); }
	void Init()
	{
		nLogTypeID = 0;
		memset(szID, 0, sizeof(szID));
		memset(szLogTypeName, 0, sizeof(szLogTypeName));
		memset(szSource, 0, sizeof(szSource));
		memset(szCreater, 0, sizeof(szCreater));
		memset(szLogText, 0, sizeof(szLogText));
		memset(&stLogTime, 0, sizeof(stLogTime));
	}

	vvtagLog& operator=(const vvtagLog & other)   
	{
		if (&other == this)
			return *this;
		
		memcpy( szID, other.szID, sizeof(szID) );
		memcpy( szLogTypeName, other.szLogTypeName, sizeof(szLogTypeName) );
		memcpy( szSource, other.szSource, sizeof(szSource) );
		memcpy( szCreater, other.szCreater, sizeof(szCreater) );
		memcpy( szLogText, other.szLogText, sizeof(szLogText) );

		stLogTime = other.stLogTime;
		nLogTypeID = other.nLogTypeID;

		return *this;
	}
};

struct vvtagAppStatus
{
	TCHAR szID[ID_MAX_LENGTH];
	TCHAR szTypeName[ID_MAX_LENGTH];
	TCHAR szSource[ID_MAX_LENGTH];
	TCHAR szValue[ID_MAX_LENGTH];
	TCHAR szRemark[ID_MAX_LENGTH];

	SYSTEMTIME stUpdateTime;
	int nTypeId;

	vvtagAppStatus() { Init(); }
	void Init()
	{
		memset(szID, 0,sizeof(szID));
		memset(szTypeName, 0,sizeof(szTypeName));
		memset(szSource, 0,sizeof(szSource));
		memset(szValue, 0,sizeof(szValue));
		memset(szRemark, 0,sizeof(szRemark));

		memset(&stUpdateTime, 0, sizeof(stUpdateTime));
		
		nTypeId = 0;
	}

	vvtagAppStatus& operator=(const vvtagAppStatus & other)   
	{
		if (&other == this)
			return *this;

		memcpy( szID, other.szID, sizeof(szID) );
		memcpy( szTypeName, other.szTypeName, sizeof(szTypeName) );
		memcpy( szSource, other.szSource, sizeof(szSource) );
		memcpy( szValue, other.szValue, sizeof(szValue) );
		memcpy( szRemark, other.szRemark, sizeof(szRemark) );

		stUpdateTime = other.stUpdateTime;

		nTypeId = other.nTypeId;

		return *this;
	}
};

struct vvtagUploadTask
{
	int nChlNo;
	SYSTEMTIME stBeginTime;
	SYSTEMTIME stEndTime;

	vvtagUploadTask(){}
	void Init()
	{
		
	}
};