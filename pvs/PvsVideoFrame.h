#pragma once

#include "PvsDef.h"
#include "BitmapLoad.h"
#include "ScMutex.h"
#include "nvmmtool.h"
#include <list>
using std::list;

#define PVS_USING_CACHE  0 // �Ƿ�ʹ�û���
#define PVS_NORMAL_FRAME_INTERVAL_TIME 39 // ��������֡ʱ����(ms)
#define OUTPUT_TYPE_RAW 0
#define OUTPUT_TYPE_H264 1
#define OUTPUT_TYPE_NVMM 2

//////////////////////////////////////////////////////////////////////////
class IVideoService
{
public:
	// ���ݷ��ͻص�
	virtual void OnSendVideoFrame(VideoFrame& vframe, void* hplay, void* playuser) = 0;
	// ��������ص�
	virtual long OnReplayChannel(void* hplay) = 0;
	
	// ��������¼�
	virtual long OnOutputError(std::string sCamID, CommonErr err) = 0;
};

//////////////////////////////////////////////////////////////////////////
// ͨ�û���
class SharedBuf
{
private:
	void* pBuf;
	int nSize;

public:
	SharedBuf()
	{
		this->pBuf = NULL;
		this->nSize = 0;
	}
	~SharedBuf()
	{
		this->Release();	
	}
	inline void Release()
	{
		if (this->pBuf != NULL)
		{
			free(this->pBuf);
			this->pBuf = NULL;
		}
		this->nSize = 0;
	}
	inline void* Check(int size)
	{
		if (this->nSize != size)
		{
			this->Release();

			this->pBuf = malloc(size);
			this->nSize = size;
		}
		return this->pBuf;
	}
};
typedef SharedBuf* PSharedBuf;
//////////////////////////////////////////////////////////////////////////
// h264����
class H264Data
{
public:
	H264Data(VideoFrame  vH264Frame)
	{
		m_pH264Data = (VideoFrame*)malloc(sizeof(VideoFrame));
		*m_pH264Data = vH264Frame;
		m_pH264Data->data = (unsigned char *)malloc(vH264Frame.size);
		memcpy(m_pH264Data->data, vH264Frame.data, vH264Frame.size);

	}
	~H264Data()
	{
		if(m_pH264Data->data)
		{
			free(m_pH264Data->data);
		}
		if(m_pH264Data)
		{
			free(m_pH264Data);
		}
	}
public:
	VideoFrame * GetH264Frame()
	{
		return m_pH264Data;
	}

private:
	VideoFrame * m_pH264Data;
};

//���ͨ����
//���������������桢��¼���width��height�ȹ��ܣ���������ͼ�������Ӧ�ò�
class PVideoFrame
{
public:
    static void InitEx();
    static void UninitEx();
    static void SetCheckFrameParam(int nTimeoutMillisecs = 5000, int nNoFrameCameTimeoutSecs = 180);
public:
	PVideoFrame(IVideoService* pService);
	virtual ~PVideoFrame(void);
public:
	void Destory();
	virtual void OnVideoFrame(void* data);
	virtual void StartSendFrame(int width, int height, BOOL bPlaySucceed,int bMode=0);
	virtual void StopSendFrame();
	virtual BOOL CheckVideoFrame(BOOL bConvert, const VideoFrame& vframe);
	virtual BOOL CopyVideoFrame(void* dstBuf, const VideoFrame& vframe);

	inline const VideoFrame* GetVideoFrame() const{
		return &this->m_videoFrame;
	}

	inline LPBYTE GetSharedBuf() {
		return (LPBYTE)m_bufFrame.Check(this->m_videoFrame.size);
	}

	// ���û������
	virtual BOOL SetFrameCacheParam(int nMaxFrameCache, int nMaxDelayCache, int nNormalInterval, int nMinInterval);
	// ����֡��
	inline BOOL SetFrameRate(int fps) {
		InterlockedExchange(&m_nSetFrameInterval, 1000/fps);
		return TRUE;
	}
	// ��ȡ֡��
	inline LONG GetFrameRate() const {
		return 1000/m_nSetFrameInterval;
	}

