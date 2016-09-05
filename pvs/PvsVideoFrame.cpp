#include "stdafx.h"
#include "PvsVideoFrame.h"
#include "PlatformVideoService.h"
#include "pvs.h"
#ifdef _LINUX
#include <sys/time.h>
#include <SCFileUtils.h>
#include <scOSBase.h>
#elif defined _WINDOWS
#include <process.h>
#endif

int PVideoFrame::s_nMaxNoFrameCameMilliSecs = 5000;
int PVideoFrame::s_nMaxNoFrameCameSec = 4000;//�೤ʱ��û������,��ʱ�����ԭ���߼�����ʼ��ʱ��������
VideoFrame PVideoFrame::s_missFrame;
int PVideoFrame::s_nNoFrameCameTimeoutMillisecs = 30000; // Ĭ������Ƶ��ʧ30��֮��������������Ƶ����
BOOL PVideoFrame::s_bIsShouldCopyMiss = FALSE;
//////////////////////////////////////////////////////////////////////////
unsigned int CALLBACK PVideoFrame::ThreadRoutine(void* lpParam)
{
	if (lpParam)
	{
		PVideoFrame* pInv = (PVideoFrame*)lpParam;
		pInv->ThreadFrameHandler();
	}
    printf("PVideoFrame::ThreadRoutine exit\n");
	return 0;
}

