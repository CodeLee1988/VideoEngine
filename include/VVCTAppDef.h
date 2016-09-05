#pragma once
#include <tchar.h>
#include <wtypes.h>
#include "VasCDef.h"

#define MY_SZLENGTH 128

#define IMG_BMP 0
#define IMG_JPG 1
#define IMG_AVI 2

//////////////////////////////////////////////////////////////////////////
// �澯����
#define AltLel_0	0	// �Ǹ澯��������¼
#define AltLel_1	1	// һ���澯�����س̶ȣ��ܵͣ�
#define AltLel_2	2	// �����澯�����س̶ȣ��ͣ�
#define AltLel_3	3	// �����澯�����س̶ȣ�һ�㣩
#define AltLel_4	4	// �ļ��澯�����س̶ȣ��ܸߣ�
#define AltLel_5	5	// �弶�澯�����س̶ȣ���ߣ�

//-----------------------------------------------------
//	����������
//-----------------------------------------------------
#define IMG_BMP 0
#define IMG_JPG 1
#define IMG_AVI 2
typedef long VAS_BINARY_TYPE;

////////////////////////////////////Ӧ�ü�����//////////////////////////////////////
// ����ͳ�ƽ��
struct vvtagVncountResult 
{
	TCHAR szUniqueResultID[MY_SZLENGTH];	// ���ID
	//
	TCHAR szVAID[MY_SZLENGTH];			// ��Ƶ������ID
	TCHAR szVAServerID[MY_SZLENGTH];	// VAServerID
	long  nDeviceNo;					// ͨ����
	TCHAR szVideoSrcCode[MY_SZLENGTH];	// �����ID
	TCHAR szVideoSrcName[MY_SZLENGTH];	// ���������

	SYSTEMTIME tmLogTime;		// �Ǽ�ʱ��
	long nResultFlag;			// 1-nIns��nOutsΪ����������00:00�������ڵĽ��������� 2-nIns��nOutsΪһ��ָ��ʱ�εĽ��������� 3-һ����ۼ�����
	long nIns;
	long nOuts;

	long nAlertLevel;			// ��������

	//---
	// ��ʼ��
	vvtagVncountResult() { Init(); }
	void Init(){
				memset(szUniqueResultID, 0, sizeof(szUniqueResultID));
				//---
				memset(szVAID, 0, sizeof(szVAID) );
				memset(szVAServerID, 0, sizeof(szVAServerID) );
				nDeviceNo = -1;
				memset(szVideoSrcCode, 0, sizeof(szVideoSrcCode) );
				memset(szVideoSrcName, 0, sizeof(szVideoSrcName) );

				memset( &tmLogTime, 0, sizeof(tmLogTime) );
				nResultFlag = 1;
				nIns = 0;
				nOuts = 0;
				//---
				nAlertLevel = 0;
	};
	vvtagVncountResult& operator=(const vvtagVncountResult & other)   
	{
		if(&other == this)
			return *this;
		_tcscpy(szUniqueResultID, other.szUniqueResultID);
		//
		_tcscpy(szVAID, other.szVAID);
		_tcscpy(szVAServerID, other.szVAServerID);
		nDeviceNo = other.nDeviceNo;
		_tcscpy(szVideoSrcCode, other.szVideoSrcCode);
		_tcscpy(szVideoSrcName, other.szVideoSrcName);
	
		tmLogTime = other.tmLogTime;
		nResultFlag = other.nResultFlag;
		nIns = other.nIns;
		nOuts = other.nOuts;

		nAlertLevel = other.nAlertLevel;
		return *this;
	}
};

// ����ץͼ�����ṹ
struct VasPvsAlarmCapture
{
	TCHAR szUniqueResultID[MY_SZLENGTH];	// ���ID
	TCHAR szVideoSrcCode[MY_SZLENGTH];	// �����ID
	long nChannelNo;		// ��ӦPVS���Ŵ���źͷ������򴰸�ţ�0-15

	VasNetBinary pic;	// PVS��ȡ��ͼƬ��Ϣ

	VasPvsAlarmCapture()
	{
		szUniqueResultID[0] = '\0';
		szVideoSrcCode[0] = '\0';
		nChannelNo = -1;
		pic.pBuf = NULL;
		pic.tszFileName[0] = 0;
		pic.lSize = 0;
		pic.nType = IMG_JPG;
	}
};

