#ifndef _Video_FRAME_H
#define _Video_FRAME_H
#include "ScMutex.h"
#include "ScType.h"

class SC_EXPORTS CVideoFrame
{
public:
	CVideoFrame();
	~CVideoFrame();

public:
	void AddRef();
	void ReleaseRef();

	BYTE* LockFrame(int &nFrameLen);
	void UnlockFrame();

	//��֡�������
	ScErr SetFrameData(BYTE*pData,unsigned int nDataLen,ScSystemTime *pstFrameTime,BOOL bIFrame,unsigned int nUserData = 0);
	//�������ݣ���һ���������٣����RefΪ0ʱ���������٣�
	ScErr ResetFrameData();
	//ӵ�����ݣ������Ա����̵߳��ã�
	BOOL HasData();

	ScErr GetFrameTime(ScSystemTime&stFrameTime);

	unsigned int GetFrameUserData();

	BOOL IsIFrame();

private:
	void lock();
	void unlock();

private:
	ScSystemTime m_stFrameTime;//֡ʱ��
	BOOL m_bIFrame;//�Ƿ�ΪI֡
	BYTE *m_pData;//֡���ݳ���
	unsigned int m_nDataLenth;//֡���ݳ���
	HSCMutex m_hMutex;//������
	unsigned int m_nRefCnt;//�������ü���
	unsigned int m_nUserData;
};

#endif