void PVideoFrame::ThreadFrameHandler()
{
#ifdef _LINUX
	long nElapsedTime = 0;
	timeval last; // ��һ��ʱ��
	timeval curr; // ��ǰʱ��
	long nNoFrameCameTotalMilliSecs = 0; // ͳ���ܹ��೤ʱ���Ѿ�û����Ƶ�����ݹ�����
#if PVS_USING_CACHE
	bool incReadPos = true;
#endif
	long nNoFrameCameMillisecsCount = 0; // ͳ�Ƶ�ǰû����Ƶ��ʱ�䣬���ڷ���������������

#   define GetTick(t) gettimeofday(&t, NULL)
#	define GetMilliseconds(t) \
			t = (curr.tv_sec-last.tv_sec)*1000;\
			t += (curr.tv_usec-last.tv_usec)/1000

#else

	LONGLONG nElapsedTime = 0;
	LONGLONG freq = 0; // ��Ƶ
	LONGLONG last = 0; // ��һ��COUNTER
	LONGLONG curr = 0; // ��ǰCOUNTER
	LONGLONG nNoFrameCameTotalMilliSecs = 0; // ͳ���ܹ��೤ʱ���Ѿ�û����Ƶ�����ݹ�����
#if PVS_USING_CACHE
	bool incReadPos = true;
#endif
	LONGLONG nNoFrameCameMillisecsCount = 0; // ͳ�Ƶ�ǰû����Ƶ��ʱ�䣬���ڷ���������������
	QueryPerformanceFrequency((LARGE_INTEGER*)&freq);

#	define GetTick(t) \
			QueryPerformanceCounter((LARGE_INTEGER*)&t)
#	define GetMilliseconds(t) \
			t = ((curr - last)*1000)/freq;

#endif

	GetTick(last);
	unsigned char * pBuf = NULL;
	VideoFrame Frame ;
	if(m_DataType == 1)//����H264
	{
		pBuf = (unsigned char *)malloc(1024*1024);
	}
	while (!m_bExit)
	{
		InterlockedCompareExchange(&m_bRun, 1, 0);

		GetTick(curr);
		GetMilliseconds(nElapsedTime); // ms
		if(nElapsedTime < 0)
		{
			last = curr;
		}
		last = curr;
		// ͳ�ƶ�ʧ��Ƶʱ��
		if(!m_bHasFrameCame)
		{
			m_nMaxNoFrameCameCount += nElapsedTime;
			if(m_nMaxNoFrameCameCount < s_nMaxNoFrameCameSec)
			{

				Sleep(1);
				if(0 == m_DataType || 2 == m_DataType)
				{
					continue;
				}
				if(1 == m_DataType)
				{
					scLockMutex(m_lockListFrame);
					if(m_listH264.size() == 0)
					{
						scUnlockMutex(m_lockListFrame);
						continue;
					}
					scUnlockMutex(m_lockListFrame);
				}
			}
			else
			{
				Sleep(100);
			}
		}

		if (!m_bPlaying)
		{
			//���رղ��ź�����ͨ����h264�����л��棬�������
			this->ClearH264Cache();

			nNoFrameCameTotalMilliSecs = 0;
			nNoFrameCameMillisecsCount = 0;
			InterlockedExchange(&m_bRun, 0);

			if (m_bExit)
				break;

			GetTick(last);
			continue;
		}

#if PVS_USING_CACHE
		// ����֡
		if (!m_bPlaySucceed 
			|| (nNoFrameCameTotalMilliSecs >= s_nMaxNoFrameCameMilliSecs)
			)
		{
			// ������Ƶʧ��֮�����Ϸ�����Ƶ��ʧͼ��
			// �����ѳ�ʱ��������Ƶ��ʧͼ��
			this->SendFrame(s_missFrame);

			// ����Ѿ������趨����������ʱ�䣬����������������
			// ���һֱû����Ƶ����ÿ���趨��ʱ��һֱ�ظ�����
			nNoFrameCameMillisecsCount += nElapsedTime;
			if (nNoFrameCameMillisecsCount >= s_nNoFrameCameTimeoutMillisecs)
			{
				// ���¼���
				// ����ٴγ�ʱ�������·���һ��
				nNoFrameCameMillisecsCount = 0;

				if (m_pService)
				{	
					if (m_pService->OnReplayChannel(m_nChl))
					{
						m_bPlaySucceed = TRUE;
					}
					else
					{
						// ��ʧ��֮�����¼�ʱ
						GetTick(last);
						m_bPlaySucceed = FALSE;
					}
				}
			}
		}
		else if (m_nFrameCache)
		{
			m_videoFrame.data = m_pFrameCache + m_nFrameSize*m_nCurrReadCache;
			this->SendFrame(m_videoFrame);
		}

		incReadPos = true;

		if (m_nFrameCache <= 1)
		{
			// ��ǰû�л���֡
			// �ָ����ͼ��ʱ��
			m_nCurrFrameInterval = m_nNormalFrameInterval;
			incReadPos = false;
		}
		else if (m_nFrameCache >= m_nMaxDelayCache)
		{
			// ��ȡ����Ѵ���ָ��ֵ
			--m_nCurrFrameInterval;
			if (m_nCurrFrameInterval < m_nMinFrameInterval)
				m_nCurrFrameInterval = m_nMinFrameInterval;
		}
		else if (m_nFrameCache >= m_nMaxFrameCache)
		{
			// ��д������
			m_nCurrFrameInterval = m_nMinFrameInterval;
		}

		if (incReadPos)
		{
			// �ݼ���ǰ�����֡��
			InterlockedDecrement(&m_nFrameCache);

			++m_nCurrReadCache;
			if (m_nCurrReadCache >= m_nMaxFrameCache)
			{
				m_nCurrReadCache = 0;
			}

			// �������¼���
			nNoFrameCameTotalMilliSecs = 0;
		}
		else
		{
			// �ۼ�
			nNoFrameCameTotalMilliSecs += nElapsedTime;
		}
#else
		// ����H264��Ƶ����
		if(m_bPlaySucceed && m_DataType == 1)
		{
			scLockMutex(m_lockListFrame);
			if(m_listH264.size())
			{
				H264Data * pH264Data = m_listH264.front();
				m_listH264.pop_front();
				scUnlockMutex(m_lockListFrame);
				Frame = *(pH264Data->GetH264Frame());
				// ���Թ����У����ֵ㲥��ʱ������pBufΪNULL����������������ڴ�ʧ�ܻ��Ǹ�����û��H264��ͨ����û�������ڴ棩��������memcpyʱ����
				if (NULL != pBuf)
				{
					memcpy(pBuf, Frame.data, Frame.size);
					delete pH264Data;
					Frame.data = pBuf;
					this->SendFrame(Frame);
				}
				else
				{
					pBuf = (unsigned char *)malloc(1024*1024);
				}
				//����H264����ʱ��Ҳ��������
				nNoFrameCameMillisecsCount = 0;
			}
			else
			{
				scUnlockMutex(m_lockListFrame);
			}
		}

		// ����YUV���ݺ�NVMM��������
		if (m_bPlaySucceed && InterlockedCompareExchange(&m_bHasFrameCame, 0, 1))
		{
			m_bFrameState = TRUE;
			// ����Ƶ����
			m_nCurrFrameInterval = m_nSetFrameInterval;
			if(0 == m_DataType || 2 == m_DataType)
			{
				this->SendFrame(m_videoFrame);
			}
			nNoFrameCameMillisecsCount = 0;
			nNoFrameCameTotalMilliSecs = 0;
		}

		if(m_bMode)
		{//���������ݻص�ʱ������Ҫ�ж�����
			continue;
		}
		else 
		{
			if (!m_bPlaySucceed || nNoFrameCameTotalMilliSecs >= s_nMaxNoFrameCameMilliSecs)
			{
				m_nCurrFrameInterval = m_nSetFrameInterval;
				nNoFrameCameTotalMilliSecs = s_nMaxNoFrameCameMilliSecs;

				// ���ʹ�����
				if (m_bFrameState)
				{
					m_bFrameState = FALSE;
					m_pService->OnOutputError(((PlayHandle)m_hplay)->cache->cnPlay->szID, Err_OverTimeNoStream);
				}
				
				// ����ָ��ʱ��û����Ƶ����
				// ������Ƶ��ʧͼ��
				if(s_bIsShouldCopyMiss)
				{
					this->SendFrame(s_missFrame);

				}
			}
			nNoFrameCameTotalMilliSecs += nElapsedTime;

			// ����ָ��ʱ��������������Ƶ
			// �κ�һ��ʹ�õ�ͨ���ò������ݶ�Ӧ������ change by wuth
			// if (m_bMainChannel)
			{
				if (nNoFrameCameMillisecsCount >= s_nNoFrameCameTimeoutMillisecs)
				{
					// ���¼���
					// ����ٴγ�ʱ�������·���һ��
					
					//����ʱ������ͨ����h264�����л��棬�������
					this->ClearH264Cache();

					nNoFrameCameMillisecsCount = 0;
					m_nMaxNoFrameCameCount = 0;

					if (m_pService)
					{	
						if (m_pService->OnReplayChannel(m_hplay))
						{
							m_bPlaySucceed = TRUE;
						}
						else
						{
							// ��ʧ��֮�����¼�ʱ
							GetTick(last);
							m_bPlaySucceed = FALSE;
						}
					}
				}
				nNoFrameCameMillisecsCount += nElapsedTime;	
			}
		}
#endif
	}
	if(pBuf)
		free(pBuf);
}