	inline void SetChannel(void* hplay, void* playuser) {
		m_hplay = hplay;
		m_playuser = playuser;
	}
	inline void ChangeMain(BOOL bMain) {
		InterlockedExchange(&m_bMainChannel, bMain);
	}
	inline BOOL IsMainChannel() const {
		return (BOOL)m_bMainChannel;
	}

protected:
	BOOL AllocImageCache();

	inline void SendFrame(VideoFrame& vframe){
		if (m_pService && vframe.data)
			m_pService->OnSendVideoFrame(vframe, m_hplay, m_playuser);
	}

	// ���h264����
	void ClearH264Cache();

public:
	int m_DataType;// 2����NVMM, 1����ΪH264����0����yuv
	list <H264Data *> m_listH264;
	HSCMutex m_lockListFrame;//H264�߳�������
	int m_bMode;
protected:
	IVideoService* m_pService;
	void* m_hplay; // ͨ����
	VideoFrame m_videoFrame; // һ֡ͼ��
	BOOL m_vflip;//�Ƿ���֡
	SharedBuf m_bufFrame; // ֡����
	volatile LONG m_bPlaying;
	volatile LONG m_bPlaySucceed; // �Ƿ��Ѿ��ɹ�������Ƶ�ɹ�
	BOOL m_bOutputOriginalSize; // �Ƿ����ԭʼͼ���С
	volatile LONG m_bMainChannel; // ��ͨ����ֻ����ͨ������������Ƶ��ʧ�����������
	void* m_playuser;
	BOOL m_bConvert;
	int m_nWidthConverted;
	int m_nHeightConverted;
	unsigned int m_nSizeConverted;

#if PVS_USING_CACHE
	// ֡����
	int m_nMaxFrameCache; // ��󻺴�֡��
	int m_nMaxDelayCache; // �����ʱ����֡����������д�Ĳ�ࣩ
	int m_nNormalFrameInterval; // ������ȡ֡���������
	int m_nMinFrameInterval; // ��С��ȡʱ��������д�������ʱ��
	unsigned char* m_pFrameCache; // ֡����
	volatile LONG m_nCurrReadCache; // ��ǰ������֡����
	volatile LONG m_nCurrWriteCache; // ��ǰд����֡����
	volatile LONG m_nFrameCache; // ��ǰ�����֡��
#else
	// ֡���
	volatile LONG m_bHasFrameCame; // ��ָ��ʱ�������Ƿ�������
#endif

	LONG m_nCurrFrameInterval; // ��ʱ�߳�ʱ����
	volatile LONG m_nSetFrameInterval; // ���õ�֡����ʱ����

	// ��ʱ�߳�
	volatile LONG m_bExit;
	volatile LONG m_bRun;
	HANDLE m_hThreadFrame;
	HANDLE m_hEvtFrame;

	static unsigned int CALLBACK ThreadRoutine(void* lpParam);
	virtual void ThreadFrameHandler();
protected:
	// ����s_nMaxNoFrameCameMilliSecsû��ͼ�������ϲ�㱨Err_OverTimeNoStream��Ϣ
	static int s_nMaxNoFrameCameMilliSecs;
	// ��Ƶ��ʧͼ��
	static VideoFrame s_missFrame;
	// ����Ƶ��ʧ���֮������������������룩
	static int s_nNoFrameCameTimeoutMillisecs;

	//�Ƿ񿽱�missͼ
	static BOOL s_bIsShouldCopyMiss;
	//�೤ʱ��û������,��ʱ�����ԭ���߼�����ʼ��ʱ��������
	static int s_nMaxNoFrameCameSec;
	//�೤ʱ��û������,ʱ��ͳ��
	int m_nMaxNoFrameCameCount;
	// ��״̬�仯��ʶ�����ڿ���û����ʱ������־ֻ���һ��
	BOOL m_bFrameState; 
};
