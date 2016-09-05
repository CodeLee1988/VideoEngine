#ifndef __PVSDEF_H__
#define __PVSDEF_H__

#include "ScType.h"
#include "PvsVideoDef.h"
#include "CommonErr.h"
#include <string>

// PTZ
#define PT_MAX_SPEED		8

//////////////////////////////////////////////////////////////////////////PT���Ƶ�����
// nDirection
#define PTZ_TILT_UP					0x0101	// ����
#define PTZ_TILT_DOWN				0x0103	// ����

#define PTZ_PAN_LEFT				0x0201  // ����
#define PTZ_PAN_RIGHT				0x0203	// ����

#define PTZ_MOVE_UPLEFT				0x0301  // ����
#define PTZ_MOVE_DOWNLEFT			0x0303  // ����

#define PTZ_MOVE_UPRIGHT			0x0401  // ����
#define PTZ_MOVE_DOWNRIGHT			0x0403  // ����

//////////////////////////////////////////////////////////////////////////�䱶����
// nOperaType
#define PTZ_ZOOM_IN					0x0501	// �Ŵ�
#define PTZ_ZOOM_OUT				0x0503	// ��С

//////////////////////////////////////////////////////////////////////////�������
// nOperaType
#define PTZ_FOCUS_FAR				0x0601	// Զ�۽�
#define PTZ_FOCUS_NEAR				0x0603	// ���۽�

//////////////////////////////////////////////////////////////////////////��Ȧ����
// nOperaType
#define PTZ_IRIS_OPEN				0x0701	// ��Ȧ��
#define PTZ_IRIS_CLOSE				0x0703	// ��Ȧ��

//////////////////////////////////////////////////////////////////////////Ԥ��λ����
// nOperaType
#define PTZ_SAVE_PRE_PLACE			0x0801	// ����Ԥ��λ
#define PTZ_GOTO_PRE_PLACE			0x0802	// ת��Ԥ��λ
#define PTZ_DEL_PRE_PLACE			0x0803	// ���Ԥ��λ

//////////////////////////////////////////////////////////////////////////����
#define PTZ_FASTGOTO				0x0900	//����goto

#define PTZ_SHUTTER_TIME 			0x0901 // ����ʱ��
#define PTZ_SHUTTER_MODE 			0x0902 // ����ģʽ���Զ��ֶ�
#define PTZ_CRUISE 					0x0903 // Ѳ��
#define PTZ_SOUND_ONOFF             0x0904 // �Ƿ����������
#define PVS_SET_REAL_TIME	        0x0905 // ���Уʱ

// All stop
#define PTZ_ALL_STOP				0x0998  // ȫͣ����

//////////////////////////////////////////////////////////////////////////

//������SetConfig��GetConfig��key �� value
#define KEY_PRINTINFO_STAMP         "TurnOnPrintInfo"   //�Ƿ��ʱ�����ӡ
#define KEY_RECORD_BY_TIME 			"StartRecordByTimeSpan" //����ʱ��α���¼�� ��Ӧ��value��PVS_SaveRecordByTimeSpanParam�ṹ��
#define KEY_RECORD_BUFFER_TIMESPAN 	"ReocordBufferTimeSpan" //����Ԥ��¼���ʱ�䡣 value��int�� ��λ����

#define KEY_DEVICE_CHANGED 	"DeviceChanged" // ��ӡ��޸Ļ�ɾ���豸��valueֵ����Ϊchar*��XML����ʽ
#define KEY_DEVICE_UPDATE 	"DeviceUpdate" // �����豸�б�����valueֵ
#define KEY_DEVICE_LIST 	"GetDeviceListXML" // ��ȡ�豸�б�valueֵ����Ϊchar**
#define KEY_DEVICE_LIST_OBJ 	"GetDeviceListOjbect" // ��ȡ�豸�б�value����ΪBaseNode**

#define KEY_DEVICE_CONFIG_SET 	"SetDeviceConfigXML" // �����豸������Ϣ��valueֵ����Ϊchar*
#define KEY_DEVICE_CONFIG_GET 	"GetDeviceConfigXML" // ��ȡ�豸������Ϣ��valueֵ����Ϊchar**

#define KEY_FRAME_CONVERT_TO_RGB_SET  "SetConvertFrameToRGB" // �����Ƿ�YUV����ת����RGB���ݣ�valueֵ����Ϊint*��1-ת����0-��ת��
#define KEY_FRAME_CONVERT_TO_RGB_GET  "GetConvertFrameToRGB" // ��ȡ�Ƿ�YUV����ת����RGB���ݣ�valueֵ����Ϊint*��1-ת����0-��ת��

