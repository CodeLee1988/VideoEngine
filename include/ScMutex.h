#ifndef  SC_MUTEX_H
#define  SC_MUTEX_H

#include "ScType.h"


#  ifdef __cplusplus 
extern "C" {
#  endif /* __cplusplus */
/************************************************************************/
/* �ٽ���mutex�����ڶ��߳�ʱ����������Դ��
��ʹ��ǰ����scLockMutex�������ʹ�ú�scUnlockMutex��
mutex�ᱣ֤ͬʱֻ��һ���߳̿��Է��ʣ�lock��unlock֮��Ĵ���Σ��Ӷ��Դ�����б�����
scLockMutex��scUnlockMutex�ķ�ΧӦ�þ���С�������̻߳����˷���Դ*/
/************************************************************************/


//�ٽ������	
typedef void* HSCMutex;
//�����ٽ��������ʹ��ǰ�ޱȴ���һ�����
SCAPI(HSCMutex) scCreateMutex();
//�����ٽ������������ʹ��ʱ���١�
SCAPI(void) scDestroyMutex(HSCMutex hMutex);
//��ס(���롢�ȴ�)�ٽ���
SCAPI(void) scLockMutex(HSCMutex hMutex);
//��(�뿪)�ٽ���
SCAPI(void) scUnlockMutex(HSCMutex hMutex);

#ifdef __cplusplus
}
#endif /* __cplusplus */

#endif 
