#ifndef __PLATFORMNOTIFY_H__
#define __PLATFORMNOTIFY_H__

#include "PvsVideoDef.h"
#include "basictypedef.h"
#include "LxLogDef.h"

typedef int (CALLBACK* ThrdPlatformTimer)(UINT nIDEvent, void* pvContext);

// ��������ģ�������ʱ��ͨ����������Ӧ�Ķ���
#define PFE_QUIT   -1 // Ҫ���˳�����
#define PFE_OK      0 // ��
#define PFE_REINIT  1 // Ҫ�����³�ʼ��ģ��

//////////////////////////////////////////////////////////////////////////

class IPlatformNotify
{
public:
	IPlatformNotify(){};
	virtual ~IPlatformNotify(){};

public:
	// ֪ͨ�����豸����
	// ���ݴ���Ĵ�����֯�ṹ���豸����ӵ�������
	// ÿ����һ�ν����Ȳ��ҵ����ҽڵ㣬��ոó��ҽڵ��µ����нڵ㣬���������
	// �������Ŀ�ֵ����ֱ�ӷ���
	// ���øýӿڲ���ɾ�����ҽڵ㣬ֻ��������ó����µĽڵ�
	virtual long OnDeviceChanged(const node::PVendorNode pNode) = 0;
	virtual long OnGetPlayCount(node::PlayCount & vPlayCount, void* user) = 0;//��ȡ��ͬ�������㲥�Ĵ���

	// ��Ƶ֡���ݻص�
	virtual long OnDecodeFrame(VideoFrame& vframe, void* user) = 0;

	// �����־
	virtual long OnOutputLog(LPCTSTR pszLog, LPCTSTR FuncName=_T(""), LPCTSTR FileName=_T(""), long Line=__LINE__, long Level=LEV_INFO) = 0;

	// ����0��ʾ��ץͼ��1��ʾץͼ��ɣ�-1��ʾץͼʧ��
	virtual long OnCaptureFrame(LPCTSTR lpszCamID/*���ID*/, OUT LONG* pChnNo/*ͨ����*/, IN OUT TCHAR szImagePath[MAX_PATH]/*�洢��ͼƬ·��*/) = 0;

	// ��������������ʱ�ⲿ����ӿ�
	// nError������궨��
	virtual long OnProcessPlatformError(LPCTSTR lpszVendorName, long nError) = 0;

	// ����������Ҫ�����涨ʱ��ʱ���ɵ��øýӿ����
	// ����ֵ���ڵ������ʾ���óɹ�����Ϊ���õ�TIMER IDֵ��С�����ʾʧ��
	// ����Ļص���������ֵ�����-1������ٸö�ʱ��
	virtual long OnSetPlatformTimer(UINT nElapse, ThrdPlatformTimer lpfnTimer, void* pvContext) = 0;
};

#endif