#define KEY_CAMERA_STATUS_GET  "GetCameraStatus" // ��ȡ���״̬��paramֵ����ΪPVS_CameraStatus*��valueֵΪint*
#define KEY_ONE_FRAMEDATA_GET "OneFrameData_Get"		//�������ȡͼƬ
#define KEY_ONE_H264DATA_GET   "OneH264Data_Get"		//��ȡһ֡H264��I֡
//////////////////////////////////////////////////////////////////////////
#define PVS_BOOL int
#define PVS_TRUE 1
#define PVS_FALSE 0

typedef void* HPVSPLAY; // ���ž��
typedef void* ResourceHandle; // ��Դ���
#define INVALID_PLAY_HANDLE ((HPVSPLAY)(NULL))

//////////////////////////////////////////////////////////////////////////
#pragma pack(push)
#pragma pack(4)


//1.����AE�Զ�ģʽ
//lMode = 0
//2.���ÿ�������ģʽ
//lMode = 1
//3.AE��Ȧ����ģʽ
//lMode = 2
//4.AEȫ�ֶ�ģʽ ���ã�
//lMode = 3
typedef struct PVS_ShutterMode
{
	long lMode;
	long lShutterSpeed;
	long lIris;
	long lGain;
}PVS_ShutterMode;
// PTZ Control
struct PVS_PtzMsgContent
{
	char szCamId[256]; // ���ID
	long OpType;	// ������
	// ��OpTypeΪPT����ʱ��Param1��������ƶ��ٶȣ�Param2���������ƶ��ٶ�
	// ��OpTypeΪZoom������Focus������Iris����ʱ��Param1������Щ�������ٶȣ�Param2������
	// ��OpTypeΪԤ��λ����ʱ��Param1��Ԥ��λֵ��Param2������
	// ��OpTypeΪPTZ_FASTGOTO(���ٶ�λ����)��Param4����3D��λ�ṹ������������
	// ��OpTypeΪPTZ_SHUTTER_TIMEʱ��Param1�����������ʱ��
	// ��OpTypeΪPTZ_SHUTTER_MODEʱ��Param1������������Զ�ģʽ�����ֶ�ģʽ
	long Param1;
	long Param2;
	long Param3;
	void* Param4;
	void* pReserved1; // ����1
	void* pReserved2; // ����2
};

//////////////////////////////////////////////////////////////////////////
//3D��λ�ṹ
//////////////////////////////////////////////////////////////////////////
// ���궨��Ϊԭ�������Ͻǣ�����Ϊx��������Ϊy����
struct PVS_DPOINT
{
	int width; // ��ʾ��
	int height; // ��ʾ��
	ScPoint startPoint; // Ŀ����ʼ��
	ScPoint endPoint; // Ŀ�������
};

// Ԥ��¼��
struct PVS_SaveRecordByTimeSpanParam
{
	HPVSPLAY hPlay;		// ����Ϊ��
	char szFileFullPath[512];
	ScSystemTime stBegin;
	ScSystemTime stEnd;
	void* pReserved; // ����
};
struct PVS_GetCapture
{
	char szCamID[256]; //���ID
	unsigned int PitureID;//ͼƬ��־
	void* pReserved; // ����

};
struct PVS_GetOneH264
{
	char szCamID[256]; //���ID
	unsigned char * pData;
	int nLength;
	void * param1;
	void*  pReserved; // ����

};
// ���״̬
struct PVS_CameraStatus
{
	enum StatusType
	{
		Focus, // �۽�
		Nothing
	};

	char szCamID[256]; // ���ID
	StatusType eStatusType; // ״̬����
	int nStatus; // ״ֵ̬
	void* pReserved; // ����
};

// �ⲿ�ṩ����Ԥ���ṹ
struct PVS_RealPlay
{
	char vendor[64]; // ���ұ�ʶ
	char ipaddr[64]; // �豸��ƽ̨IP��ַ
	char username[256]; // ��½�û���
	char password[256]; // ��½����
	int port; // ��½�˿ں�
	char channel[256]; // ͨ����ʶ
	int chno; // ͨ����
	char reserved[512]; // ����
};

#pragma pack(pop)

//////////////////////////////////////////////////////////////////////////

// ͼ�����ݻص�
// img24 - 24λλͼͼ������
// hPlay - ����ͨ�����
// user - ͼ�����ݻص��û�����
// play_user - ����ͨ���û�����
typedef void (CALLBACK *PVideoFrameCallback)(VideoFrame& vframe, HPVSPLAY hPlay, void* user, void* play_user);

// �����־�ص�
typedef long (CALLBACK *POutputLogCallback)(const char* lpszLog, const char* lpszFuncName, const char* lpszFileName, long nLine, long nLevel, void* user);

// �������ص�
typedef long (CALLBACK *POutputErrorCallback)(std::string& sCamID, CommonErr error, void* user);

//////////////////////////////////////////////////////////////////////////

#endif //__PVSDEF_H__
