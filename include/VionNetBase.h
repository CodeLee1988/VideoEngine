#pragma once
// �����İ��Ƽ���չ���޹�˾

// ͨ�ò���--VVVVV----------------------------------------------------------------------------

// ��Ϣ���ʶ
#define MYMF_NONE	0
#define MYMF_XML	1
#define MYMF_JPG	2
#define MYMF_BINARY 3
#define MYMF_OTHER	4

// ��Ϣ����
#define NETCMD_UNDEFINED	0	// 
#define NETCMD_REQUEST	1	// ����
#define NETCMD_RESPONSE 2	// ��Ӧ
#define NETCMD_NOTIFY	3	// ֪ͨ


// �İ����紫��ͨ��Э��ͷ---VVV--------
struct SVNetNotifyHead
{
	DWORD dwMainVersion;
	DWORD dwSubVersion;
	//
	DWORD dwNetCmdCategory;		// 0 - ���󣬡�1 - ��Ӧ
	DWORD dwTransationID;	// ����ID
	//  �ض�Ӧ�õ�����
	DWORD nNetNotifyType;		// ������ʶ���͵�����/��Ϣ
	DWORD nNetNotifyResult;		// ��������������	0�������ɹ��� XX�������룬��0�����������ɹ�
	//
	DWORD nReserved;
	SVNetNotifyHead() { Init(); }
	void Init() {
				  dwMainVersion = 1;
				  dwSubVersion = 0;
				  //
				  dwNetCmdCategory = NETCMD_UNDEFINED;
				  dwTransationID = -1;
				  //
				  nNetNotifyType=-1;
				  nNetNotifyResult = 0;
				  //
				  nReserved = 0;
	};
};
// �İ����紫��ͨ��Э��ͷ---^^^--------

// ͨ�ò���---^^^^^---------------------------------------------------------------------------
