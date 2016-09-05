#ifndef _Video_BUFFER_H
#define _Video_BUFFER_H
#include "VideoFrame.h"
#include <list>
using std::list;

class SC_EXPORTS CVideoBuffer
{
public:
	CVideoBuffer();
	~CVideoBuffer();

public:
	ScErr Initialize(int nFrameNum);
	ScErr LockShortVideoFrameList(ScSystemTime stStart, ScSystemTime stEnd,list<CVideoFrame*> &lOutFrame);
	ScErr LockShortVideoFrameList(int nTime, CVideoFrame* pBeg, list<CVideoFrame*> &lOutFrame);
	ScErr LockVframeVideoFrameList(CVideoFrame* pVframe, ScSystemTime stEnd,list<CVideoFrame*> &lOutFrame);
	
	ScErr UnlockShortVideoFrameList(list<CVideoFrame*> lInFrame);
	ScErr PushData(BYTE*pData,unsigned int nDataLen,ScSystemTime *pstFrameTime,BOOL bIFrame,unsigned int nUserData = 0);

private:
	//��ȡһ֡�ڵ㣨�����Ա����̵߳��ã�
	CVideoFrame*GetOneFrame();
	void lockAllFramelist();
	void unlockAllFramelist();
	void lockVdCachelist();
	void unlockVdCachelist();

private:
	list<CVideoFrame*> m_listAllFrame;//���������CVideoFrame
	list<CVideoFrame*> m_listVideoCache;//��������¼���CVideoFrame
	int m_nFrameCnt;//���Ļ���֡��
	HSCMutex m_hMutexAll;//m_listAllFrame����
	HSCMutex m_hMutexCache;//m_listVideoCache����
};


#endif