void PVideoFrame::InitEx()
{
	char szPath[MAX_PATH] = {0};
	char szFile[MAX_PATH] = {0};

#ifdef _LINUX
	scGetModulePath(szPath);
	sprintf(szFile, "%s/%s", szPath, "miss.bmp");
#else
	TCHAR szDrv[MAX_PATH] = {0};
	TCHAR szDir[MAX_PATH] = {0};
	GetModuleFileName(thePVSModule, szPath, MAX_PATH);
	_tsplitpath(szPath, szDrv, szDir, NULL, NULL);
	_tmakepath(szFile, szDrv, szDir, _T("miss"), _T("bmp"));
#endif

	CBitmapLoad bmp;
	unsigned long nSizeImg = 0;
	if (bmp.Load(szFile))
	{
		nSizeImg = bmp.GetDataSize();
		s_missFrame.data = new unsigned char[nSizeImg];
		bmp.Copy(s_missFrame.data);
		bmp.GetSize(&s_missFrame.width, &s_missFrame.height);
		s_missFrame.size = nSizeImg;
		s_missFrame.type = VideoFrame::RGB24;
		s_bIsShouldCopyMiss = TRUE;
	}
	else
	{
		// ����ʧ��
		nSizeImg = 304128;
		s_missFrame.data = new unsigned char[nSizeImg];
		memset(s_missFrame.data, 0, nSizeImg);
		s_missFrame.width = 352;
		s_missFrame.height = 288;
		s_missFrame.size = nSizeImg;
		s_missFrame.type = VideoFrame::RGB24;
		s_bIsShouldCopyMiss = FALSE;
	}
}

