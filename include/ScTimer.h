#ifndef SCTIMER_H
#define SCTIMER_H

#include "ScType.h"
#include "ScThread.h"
#ifndef CALLBACK
#define CALLBACK
#endif
/** @class CSCTimer 
*  @brief ��ʱ����.
*
* 
*/

typedef void* PVOID;

typedef void (CALLBACK *HighTimerProc)(PVOID pUserData, unsigned long dwTimeElapse);
class CSCTimer
{
public:
	CSCTimer(void);
	~CSCTimer(void);

	/** ������ʱ��
	@param nPeriod ��ʱ����
	@param time_proc �̵߳Ļص�����
	@param pUserData �ص��������û�����
	@return ����ʱ���Ƿ�ɹ�
	@see End()
	@par	ʾ��:
	@code

	void __stdcall Time1Proc(VOID*pUserData, unsigned long dwTimeElapse)
	{
	}
	CSCTimer timer;
	timer.Begin(2000,Time1Proc,NULL);

	@endcode
	*/
	BOOL Begin(int nPeriod, HighTimerProc time_proc, PVOID pUserData);

	/** �رն�ʱ�� 	
	@return �Ƿ�ɹ�
	@see Begin()
	*/	
	BOOL End();
	/** �����Ƿ�Ϊһ�ζ�ʱ��
	@param bRunOnce ��ʾ�Ƿ�Ϊһ�εĶ�ʱ����TRUE��ʾ�ǣ�FALSE��ʾ����
	*/	
	void SetRunOnce( BOOL bRunOnce );
	/** �����Ƿ�Ϊ��ʱ�������ɹ������������һ�λ��ǵõȵ����ʱ��������õĶ�ʱ���ڲſ�ʼ����
	@param bBeginRun ���ɹ������������һ�λ��ǵõȵ����ʱ��������õĶ�ʱ���ڲſ�ʼ���У�TRUE��ʾ�ǣ�FALSE��ʾ����
	*/	
	void SetBeginRun( BOOL bBeginRun );

	/** ��ʱ�����д�����
	@see Begin() End();
	*/
	void TimerProcProxy();
private:
	BOOL            m_bRunOnce;
	BOOL            m_bBeginRun;
	HighTimerProc	m_TimerCallback;
	CSCThread       m_hTimerThread;
	BOOL            m_bStopThread;
	int             m_nPeriod;
	PVOID           m_pUserData;
};

#endif
