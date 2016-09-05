#pragma once

#include "tstring.h"
#include "PlatformInterface.h"
#include "PvsVideoFrame.h"
#include "ScImage.h"
#include "ScPreConfigs.h"
#include "ScTypeEx.h"
#include <map>
#include <vector>
#include <list>

typedef std::map<string,node::PBaseNode> PBaseNodeMap;
typedef std::map<node::PCameraNode,long> PtzCommandMap;
typedef std::map<void*, int> FrameReferenceCountMap;

// ץͼ�ṹ
struct CapturedPicture
{
	volatile LONG cap; // �Ƿ���Ҫץͼ
	BOOL wait; // �Ƿ�ȴ����
	HANDLE evt; // ץͼ�ȴ��¼�
	BOOL res; // ץͼ���
	TCHAR file[MAX_PATH]; // ͼƬ����·��

	CapturedPicture()
	{
		this->cap = 0;
		this->wait = 0;
		this->evt = NULL;
		this->res = FALSE;
		this->file[0] = _T('\0');
	}
	~CapturedPicture()
	{
		if (evt)
		{
			CloseHandle(evt);
			evt = NULL;
		}
	}
};

//////////////////////////////////////////////////////////////////////////
typedef std::list<PVideoFrame*> VideoFrameList;

struct VideoCache
{
	volatile LONG nPlayRef; // �ýڵ㲥�ż���
	node::PCameraNode cnPlay; // ���Žڵ�
	BOOL bPlayState; // ����״̬
	VideoFrameList lstVideoFrame; // ͨ���б���һ��Ϊ��ͨ��������Ϊ��ͨ������ͨ����������������Ƶ
	CRITICAL_SECTION csVideo; // ͨ���б�ͬ����
	CapturedPicture* pCapture; // ץͼ�ṹ
	volatile LONG nH264FrameCount;//H264�Ĳ��ż���,Ϊ���ò��֪���Ƿ����ϴ�H264��
	volatile LONG nRollDataCount;//RollData�Ĳ��ż�����Ϊ���ò��֪���Ƿ����ϴ�RollData��
	volatile LONG nNvmmDataCount;//Nvmm�Ĳ��ż�����Ϊ���ò��֪���Ƿ����ϴ�NVMM����

	VideoCache()
	{
		nH264FrameCount = 0;
		nRollDataCount = 0;
		nNvmmDataCount = 0;
		nPlayRef = 0;
		cnPlay = NULL;
		bPlayState = FALSE;
		InitializeCriticalSection(&csVideo);
		pCapture = new CapturedPicture;
	}
	~VideoCache()
	{
		DeleteCriticalSection(&csVideo);
		if (pCapture)
		{
			delete pCapture;
			pCapture = NULL;
		}
	}
	inline void lock()
	{
		EnterCriticalSection(&csVideo);
	}
	inline void unlock()
	{
		LeaveCriticalSection(&csVideo);
	}
	inline void StopPlay()
	{
		bPlayState = FALSE;
		if (cnPlay)
		{
			cnPlay->StopPlay();
			cnPlay = NULL;
		}
	}
};

//////////////////////////////////////////////////////////////////////////
typedef struct tagPlayHandle
{
	VideoCache* cache;
	PVideoFrame* video;
	tagPlayHandle()
	{
		cache = NULL;
		video = NULL;
	}
	~tagPlayHandle()
	{
		if (video)
		{
			delete video;
			video = NULL;
		}
	}
	inline void InvalidHandle()
	{
		cache = NULL;
	}
	inline BOOL IsInvalidHandle() const
	{
		if (cache == NULL)
			return TRUE;
		if (cache->cnPlay == NULL)
			return TRUE;
		return FALSE;
	}
}*PlayHandle;

typedef std::vector<PlayHandle> PlayHandleVector;
typedef std::map<node::PCameraNode, PlayHandleVector>PCameraHandleMap; // ��������handle��ӳ���ϵ
// Auto lock
class AutoLock
{
public:
	AutoLock(CRITICAL_SECTION *cs_ptr) { _cs_ptr = cs_ptr; EnterCriticalSection(cs_ptr); }
	~AutoLock() { LeaveCriticalSection(_cs_ptr); }
private:
	CRITICAL_SECTION *_cs_ptr;
};