void PVideoFrame::UninitEx()
{
	if (s_missFrame.data)
	{
		delete[] s_missFrame.data;
		s_missFrame.data = NULL;
	}
}

void PVideoFrame::SetCheckFrameParam(int nTimeoutMillisecs, int nNoFrameCameTimeoutSsecs)
{
	s_nMaxNoFrameCameMilliSecs = nTimeoutMillisecs; 
	s_nNoFrameCameTimeoutMillisecs = nNoFrameCameTimeoutSsecs*1000;
}
//////////////////////////////////////////////////////////////////////////
PVideoFrame::PVideoFrame(IVideoService* pService)
{
	m_pService = pService;
	m_hplay = 0;
	m_bPlaying = 0;
	m_playuser = 0;
	m_nMaxNoFrameCameCount = 0;
	m_lockListFrame = scCreateMutex();
#if PVS_USING_CACHE
	m_nMaxFrameCache = 25;
	m_nMaxDelayCache = 10;
	m_nNormalFrameInterval = PVS_NORMAL_FRAME_INTERVAL_TIME;
	m_nMinFrameInterval = 27;
	m_pFrameCache = NULL;
	m_nCurrReadCache = 0;
	m_nCurrWriteCache = 0;
	m_nFrameCache = 0;
#else
	m_bHasFrameCame = 0;
#endif

	memset(&m_videoFrame, 0, sizeof(m_videoFrame));

	m_nCurrFrameInterval = PVS_NORMAL_FRAME_INTERVAL_TIME;
	m_nSetFrameInterval = PVS_NORMAL_FRAME_INTERVAL_TIME;

	m_bExit = 0;
	m_bRun = 0;
	m_hThreadFrame = NULL;

	m_bOutputOriginalSize = FALSE;
	m_bMainChannel = TRUE;
	m_bConvert = TRUE;
	m_nWidthConverted = 352;
	m_nHeightConverted = 288;
	m_nSizeConverted = 304128;
	m_vflip = 0;
    m_bFrameState = TRUE;
}

PVideoFrame::~PVideoFrame(void)
{
	this->Destory();
#if PVS_USING_CACHE
	if (m_pFrameCache)
	{
		delete[] m_pFrameCache;
		m_pFrameCache = NULL;
	}
#endif
}

void PVideoFrame::Destory()
{
	InterlockedExchange(&m_bExit, 1);
	InterlockedExchange(&m_bPlaying, 0);
	
	if (m_hThreadFrame)
	{
		WaitForSingleObject(m_hThreadFrame, INFINITE);
		CloseHandle(m_hThreadFrame);
		m_hThreadFrame = NULL;
	}
	scDestroyMutex(m_lockListFrame);
}

BOOL PVideoFrame::AllocImageCache()
{
#if PVS_USING_CACHE
	if (m_pFrameCache)
	{
		delete[] m_pFrameCache;
		m_pFrameCache = NULL;
	}

	int sizeTotal = m_nMaxFrameCache * m_videoFrame.size;
	if (!m_pFrameCache)
	{
		m_pFrameCache = new unsigned char[sizeTotal];
	}

	memset(m_pFrameCache, 0, sizeTotal);
	return TRUE;
#else
	return FALSE;
#endif
}

void PVideoFrame::OnVideoFrame(void* data)
{
	if (!m_bPlaying)
		return;

#if PVS_USING_CACHE
	// д�뻺����
	unsigned char* pWritePos = m_pFrameCache + m_nCurrWriteCache*m_videoFrame.size;
	memcpy(pWritePos, data, m_videoFrame.size);

	// ���µ�ǰд�뻺��֡����
	// �����ȡ��������д���죬Ϊ�˲�����δ��ȡ�����ݣ�ֻ�ܸ������µ�һ֡����
	if (m_nFrameCache < m_nMaxFrameCache)
	{
		++m_nCurrWriteCache;
		if (m_nCurrWriteCache >= m_nMaxFrameCache)
		{
			m_nCurrWriteCache = 0;
		}

		// ������ǰ�����֡��
#	ifdef _DEBUG
		LONG nCache = InterlockedIncrement(&m_nFrameCache);

		TCHAR szCache[64];
		_stprintf(szCache, _T("OnDrawFrame: %d - %d\n"), m_nChl, nCache);
		OutputDebugString(szCache);
#	else
		InterlockedIncrement(&m_nFrameCache);
#	endif

	}
#else
	m_videoFrame.data = (unsigned char*)data;
	// ������
	InterlockedExchange(&m_bHasFrameCame, 1);
	m_nMaxNoFrameCameCount = 0;
	if(m_DataType == 1)//1ΪH264��
	{
		scLockMutex(m_lockListFrame);
		if(m_listH264.size() > 100)
		{
			printf("H264frame is lost\n");
			m_vflip = 1;
		}
		else
		{
			if((m_vflip && m_videoFrame.vflip) || m_vflip == 0)
			{
				H264Data * pH264Data = new H264Data(m_videoFrame);
				m_listH264.push_back(pH264Data);
				m_vflip = 0;
			}
		}
		scUnlockMutex(m_lockListFrame);
	}
#endif
}