struct VasPvsAlarmVideo
{
	TCHAR szUniqueResultID[MY_SZLENGTH];	// ���ID
	TCHAR szVideoSrcCode[MY_SZLENGTH];	// �����ID
	long nChannelNo;		// ��ӦPVS���Ŵ���źͷ������򴰸�ţ�0-15
	SYSTEMTIME stBeginTime; // ��ʼʱ��
	SYSTEMTIME stEndTime;	// ���ʱ��
	VasNetBinary video;		// PVS�����¼����Ϣ
};

struct VasPvsGuardResult 
{
	TCHAR szUniqueResultID[MY_SZLENGTH];	// ���ID
	//
	TCHAR szVAID[MY_SZLENGTH];			// ��Ƶ������ID
	TCHAR szVAServerID[MY_SZLENGTH];	// VAServerID
	long  nDeviceNo;					// ͨ����
	TCHAR szVideoSrcCode[MY_SZLENGTH];	// �����ID
	TCHAR szVideoSrcName[MY_SZLENGTH];	// ���������

	SYSTEMTIME tmAlertTime;				// ����ʱ��
	long nEventType;					// �¼�����

	// �¼���Ϣ
	long nRuleID;			// ��Υ���Ĺ���
	long nObjectType;		// ��������
	long narrObjectPos[4];	// ����λ��
	long nScaleAlert;		//ʵ�ʱ仯����
	SYSTEMTIME	EntryTime;	//����ʱ�䣨For�����ǻ�������

	long nAlertLevel;					// ��������

	// ͼƬ��Ϣ
	VasNetBinary pic;
	VasNetBinary video;
	// ��ʼ��
	VasPvsGuardResult() 
	{
		memset(szUniqueResultID, 0, sizeof(szUniqueResultID));
		//---
		memset(szVAID, 0, sizeof(szVAID) );
		memset(szVAServerID, 0, sizeof(szVAServerID) );
		nDeviceNo = -1;
		memset(szVideoSrcCode, 0, sizeof(szVideoSrcCode) );
		memset(szVideoSrcName, 0, sizeof(szVideoSrcName) );

		memset( &tmAlertTime, 0, sizeof(tmAlertTime) );
		nEventType = -1;

		// �¼���Ϣ
		nRuleID = -1;			// ��Υ���Ĺ���
		nObjectType = 3;		// ��������
		memset(narrObjectPos, 0, sizeof(narrObjectPos) );	// ����λ��
		nScaleAlert = 0;		//ʵ�ʱ仯����
		memset(&EntryTime, 0, sizeof(EntryTime) );	//����ʱ�䣨For�����ǻ�������

		nAlertLevel = 3;
	};

	~VasPvsGuardResult()
	{ 
		pic.UnInit();
		video.UnInit();
	}  
};

// �¼����ʵʱ�������
struct vvtagVnguardResult 
{
	TCHAR szUniqueResultID[MY_SZLENGTH];	// ���ID
	//
	TCHAR szVAID[MY_SZLENGTH];			// ��Ƶ������ID
	TCHAR szVAServerID[MY_SZLENGTH];	// VAServerID
	long  nDeviceNo;					// ͨ����
	TCHAR szVideoSrcCode[MY_SZLENGTH];	// �����ID
	TCHAR szVideoSrcName[MY_SZLENGTH];	// ���������

	SYSTEMTIME tmAlertTime;				// ����ʱ��
	long nEventType;					// �¼�����

	// �¼���Ϣ
	long nRuleID;			// ��Υ���Ĺ���
	long nObjectType;		// ��������
	long narrObjectPos[4];	// ����λ��
	long nScaleAlert;		//ʵ�ʱ仯����
	SYSTEMTIME	EntryTime;	//����ʱ�䣨For�����ǻ�������

	long nAlertLevel;					// ��������

	// ͼƬ��Ϣ
	TCHAR szResultImageID[MY_SZLENGTH];	// ��Ƶ�������ͼƬID
	unsigned long unBinaryType;	// ͼƬ��Ϣ��ImgType, ImgSize��char* pJpgBuf��
	unsigned long unBinarySize;	// 
	byte *bypBinaryBuf;			//

