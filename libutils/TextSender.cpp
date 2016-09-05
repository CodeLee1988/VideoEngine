#include "stdafx.h"
#include "TextSender.h"
#include <process.h>

//////////////////////////////////////////////////////////////////////////

unsigned int __stdcall Reconnect_Thread(void* lpParam)
{
	CTextSender *pThis = (CTextSender*)lpParam;

	pThis->Reconnect_ThreadFunction();

	return 0;
}

CTextSender::CTextSender(void)
{
	// ��ʼ��WS2_32.dll
	BYTE minorVer = 2;
	BYTE majorVer = 2;
	WSADATA wsaData;
	WORD sockVersion = MAKEWORD(minorVer, majorVer);
	::WSAStartup(sockVersion, &wsaData);

	m_strServer = "";
	m_nPort = -1;
	m_bInited = false;

	m_bIsTCPConnected = false;
	m_sockServer = INVALID_SOCKET;
	m_pNetCb = NULL;
	m_pInvoker = NULL;

	unsigned int id = 0;
	m_bReconnectThreadWork = true;
	m_hThread = (HANDLE)_beginthreadex(NULL, 0, Reconnect_Thread, this, 0, &id);
}

CTextSender::~CTextSender(void)
{
	UnInit();
	DisConnect();
	if (m_hThread != NULL)
	{
		WaitForSingleObject(m_hThread, INFINITE);
		CloseHandle(m_hThread);
	}
	
	::WSACleanup();
}

void CTextSender::Reconnect_ThreadFunction()
{
	while (m_bReconnectThreadWork)
	{
		Sleep(1);
		if (m_bIsTCPConnected)
		{
			// ��������
			char buff[4096];
			memset(buff, 0, sizeof(buff));
			int bytesRecv = ::recv(m_sockServer, buff, 4096, 0);
			// �����������ӷ������ķ�����������ʹ��������ʽ����socket������
			if ( bytesRecv <= 0
				|| WSAENETDOWN == bytesRecv
				|| WSAENOTCONN == bytesRecv
				|| WSAENETRESET == bytesRecv
				|| WSAESHUTDOWN == bytesRecv
				|| WSAECONNABORTED == bytesRecv
				|| WSAECONNRESET == bytesRecv
				)	//
			{
				InterlockedExchange(&m_bIsTCPConnected, false);
			}
			if (m_pNetCb != NULL)
			{
				m_pNetCb(buff, bytesRecv, m_pInvoker);
			}
		}
	}
}

BOOL CTextSender::IsConnected()
{
	// ԭ�������SendText�����Ŀ�ʼ�������ӣ�����״̬��ѯ��ͬ�����ӣ����ֱ�ӷ������ϲ�
	if ( m_bInited )
		if ( !m_bIsTCPConnected )
			ReConnect();

	return m_bIsTCPConnected; 
}

void CTextSender::ReConnect()
{
	ReConnectServer(m_strServer.c_str(), m_nPort);
}

void CTextSender::Init(const char* cszServerAddr, int nPort, pNetCallback pNetCb, void *pInvoker)
{
	string strServer = cszServerAddr;
	if(strServer.length() == 0 || nPort <= 0 )
		return;
	m_strServer = cszServerAddr;
	m_nPort = nPort;

	m_pNetCb = (pNetCallback)pNetCb;
	m_pInvoker = pInvoker;

	m_bInited = true;
}

void CTextSender::UnInit() 
{ 
	InterlockedExchange(&m_bReconnectThreadWork, false); 
}

void CTextSender::ReConnectServer(const char* cszServerAddr, int nPort)
{
	string strServer = cszServerAddr;
	if(strServer.length() == 0 || nPort <= 0 )
		return;
	m_strServer = cszServerAddr;
	m_nPort = nPort;

	DisConnect();

	// �����׽���
	SOCKET s = ::socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
	if(s == INVALID_SOCKET)
	{
		return ;
	}

	// ��ʱ����
	const char chOpt = 1;
	int nErr = setsockopt(s, IPPROTO_TCP, TCP_NODELAY, &chOpt, sizeof(char));

	// ��дԶ�̵�ַ��Ϣ
	sockaddr_in servAddr; 
	servAddr.sin_family = AF_INET;
	servAddr.sin_port = htons((u_short)nPort);
	servAddr.sin_addr.S_un.S_addr = inet_addr(m_strServer.c_str());

	if(::connect(s, (sockaddr*)&servAddr, sizeof(servAddr)) == SOCKET_ERROR)
	{
		::closesocket(s);
		s = INVALID_SOCKET;
		return;
	}

	m_sockServer = s;
	InterlockedExchange(&m_bIsTCPConnected, true);
}

void CTextSender::DisConnect()
{
	if (!m_bIsTCPConnected)
		return;

	InterlockedExchange(&m_bIsTCPConnected, false);

	::closesocket(m_sockServer);
	m_sockServer = INVALID_SOCKET;
}

BOOL CTextSender::SendText(const char* szText, int len, BOOL bSendOneTime/*=TRUE*/)
{
	if ( !m_bIsTCPConnected )
	{
		//if(m_bInited)
		//	ReConnect();
		//if ( !m_bIsTCPConnected )
		//{
			return FALSE;
		//}
	}
	
	if(len <= 0 || szText==NULL )
		return FALSE;

	if (bSendOneTime)
	{
		::send(m_sockServer, szText, len, 0);
	}
	else	// �ֿ���η���
	{
		int nMaxSendOneTime = 50000;	// ÿ�η��Ͳ�����50K
		int nSendTime = len/nMaxSendOneTime;
		if( len%nMaxSendOneTime != 0 )
			nSendTime += 1;
		for (int i=0; i<nSendTime; i++)
		{
			if( INVALID_SOCKET==m_sockServer || !m_bIsTCPConnected)
				break;
			int nCopyCount = 0;
			if( i< nSendTime-1 )
				nCopyCount = nMaxSendOneTime;
			else
				nCopyCount = len - i*nMaxSendOneTime;

			::send(m_sockServer, szText+i*nMaxSendOneTime, nCopyCount, 0);
			Sleep(1);
		}
	}

	return TRUE;
}