void PVideoFrame::StartSendFrame(int width, int height, BOOL bPlaySucceed, int bMode)
{
	if (m_bPlaying)
		return;

	if (width < 0 || height < 0)
	{
		// ���ԭʼͼ���С
		// ����ǰ�ԭʼͼ���С���
		// ��ֻ�������ݻص��в���ȷ�������С
		m_bOutputOriginalSize = TRUE;
	}
	if (m_videoFrame.width != width || m_videoFrame.height != height)
	{
		// ͼ������ߴ��Ѿ��ı�
		m_bConvert = TRUE;
		m_nWidthConverted = width;
		m_nHeightConverted = height;
		m_nSizeConverted = ((width*3+3)/4*4)*height;

		m_videoFrame.width = m_nWidthConverted;
		m_videoFrame.height = m_nHeightConverted;
		m_videoFrame.size = m_nSizeConverted;
		m_videoFrame.type = VideoFrame::RGB24;

#if PVS_USING_CACHE
		if (m_pFrameCache)
		{
			delete[] m_pFrameCache;
			m_pFrameCache = NULL;
		}
#endif
	}

#if PVS_USING_CACHE
	m_nCurrWriteCache = 0;
	m_nCurrReadCache = 0;
	m_nFrameCache = 0;
#else
	m_bHasFrameCame = 0;
	m_nCurrFrameInterval = PVS_NORMAL_FRAME_INTERVAL_TIME;
	m_nSetFrameInterval = PVS_NORMAL_FRAME_INTERVAL_TIME;
#endif

	this->ClearH264Cache();
	InterlockedExchange(&m_bPlaySucceed, bPlaySucceed);
	InterlockedCompareExchange(&m_bPlaying, 1, 0);

	m_bMode = bMode;
	if (m_hThreadFrame)
	{
	}
	else
	{
		// ������ʱ�߳�
		m_hThreadFrame = (HANDLE)_beginthreadex(NULL, 0, ThreadRoutine, this, 0, NULL);
	}
}

void PVideoFrame::StopSendFrame()
{
	InterlockedCompareExchange(&m_bPlaying, 0, 1);
	m_bOutputOriginalSize = FALSE;
	this->ClearH264Cache();
}

BOOL PVideoFrame::SetFrameCacheParam(int nMaxFrameCache, int nMaxDelayCache, int nNormalInterval, int nMinInterval)
{
	if (m_bPlaying)
		return FALSE;
#if PVS_USING_CACHE
	m_nMaxFrameCache = nMaxFrameCache;
	m_nMaxDelayCache = nMaxDelayCache;
	m_nNormalFrameInterval = nNormalInterval;
	m_nMinFrameInterval = nMinInterval;
#endif
	return TRUE;
}

