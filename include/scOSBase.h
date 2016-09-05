#ifndef SC_OS_BASE_H
#define SC_OS_BASE_H


#  ifdef __cplusplus
extern "C" {
#  endif /* __cplusplus */


/************************************************************************/
/* ϵͳ�ຯ��														    */
/************************************************************************/

//��ȡ�豸id
//DeviceID���İ��豸ͳһ����ı�ʶ����Ϊֻ���ֶΡ�
ScErr  scGetDeviceID(char DeviceID[256]);

//��ȡ�̸߳���
HANDLE scGetCurrentThreadHandle();

ScErr scSleep(unsigned int unMS);

//����ϵͳ
ScErr scRestartSystem();

//�����ڴ�ӿڣ���ĳЩǶ��ʽƽ̨�£�����ָ��������ڴ����Ϊĳ��ֵ��nStep������������ϵͳ������ڴ���Զ���nStep���в���
void* scMalloc(int nSize,int nStep);

//��õ�ǰ���¶ȣ���λC
ScErr scReadCurTemperature(float* pCurTptr);

//��ȡӲ���汾����Ϣ
ScErr scGetHardwareVersion(char * szValue);

//�õ�CUPռ����
ScErr scGetCpuUsageRate(long* pCurUsage);
//�Լ�������ռ���ڴ��С
ScErr scGetMemUsageRate(long* pMemUsage);






/************************************************************************/
/* �������                                                             */
/************************************************************************/
//ScTextOut��������֣��������еĺܶ���붼����ô˺������������һЩ״̬�ʹ�����Ϣ��
//��ͬ��ϵͳ�в�ͬ��ʵ�֣����Ӧ�����Լ�����ʵ�֣���Ҫ����RegTxtOut����ע��һ��ScTextOutCallback�ص�
typedef void (*ScTextOutCallback)(const char* szSection,const char* szFormat,...);
ScErr RegTextOut(ScTextOutCallback pCB);
ScErr ScTextOut(const char* szSection,const char* szFormat,...);



#ifdef __cplusplus
}
#endif /* __cplusplus */


#endif