	// ��ʼ��
	vvtagVnguardResult() { Init(); }
	void Init(){
		memset(szUniqueResultID, 0, sizeof(szUniqueResultID));
		//---
		memset(szVAID, 0, sizeof(szVAID) );
		memset(szVAServerID, 0, sizeof(szVAServerID) );
		nDeviceNo = -1;
		memset(szVideoSrcCode, 0, sizeof(szVideoSrcCode) );
		memset(szVideoSrcName, 0, sizeof(szVideoSrcName) );

		memset( &tmAlertTime, 0, sizeof(tmAlertTime) );
		nEventType = -1;

		// �¼���Ϣ
		nRuleID = -1;			// ��Υ���Ĺ���
		nObjectType = 3;		// ��������
		memset(narrObjectPos, 0, sizeof(narrObjectPos) );	// ����λ��
		nScaleAlert = 0;		//ʵ�ʱ仯����
		memset(&EntryTime, 0, sizeof(EntryTime) );	//����ʱ�䣨For�����ǻ�������

		nAlertLevel = 3;

		// ͼƬ��Ϣ
		memset(szResultImageID, 0, sizeof(szResultImageID) );
		unBinaryType = IMG_JPG;
		unBinarySize = 0;
		bypBinaryBuf = NULL;
	};
	void UnInit()
	{
		if( NULL != bypBinaryBuf )
		{
			delete bypBinaryBuf;
			bypBinaryBuf = NULL;
		}
	}

	void CopyFromOther(const vvtagVnguardResult& other)
	{
		_tcscpy(szUniqueResultID, other.szUniqueResultID);
		//
		_tcscpy(szVAID, other.szVAID);
		_tcscpy(szVAServerID, other.szVAServerID);
		nDeviceNo = other.nDeviceNo;
		_tcscpy(szVideoSrcCode, other.szVideoSrcCode);
		_tcscpy(szVideoSrcName, other.szVideoSrcName);

		tmAlertTime = other.tmAlertTime;
		nEventType = other.nEventType;

		nRuleID = other.nRuleID;				// ��Υ���Ĺ���
		nObjectType = other.nObjectType;		// ��������
		memcpy(narrObjectPos, other.narrObjectPos, sizeof(other.narrObjectPos));	// ����λ��
		nScaleAlert = other.nScaleAlert;		//ʵ�ʱ仯����
		EntryTime = other.EntryTime;			//����ʱ�䣨For�����ǻ�������

		nAlertLevel = other.nAlertLevel;

		_tcscpy(szResultImageID, other.szResultImageID);
		if (other.bypBinaryBuf!=NULL && other.unBinarySize>0)
		{
			bypBinaryBuf = new byte[other.unBinarySize];
			memcpy(bypBinaryBuf, other.bypBinaryBuf, other.unBinarySize);
		}
		else
		{
			bypBinaryBuf = NULL;
		}
		unBinaryType = other.unBinaryType;
		unBinarySize = other.unBinarySize;
	}

	vvtagVnguardResult(const vvtagVnguardResult& other)
	{
		CopyFromOther(other);
	}

	vvtagVnguardResult& operator=(const vvtagVnguardResult & other)   
	{
		if(&other == this)
			return *this;
		UnInit();
		CopyFromOther(other);

		return *this;
	}
	~vvtagVnguardResult() 
	{ 
		UnInit();
	}  
};

// ��Ƶ��Ͻ��
struct vvtagVndiagResult 
{
	TCHAR szUniqueResultID[MY_SZLENGTH];	// ���ID
	//
	TCHAR szVAID[MY_SZLENGTH];			// ��Ƶ������ID
	TCHAR szVAServerID[MY_SZLENGTH];	// VAServerID
	long  nDeviceNo;					// ͨ����
	TCHAR szVideoSrcCode[MY_SZLENGTH];	// �����ID
	TCHAR szVideoSrcName[MY_SZLENGTH];	// ���������
	SYSTEMTIME tmAlertTime;				// ����ʱ��

	long nSwitchScore;	// �л���Ͻ��
	long nSignalScore;	// �ź���Ͻ��
	
