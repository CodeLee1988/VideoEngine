#ifndef __COMMONERR_H__
#define __COMMONERR_H__

//������Ϣ��ʶ
typedef enum
{
	Err_Success = 0 ,		//���гɹ�
	Err_SceneStop,		//����ֹͣ״̬
	Err_SceneFinish,		//�������״̬
	Err_ScenePause,		//������ͣ״̬
	Err_SceneWait,		//���ڵȴ�״̬
	Err_NoIdleVA,		//û�п��е�VA����
	Err_NotSupportAlgoType,	//��֧�ֵ��㷨����
	Err_RunFailed,		//���г���ʧ��
	Err_OverTimeNoStream = 1000		//��ʱ��û����������
}CommonErr;

#define ErrSuccessMsg "����"
#define ErrSceneStopMsg "ֹͣ"
#define ErrSceneFinishMsg "���"
#define ErrScenePauseMsg "��ͣ"
#define ErrSceneWaitMsg "�ȴ�"
#define ErrNoIdleVAMsg "�޿���ͨ������"
#define ErrNotSupportAlgoTypeMsg "�㷨���Ͳ�֧��"
#define ErrRunFailed	"���г���ʧ��"
#define ErrOverTimeNoStreamMsg "δ��ȡ����Ƶ����"
#endif