//////////////////////////////////////////////////////////////////////////
class CPlatformVideoService :
	public IPlatformNotify, public IVideoService
{
public:
	CPlatformVideoService(int nVideo);
	~CPlatformVideoService(void);

public:
	// ֪ͨ�����豸����
	// ���ݴ���Ĵ�����֯�ṹ���豸����ӵ�������
	// ÿ����һ�ν����Ȳ��ҵ����ҽڵ㣬��ոó��ҽڵ��µ����нڵ㣬���������
	// �������Ŀ�ֵ����ֱ�ӷ���
	// ���øýӿڲ���ɾ�����ҽڵ㣬ֻ��������ó����µĽڵ�
	long OnDeviceChanged(const node::PVendorNode pNode);
	long OnGetPlayCount(node::PlayCount & vPlayCount, void* user);//��ȡ��ͬ�������㲥�Ĵ���
	// ��Ƶ֡���ݻص�
	long OnDecodeFrame(VideoFrame& vframe, void* user);

	// �����־
	long OnOutputLog(LPCTSTR pszLog, LPCTSTR FuncName=_T(""), LPCTSTR FileName=_T(""), long Line=__LINE__, long Level=LEV_INFO);

	// ��������¼�
	long OnOutputError(string sCamID, CommonErr err);

	// ����0��ʾ��ץͼ��1��ʾץͼ��ɣ�-1��ʾץͼʧ��
	long OnCaptureFrame(LPCTSTR lpszCamID/*���ID*/, OUT LONG* pChnNo/*ͨ����*/, IN OUT TCHAR szImagePath[MAX_PATH]/*�洢��ͼƬ·��*/);

	// ��������������ʱ�ⲿ����ӿ�
	// nError������궨��
	long OnProcessPlatformError(LPCTSTR lpszVendorName, long nError);

	// ����������Ҫ�����涨ʱ��ʱ���ɵ��øýӿ����
	// ����ֵ���ڵ������ʾ���óɹ�����Ϊ���õ�TIMER IDֵ��С�����ʾʧ��
	// ����Ļص���������ֵ�����-1������ٸö�ʱ��
	long OnSetPlatformTimer(UINT nElapse, ThrdPlatformTimer lpfnTimer, void* pvContext);

public:
	void DestroyPlayHandle();
	long SetVideoFrameCallback(PVideoFrameCallback pfnVideoFrameCallback, void* user);
	long SetOutputLogCallback(POutputLogCallback pfnOutputLog, void* user);
	long SetOutputErrorCallback(POutputErrorCallback pfnOutputErr, void*user);
	long GetDeviceList(node::PRootNode &pBaseNode);
	long GetDeviceListXML(tstring& xmlDev); // ��ȡ�豸�б�XML
	long GetConfigXML(tstring& xmlCfg); // ��ȡ������ϢXML
	long SetConfigXML(LPCTSTR xmlCfg); // ����������ϢXML
	long StartRecordFile(HPVSPLAY hPlay, const char* file); // ��ʼ����¼��
	long StopRecordFile(HPVSPLAY hPlay); // ֹͣ����¼��
	long PtzControl(node::PCameraNode pCam, PVS_PtzMsgContent *ptzCommand); // PTZ ����
	long PtzControl(HPVSPLAY hPlay, PVS_PtzMsgContent *ptzCommand); // PTZ ����
	long PtzControl(LPCTSTR devid, PVS_PtzMsgContent *ptzCommand); // PTZ ����
	long Capture(HPVSPLAY hPlay, const char* file, int wait); // ��ͼ
	int GetFrameRate(HPVSPLAY hPlay); // ��ȡ֡��
	long SetFrameRate(HPVSPLAY hPlay, int fps); // ����֡��
	long SetConfig(LPCTSTR key, void* param, void* value); // ���ò���
	long GetConfig(LPCTSTR key, void* param, void** value); // ��ȡ����
	long DestroyContent(void** value); // ���ٻ�ȡ�������ص�����

private:
	// ���ݷ��ͻص�
	virtual void OnSendVideoFrame(VideoFrame& vframe, void* cacheuser, void* playuser);
	// ��������ص�
	virtual long OnReplayChannel(void* cacheuser);

public:
	// ��ʼ����
	// ���ز��ž��
	// ����-1ʧ��
	PlayHandle StartPlay(LPCTSTR devid, void* user, int type=0, int bMode=0);
	// ��ʼ���ţ����������ͼ��ߴ�
	// ���ز��ž��
	// ����-1ʧ��
	PlayHandle StartPlay(LPCTSTR devid, int width, int height, void* user, int type=0, int bMode=0);
	PlayHandle StartRealPlay(IPlatformInterface *pPlatform, node::CameraNode *pCam, int width, int height, void* context, int type=0, int bMode=0);
	PlayHandle StartRealPlay(const PVS_RealPlay *realplay, int width, int height, void *context);
	// ֹͣ����
	long StopPlay(HPVSPLAY hPlay/*���ŷ��صľ��*/);

	// �ͷ�PVS�����Դ
	// hPlay ���ž����hResrc��Դָ��
	long ReleasePVSResource(HPVSPLAY hPlay, ResourceHandle hResrc);

	// �������ͼ��ߴ�
	long SetImageSize(int width, int height);
	// ���û������
	long SetFrameCacheParam(int nMaxFrameCache, int nMaxDelayCache, int nNormalFps, int nMaxFps);

	// ת��֡���ݸ�ʽ
	static BOOL ConvertFrameToRGB24(LPBYTE pDstBuf, int nDstWidth, int nDstHeight, const VideoFrame* pVideoFrame);

private:
	BOOL FindVendorByCamID(LPCTSTR lpszCamID, IPlatformInterface** ppPlatform, node::PCameraNode* ppCam);
	BOOL FindVendorByVenderIPChannel(const char* szIP, const char* szChannel, IPlatformInterface** ppPlatform, node::PCameraNode* ppCam);
	BOOL GetAvailableVideo(node::PCameraNode pCamNode, void* user, PlayHandle* pPlayHandle, int type = 0);
	void AvailVideo(PlayHandle hPlay);
	PlayHandle FromPVSPlayHandle(HPVSPLAY hPlay);

	// xml��ת����DeviceChanged�ṹ��ǰ���˵�δ�޸ĵĶ���
	BOOL FilterDeviceChangeInfo(node::PVendorNode pNode, const DeviceChanged* device, const ChannelChanged* channel);
	// �����豸�ڵ�ǰ���
	// �鿴�����豸�ڵ�ǰ�Ƿ�����ص���ƵԴ�ڲ��ţ��������ֹͣ�����ٸ���
	BOOL PrepareForChangeNode(node::PVendorNode pNode, DeviceChanged* pDeviceNode);

	PlayHandleVector GetCameraPlayHandle(node::PCameraNode pCam);
	void StopPlayAll(); // ֹͣ������Ƶ�Ĳ���
private:
	PVideoFrameCallback m_pfnVideoFrameCallback; // ͼ�����ݻص�
	void* m_pVideoCallbackUser; // �������ݻص��û�����

	POutputLogCallback m_pfnOutputLogCallback; // �����־�ص�
	void* m_pOutputLogUser; // �����־�ص��û�����

	POutputErrorCallback m_pfnOutputErrorCallback; // ��������¼��ص�
	void* m_pOutputErrorUser;

	int m_nWidth; // ���ͼ���
	int m_nHeight; // ���ͼ���
	int m_nVideoCount; // ֧�ֵ���Ƶ����
	volatile LONG m_nUsedVideo; // ��ǰ�Ѿ�ʹ�õ���Ƶ����
	PBaseNodeMap m_mapVendorNodes; // ���ҽڵ�ӳ���
	VideoCache* m_pVideoCache; // ����ͨ������ӳ��
	PlayHandle m_pPlayHandle; // ���ž������
	PtzCommandMap m_mapLastPtzCmd; // ��¼����һ���������̨��������
	volatile LONG m_bConvertFrameToRGB; // �Ƿ�YUV����ת����RGB����
    HSCMutex m_lockMapFrameRef;
	FrameReferenceCountMap m_mapReferenceCount; // ֡�����ü���

	CRITICAL_SECTION m_csRealPlay; // ����ͬ����
	PCameraHandleMap m_mapCameraHandle; // ������ƵԴ����Ӧ��pvs handle
	std::vector<PlayHandle> m_vtPvsStopHandle; // ��pvs���Լ�����ֹͣ���ŵľ������	
};
