// PVSEXPORTS.H
#ifndef __PVSEXPORTS_H__
#define __PVSEXPORTS_H__

#include "PvsDef.h"

#ifdef __cplusplus
extern "C" {
#endif

#ifdef _LINUX
#ifdef PVS_EXPORTS
#	define VION_PVS_API __attribute__((visibility("default")))
#else
#	define VION_PVS_API
#endif
#elif defined _WINDOWS
#ifdef PVS_EXPORTS
#	define VION_PVS_API __declspec(dllexport)
#else
#	define VION_PVS_API __declspec(dllimport)
#endif
#endif

//////////////////////////////////////////////////////////////////////////
// ��ʼ��PVS
// �ڵ����κ�PVS��SDK֮ǰ�ȵ��øýӿڳ�ʼ��
// nVideo - ֧�ֵ���Ƶ����
// pfnOutputLog - ��־�ص�
// user - ��־�ص��û�����
VION_PVS_API PVS_BOOL PVS_Init(int nVideo, POutputLogCallback pfnOutputLog, void* user);
// �ͷ�PVS��Դ
// �ڳ����˳�֮��Ҫ�ͷ���Դ
VION_PVS_API PVS_BOOL PVS_Uninit();

// ��ʼ����
// ��������������Ӧ��һ��һ����ʼ������Ҳһ��
// Ҳ���ǲ�Ҫ�ڶ��߳���ʹ�ÿ�ʼ��ֹͣ
// bPlyaMode��0��ʾ�����Ľ��벥�ţ�1��ʾ�����н��룬�ܹ�����ptz����
//type: 0 ��ʾ�򿪽���ͨ����1��ʾ��H264ͨ��
// ����INVALID_PLAY_HANDLE��ʾʧ�ܣ�������0�ɹ�
VION_PVS_API HPVSPLAY PVS_StartPlay(const char* devid, void* user, int type=0, int bPlyaMode=0);
// ��ʼ���ţ����������ͼ��ߴ�
// width��height����-1��ԭʼͼ��ߴ����
// bPlyaMode��0��ʾ�����Ľ��벥�ţ�1��ʾ�����н��룬�ܹ�����ptz����
//type: 0 ��ʾ�򿪽���ͨ����1��ʾ��H264ͨ��
// ����INVALID_PLAY_HANDLE��ʾʧ�ܣ�������0�ɹ�
VION_PVS_API HPVSPLAY PVS_StartPlayEx(const char* devid, int width, int height, void* user, int type=0, int bPlyaMode=0);

// ��ʼԤ��
// ����ָ���豸����
// ����INVALID_PLAY_HANDLE��ʾʧ�ܣ�������0�ɹ�
VION_PVS_API HPVSPLAY PVS_StartRealPlay(const PVS_RealPlay *realplay, int width, int height, void *context);

// ֹͣ����
VION_PVS_API PVS_BOOL PVS_StopPlay(HPVSPLAY hPlay);

// �ͷ�PVS�����Դ
// hPlay ���ž����hResrc��Դָ��
VION_PVS_API PVS_BOOL PVS_ReleasePVSResource(HPVSPLAY hPlay, ResourceHandle hResrc);

// ��̨����
VION_PVS_API PVS_BOOL PVS_PtzControl(HPVSPLAY hPlay, PVS_PtzMsgContent *ptzCommand);

// ��̨����
// �ڲ�������Ƶ�������ͨ������������
VION_PVS_API PVS_BOOL PVS_PtzControlEx(const char* devid, PVS_PtzMsgContent *ptzCommand);

// ��ʼ����¼���ļ�
// hPlay - ���ž��
VION_PVS_API PVS_BOOL PVS_StartRecordFile(HPVSPLAY hPlay, const char* file);

// ֹͣ����¼���ļ�
// hPlay - ���ž��
VION_PVS_API PVS_BOOL PVS_StopRecordFile(HPVSPLAY hPlay);

// �����ͼ
// hPlay - ���ž��
// file - ͼƬ����·��
// wait - �Ƿ�ȴ�ץͼ���(0-���ȴ���1-�ȴ�)
VION_PVS_API PVS_BOOL PVS_Capture(HPVSPLAY hPlay, const char* file, int wait);

// ��ȡ֡��
// hPlay - ���ž��
// ����-1��ʾʧ�ܣ����ڵ������ʾ֡��ֵ
VION_PVS_API int PVS_GetFrameRate(HPVSPLAY hPlay);

// ����֡��
// hPlay - ���ž��
VION_PVS_API PVS_BOOL PVS_SetFrameRate(HPVSPLAY hPlay, int fps);

// ͳһ�������ͼ��ߴ�
// �ڲ��ŵĹ��������û�ʧ��
// width - ͼ���
// height - ͼ���
VION_PVS_API PVS_BOOL PVS_SetOutputImageSize(int width, int height);

// ����ͼ�����ݻص�
// �ڲ��ŵĹ��������û�ʧ��
VION_PVS_API PVS_BOOL PVS_SetVideoFrameCallback(PVideoFrameCallback pfnVideoFrame, void* user);

// ���ô���ص�����
VION_PVS_API PVS_BOOL PVS_SetErrorCallback(POutputErrorCallback pfnError, void*user);

//���ò�����Ҳ�ɵ�����չ�ӿ�ʹ��
VION_PVS_API PVS_BOOL PVS_SetConfig(const char* key, void* param, void* value);
// ��ȡ����
VION_PVS_API PVS_BOOL PVS_GetConfig(const char* key, void* param, void** value);
// �ͷ�PVS_GetConfig��ȡ������
VION_PVS_API PVS_BOOL PVS_DestroyContent(void** content);

#ifdef __cplusplus
}
#endif
#endif //__PVSEXPORTS_H__