	long nBlurScore;	// ������
	long nBrightScore;	// ���ȹ���
	long nDarkScore;	// ���ȹ���
	long nColorScore;	// ƫɫ
	long nNoiseScore;	// ��������
	long nSnowScore;	// ѩ������
	long nPtzScore;		// PTZ��Ͻ��
	long nFreezeScore;	// ������Ͻ��

	long nAlertLevel;	// ��������
	
	// ͼƬ��Ϣ
	TCHAR szResultImageID[MY_SZLENGTH];	// ��Ƶ�������ͼƬID
	unsigned long unBinaryType;	// ͼƬ��Ϣ��ImgType, ImgSize��char* pJpgBuf��
	unsigned long unBinarySize;	// 
	byte *bypBinaryBuf;			//

	// ��ʼ��
	vvtagVndiagResult() { Init(); }
	void Init(){
		memset(szUniqueResultID, 0, sizeof(szUniqueResultID));
		//---
		memset(szVAID, 0, sizeof(szVAID) );
		memset(szVAServerID, 0, sizeof(szVAServerID) );
		nDeviceNo = -1;
		memset(szVideoSrcCode, 0, sizeof(szVideoSrcCode) );
		memset(szVideoSrcName, 0, sizeof(szVideoSrcName) );
		memset( &tmAlertTime, 0, sizeof(tmAlertTime) );

		nSwitchScore = 0;	// �л���Ͻ��
		nSignalScore = 0;	// �ź���Ͻ��

		nBlurScore = 0;		// ������
		nBrightScore = 0;	// ���ȹ���
		nDarkScore = 0;		// ���ȹ���
		nColorScore = 0;	// ƫɫ
		nNoiseScore = 0;	// ��������
		nSnowScore = 0;		// ѩ������
		nPtzScore = 0;		// PTZ��Ͻ��
		nFreezeScore = 0;	// ������Ͻ��

		nAlertLevel = 0;

		// ͼƬ��Ϣ
		memset(szResultImageID, 0, sizeof(szResultImageID) );
		unBinaryType = IMG_JPG;
		unBinarySize = 0;
		bypBinaryBuf = NULL;
	};
	void UnInit()
	{
		if( NULL != bypBinaryBuf )
		{
			delete bypBinaryBuf;
			bypBinaryBuf = NULL;
		}
	}

	void CopyFromOther(const vvtagVndiagResult& other)
	{
		_tcscpy(szUniqueResultID, other.szUniqueResultID);
		//
		_tcscpy(szVAID, other.szVAID);
		_tcscpy(szVAServerID, other.szVAServerID);
		nDeviceNo = other.nDeviceNo;
		_tcscpy(szVideoSrcCode, other.szVideoSrcCode);
		_tcscpy(szVideoSrcName, other.szVideoSrcName);
		tmAlertTime = other.tmAlertTime;

		nSwitchScore = other.nSwitchScore;
		nSignalScore = other.nSignalScore;

		nBlurScore = other.nBlurScore;
		nBrightScore = other.nBrightScore;
		nDarkScore = other.nDarkScore;
		nColorScore = other.nColorScore;
		nNoiseScore = other.nNoiseScore;
		nSnowScore = other.nSnowScore;
		nPtzScore = other.nPtzScore;
		nFreezeScore = other.nFreezeScore;

		nAlertLevel = other.nAlertLevel;

		_tcscpy(szResultImageID, other.szResultImageID);
		if (other.bypBinaryBuf!=NULL && other.unBinarySize>0)
		{
			bypBinaryBuf = new byte[other.unBinarySize];
			memcpy(bypBinaryBuf, other.bypBinaryBuf, other.unBinarySize);
		}
		unBinaryType = other.unBinaryType;
		unBinarySize = other.unBinarySize;
	}

	vvtagVndiagResult(const vvtagVndiagResult& other)
	{
		CopyFromOther(other);
	}

	vvtagVndiagResult& operator=(const vvtagVndiagResult & other)   
	{
		if(&other == this)
			return *this;
		CopyFromOther(other);

		return *this;
	}
	~vvtagVndiagResult()
	{
		UnInit();
	}
};

