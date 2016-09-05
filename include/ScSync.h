#ifndef SCSYNC_H
#define SCSYNC_H
#include "ScType.h"
/** @class CSCLock CSCAutoLock
*  @brief �ٽ�����.
*
* �ṩ���̷߳���ͬһ����Դʱ���Ļ���
*/

class CSCLock
{
public:
	CSCLock(void);
	~CSCLock(void);

	/** 
	*@brief ����
	*/
	void Lock();
	/** 
	*@brief �ͷ���
	*/
	void Unlock();
private:
	/** @brief ��������ָ��ͨ�ø��Ե�ƽ̨�ϵ���ȥ������� */
	void *m_pLock;

};

class CSCAutoLock
{
public:
    CSCAutoLock(CSCLock& lock);
    ~CSCAutoLock();

private:
    CSCAutoLock();
    CSCLock* m_pLock;
};

#endif