BOOL PVideoFrame::CheckVideoFrame(BOOL bConvert, const VideoFrame& vframe)
{
	if (!m_bPlaying)
		return FALSE;
	m_videoFrame.nCapture = vframe.nCapture;
	if(vframe.type == VideoFrame::H264)
	{
		m_videoFrame.size = vframe.size;
		m_videoFrame.type = vframe.type;
		m_videoFrame.height = vframe.height;
		m_videoFrame.width = vframe.width;
		return TRUE;
	}

	if (vframe.type == VideoFrame::NVMM)
	{
		m_videoFrame.size = vframe.size;
		m_videoFrame.type = vframe.type;
		m_videoFrame.height = vframe.height;
		m_videoFrame.width = vframe.width;
		return TRUE;
	}

	if (m_bOutputOriginalSize)
	{
		// ��ԭʼ�ߴ����
		if (m_videoFrame.width == vframe.width 
			&& m_videoFrame.height == vframe.height
			&& m_videoFrame.size == vframe.size
			&& m_bConvert == bConvert)
		{
			if (!bConvert && m_videoFrame.type == vframe.type)
				return TRUE;
		}

		m_videoFrame.width = vframe.width;
		m_videoFrame.height = vframe.height;
		m_bConvert = bConvert;
		if (bConvert)
		{
			m_videoFrame.size = ((vframe.width*3+3)/4*4)*vframe.height;
			m_videoFrame.type = VideoFrame::RGB24;
		}
		else
		{
			m_videoFrame.size = vframe.size;
			m_videoFrame.type = vframe.type;
		}
	}
	else // �ı�ߴ����
	{
		// ת��RGB
		if (bConvert)
		{
			if (m_bConvert)
				return TRUE;

			m_bConvert = TRUE;
			m_videoFrame.width = m_nWidthConverted;
			m_videoFrame.height = m_nHeightConverted;
			m_videoFrame.size = m_nSizeConverted;
			m_videoFrame.type = VideoFrame::RGB24;
		}
		else
		{
			// ת��������ı�����ߴ�
			// ��ת��������ı�����ߴ�
			if (!m_bConvert 
				&& m_videoFrame.width == vframe.width
				&& m_videoFrame.height == vframe.height
				&& m_videoFrame.size == vframe.size
				&& m_videoFrame.type == vframe.type)
				return TRUE;

			// ��ת��->��ת��
			m_videoFrame.width = vframe.width;
			m_videoFrame.height = vframe.height;
			m_videoFrame.size = vframe.size;
			m_videoFrame.type = vframe.type;
			m_bConvert = FALSE;
		}
	}

#if PVS_USING_CACHE
	return this->AllocImageCache();
#else
	return TRUE;
#endif
}

BOOL PVideoFrame::CopyVideoFrame(void* dstBuf, const VideoFrame& vframe)
{
	int ylen = 0;
	m_videoFrame.timestamp = vframe.timestamp;//��ʱ�����ֵ
	switch (vframe.type)
	{
	case VideoFrame::RGB24:
	case VideoFrame::RGB32:
	case VideoFrame::UYVY:
	case VideoFrame::VYUY:
	case VideoFrame::YUYV:
	case VideoFrame::YVYU:
	case VideoFrame::YUVUV:
	case VideoFrame::H264:
		memcpy(dstBuf, vframe.data, vframe.size);
		m_videoFrame.vflip = vframe.vflip;
		return TRUE;

	case VideoFrame::NVMM:
		{
			memcpy(dstBuf, &vframe.data, sizeof(vframe.data));
			return TRUE;
		}

	case VideoFrame::YUV420:
	case VideoFrame::YV12:
		ylen = vframe.width * vframe.height;
		m_videoFrame.py = (unsigned char*)dstBuf;
		m_videoFrame.pu = m_videoFrame.py + ylen;
		m_videoFrame.pv = m_videoFrame.pu + (ylen>>2);
		memcpy(m_videoFrame.py, vframe.py, ylen);
		memcpy(m_videoFrame.pu, vframe.pu, (ylen>>2));
		memcpy(m_videoFrame.pv, vframe.pv, (ylen>>2));
		return TRUE;

	default:
		break;
	}
	return FALSE;
}

void PVideoFrame::ClearH264Cache()
{
	if(m_DataType == 1)//1ΪH264��
	{
		// ��ʼ����ǰ��ջ���
		scLockMutex(m_lockListFrame);
		if ( m_listH264.empty() )
		{
			scUnlockMutex(m_lockListFrame);
			return;
		}

		for(list<H264Data*>::iterator it=m_listH264.begin(); it!=m_listH264.end(); it++)
		{
			printf("[ClearH264Cache]  h264 list clear() +++++++++++++++++ \n");	
			H264Data * pH264Data = *it;
			it = m_listH264.erase(it);
			delete pH264Data;
		}
		scUnlockMutex(m_lockListFrame);
	}

}