// ����ʶ����
struct vvtagVnlprResult 
{
	TCHAR szUniqueResultID[MY_SZLENGTH];	// ���ID
	//
	TCHAR szVAID[MY_SZLENGTH];			// ��Ƶ������ID
	TCHAR szVAServerID[MY_SZLENGTH];	// VAServerID
	long  nDeviceNo;						// ͨ����
	TCHAR szVideoSrcCode[MY_SZLENGTH];	// �����ID
	TCHAR szVideoSrcName[MY_SZLENGTH];	// ���������
	SYSTEMTIME tmLogTime;				// �Ǽ�ʱ��

	long nPlateRecogMode;				// ʶ��ģʽ
	TCHAR szVehiclePlate[MY_SZLENGTH];	// ���ƺ���
	TCHAR wszPlateType[MY_SZLENGTH];
	TCHAR wszColor[MY_SZLENGTH];
	TCHAR wszLogoType[MY_SZLENGTH];
	TCHAR wszVechileType[MY_SZLENGTH];

	long nAlertLevel;			// ��������

	// ͼƬ��Ϣ
	TCHAR szResultImageID[MY_SZLENGTH];	// ��Ƶ�������ͼƬID
	unsigned long unBinaryType;	// ͼƬ��Ϣ��ImgType, ImgSize��char* pJpgBuf��
	unsigned long unBinarySize;	// 
	byte *bypBinaryBuf;			//

	//---
	// ��ʼ��
	vvtagVnlprResult() { Init(); }
	void Init(){
		memset(szUniqueResultID, 0, sizeof(szUniqueResultID));
		//---
		memset(szVAID, 0, sizeof(szVAID) );
		memset(szVAServerID, 0, sizeof(szVAServerID) );
		nDeviceNo = -1;
		memset(szVideoSrcCode, 0, sizeof(szVideoSrcCode) );
		memset(szVideoSrcName, 0, sizeof(szVideoSrcName) );
		memset( &tmLogTime, 0, sizeof(tmLogTime) );

		nPlateRecogMode = 1;
		memset(szVehiclePlate, 0, sizeof(szVehiclePlate) );
		memset(wszPlateType, 0, sizeof(wszPlateType) );
		memset(wszColor, 0, sizeof(wszColor) );
		memset(wszLogoType, 0, sizeof(wszLogoType) );
		memset(wszVechileType, 0, sizeof(wszVechileType) );

		nAlertLevel = 0;

		memset(szResultImageID, 0, sizeof(szResultImageID) );
		unBinaryType = IMG_JPG;
		unBinarySize = 0;
		bypBinaryBuf = NULL;
	};
	void UnInit()
	{
		if( NULL != bypBinaryBuf )
		{
			delete bypBinaryBuf;
			bypBinaryBuf = NULL;
		}
	}

	void CopyFromOther(const vvtagVnlprResult& other)
	{
		_tcscpy(szUniqueResultID, other.szUniqueResultID);
		//
		_tcscpy(szVAID, other.szVAID);
		_tcscpy(szVAServerID, other.szVAServerID);
		nDeviceNo = other.nDeviceNo;
		_tcscpy(szVideoSrcCode, other.szVideoSrcCode);
		_tcscpy(szVideoSrcName, other.szVideoSrcName);
		tmLogTime = other.tmLogTime;

		nPlateRecogMode = other.nPlateRecogMode;
		_tcscpy(szVehiclePlate, other.szVehiclePlate);
		_tcscpy(wszPlateType, other.wszPlateType);
		_tcscpy(wszColor, other.wszColor);
		_tcscpy(wszLogoType, other.wszLogoType);
		_tcscpy(wszVechileType, other.wszVechileType);

		nAlertLevel = other.nAlertLevel;

		_tcscpy(szResultImageID, other.szResultImageID);
		if (other.bypBinaryBuf!=NULL && other.unBinarySize>0)
		{
			bypBinaryBuf = new byte[other.unBinarySize];
			memcpy(bypBinaryBuf, other.bypBinaryBuf, other.unBinarySize);
		}
		unBinaryType = other.unBinaryType;
		unBinarySize = other.unBinarySize;
	}

	vvtagVnlprResult(const vvtagVnlprResult& other)
	{
		CopyFromOther(other);
	}

	vvtagVnlprResult& operator=(const vvtagVnlprResult & other)   
	{
		if(&other == this)
			return *this;
		CopyFromOther(other);

		return *this;
	}
	~vvtagVnlprResult()
	{
		UnInit();
	}
};
