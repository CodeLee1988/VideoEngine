#ifndef _SCTIME_H
#define _SCTIME_H

#include "ScType.h"
//#include "ScPreConfigs.h"

/** @file ScTime.h
* �������ڶԿ�ƽ̨��ʱ���������֧�֣������˻�ȡ����ϵͳʱ�䣬ȡ�߾���ʱ�䣬ʱ����ʱ�����������ʱ���ʽ���ȡ�
*/

#  ifdef __cplusplus
extern "C" {
#  endif /* __cplusplus */

typedef double TIMESPAN ;

/**
 *@brief ��ȡ����ʱ��
 *@param[out] pScSystemTime ���ڷ��ر���ʱ��
 *@return SC_ErrSuccess �ɹ�
 *@return SC_ErrParamerErr pScSystemTimeΪNULL
 *@see scSetLocalTime
 */
SCAPI(ScErr)  scGetLocalTime(ScSystemTime *pScSystemTime);

/**
 *@brief ���ñ���ʱ��
 *@param[in] pScSystemTime �������õ�ʱ��
 *@return SC_ErrSuccess �ɹ�
 *@return SC_ErrParamerErr pScSystemTimeΪNULL
 *@see scGetLocalTime
 */
SCAPI(ScErr) scSetLocalTime(ScSystemTime* pScSystemTime);

/**
 *@brief ��ȡ�߾���ʱ�䣬�߾���ʱ�䱾��û�����壬��Ҫȡ���ʱ��ʱʹ�ã�ʱ�����Ծ�ȷ������
 *@param[out] pnRTime ���ڷ��ظ߾���ʱ��
 *@return SC_ErrSuccess �ɹ�
 *@return SC_ErrParamerErr pnRTimeΪNULL
 *@see scGetRelativeTimeSpan
 */
SCAPI(ScErr) scGetRelativeTime(unsigned int * pnRTime);

/**
 *@brief ��ȡ�����߾���ʱ���ʱ���
 *@param[in] nTime1 �߾���ʱ��1
 *@param[in] nTime2 �߾���ʱ��2
 *@param[out] pnSpan ���ڷ���nTime1-nTime2��ʱ���
 *@return SC_ErrSuccess �ɹ�
 *@return SC_ErrParamerErr pnSpanΪNULL
 *@see scGetRelativeTimeSpan
 */
SCAPI(ScErr) scGetRelativeTimeSpan(unsigned int nTime1,unsigned int nTime2,int *pnSpan/*����*/);

/**
 *@brief �ж�����
 *@param[in] year ���
 *@return year�����귵��TRUE����֮����FALSE
 *@see scGetSystemTimeDayOfYear
 *@see scGetSystemTimeDayOfWeek
 */
SCAPI(BOOL) scGudgeYear(int year);

/**
 *@brief �õ���ǰ�����Ǳ���ĵڼ���
 *@param[in] pScSystemTime ����
 *@return ����pScSystemTime�Ǳ���ĵڼ���
 *@see scGudgeYear
 *@see scGetSystemTimeDayOfWeek
 */
SCAPI(int) scGetSystemTimeDayOfYear(const ScSystemTime *pScSystemTime);

/**
 *@brief �õ���ǰ���������ڼ�
 *@param[in] pScSystemTime ����
 *@return ����pScSystemTime�����ڼ�������7��ʾ������
 *@see scGudgeYear
 *@see scGetSystemTimeDayOfYear
 */
SCAPI(int) scGetSystemTimeDayOfWeek(const ScSystemTime *pScSystemTime);

/**
 *@brief ����ʱ���
 *@param[in] nDay ����
 *@param[in] nHours Сʱ��
 *@param[in] nMins ������
 *@param[in] nSecs ����
 *@param[in] nMilliseconds ������
 *@return ����һ��ʱ���TIMESPAN
 */
SCAPI(TIMESPAN) scMakeTimeSpan(int nDay,int nHours,int nMins,int nSecs,int nMilliseconds);

/**
 *@brief �õ�ʱ��������
 *@param[in] ts ʱ���
 *@return ����tsʱ��������
 *@see scGetTimeSpanHours
 *@see scGetTimeSpanMinutes
 *@see scGetTimeSpanSeconds
 *@see scGetTimeSpanMSeconds
 */
SCAPI(int) scGetTimeSpanDays(TIMESPAN ts);

/**
 *@brief �õ�ʱ����Сʱ��
 *@param[in] ts ʱ���
 *@return ����tsʱ����Сʱ��
 *@see scGetTimeSpanDays
 *@see scGetTimeSpanMinutes
 *@see scGetTimeSpanSeconds
 *@see scGetTimeSpanMSeconds
 */
SCAPI(int) scGetTimeSpanHours(TIMESPAN ts);

/**
 *@brief �õ�ʱ���ķ�����
 *@param[in] ts ʱ���
 *@return ����tsʱ���ķ�����
 *@see scGetTimeSpanDays
 *@see scGetTimeSpanHours
 *@see scGetTimeSpanSeconds
 *@see scGetTimeSpanMSeconds
 */
SCAPI(int) scGetTimeSpanMinutes(TIMESPAN ts);

/**
 *@brief �õ�ʱ��������
 *@param[in] ts ʱ���
 *@return ����tsʱ��������
 *@see scGetTimeSpanDays
 *@see scGetTimeSpanHours
 *@see scGetTimeSpanMinutes
 *@see scGetTimeSpanMSeconds
 */
SCAPI(int) scGetTimeSpanSeconds(TIMESPAN ts);

/**
 *@brief �õ�ʱ���ĺ�����
 *@param[in] ts ʱ���
 *@return ����tsʱ���ĺ�����
 *@see scGetTimeSpanDays
 *@see scGetTimeSpanHours
 *@see scGetTimeSpanMinutes
 *@see scGetTimeSpanSeconds
 */
SCAPI(int) scGetTimeSpanMSeconds(TIMESPAN ts);

/**
 *@brief �õ�ʱ����������
 *@param[in] ts ʱ���
 *@return ����tsʱ����������
 *@see scGetTimeSpanTotalHours
 *@see scGetTimeSpanTotalMinutes
 *@see scGetTimeSpanTotalSeconds
 *@see scGetTimeSpanTotalMSeconds
 */
SCAPI(int) scGetTimeSpanTotalDays(TIMESPAN ts);

/**
 *@brief �õ�ʱ������Сʱ��
 *@param[in] ts ʱ���
 *@return ����tsʱ������Сʱ��
 *@see scGetTimeSpanTotalDays
 *@see scGetTimeSpanTotalMinutes
 *@see scGetTimeSpanTotalSeconds
 *@see scGetTimeSpanTotalMSeconds
 */
SCAPI(int) scGetTimeSpanTotalHours(TIMESPAN ts);

/**
 *@brief �õ�ʱ�����ܷ�����
 *@param[in] ts ʱ���
 *@return ����tsʱ�����ܷ�����
 *@see scGetTimeSpanTotalDays
 *@see scGetTimeSpanTotalHours
 *@see scGetTimeSpanTotalSeconds
 *@see scGetTimeSpanTotalMSeconds
 */
SCAPI(int) scGetTimeSpanTotalMinutes(TIMESPAN ts);

/**
 *@brief �õ�ʱ����������
 *@param[in] ts ʱ���
 *@param[out] pSeconds ����ʱ����������
 *@return SC_ErrSuccess �ɹ�
 *@return SC_ErrParamerErr ����������int�ܱ��ķ�Χ��������ο�����Ϊ24000��
 *@see scGetTimeSpanTotalDays
 *@see scGetTimeSpanTotalHours
 *@see scGetTimeSpanTotalMinutes
 *@see scGetTimeSpanTotalMSeconds
 */
SCAPI(ScErr) scGetTimeSpanTotalSeconds(TIMESPAN ts,int* pSeconds);

/**
 *@brief �õ�ʱ�����ܺ�����
 *@param[in] ts ʱ���
 *@param[out] pMilliSeconds ����ʱ�����ܺ�����
 *@return SC_ErrSuccess �ɹ�
 *@return SC_ErrParamerErr �ܺ���������int�ܱ��ķ�Χ��������ο�����Ϊ24��
 *@see scGetTimeSpanTotalDays
 *@see scGetTimeSpanTotalHours
 *@see scGetTimeSpanTotalMinutes
 *@see scGetTimeSpanTotalSeconds
 */
SCAPI(ScErr) scGetTimeSpanTotalMSeconds(TIMESPAN ts,int* pMilliSeconds);

/**
 *@brief �Ƚ�����ʱ��Ĵ�С
 *@param[in] pScSystemTime1 ʱ��1
 *@param[in] pScSystemTime2 ʱ��2 
 *@return pScSystemTime1����pScSystemTime2����1�����ڷ���0��С�ڷ���-1
 *@see scTimeSpanCompare
 */
SCAPI(int) scSystemTimeCompare(const ScSystemTime *pScSystemTime1,const ScSystemTime *pScSystemTime2);

/**
 *@brief �ж�����ʱ���ľ���ֵ�Ĵ�С
 *@param[in] ts1 ʱ���1
 *@param[in] ts2 ʱ���2 
 *@return |ts1|����|ts2|����1�����ڷ���0��С�ڷ���-1
 *@see scSystemTimeCompare
 */
SCAPI(int) scTimeSpanCompare(TIMESPAN ts1, TIMESPAN ts2);

/**
 *@brief ����ʱ���
 *@param[in] pScSystemTime1 ʱ��1
 *@param[in] pScSystemTime2 ʱ��2 
 *@return ����pScSystemTime1��pScSystemTime2��ʱ���
 *@see scSystemTimeAdd
 *@see scSystemTimeSub
 */
SCAPI(TIMESPAN) scGetSystemTimeSpan(const ScSystemTime *pScSystemTime1,const ScSystemTime *pScSystemTime2);

/**
 *@brief ����ʱ�����ʱ���õ���ʱ��
 *@param[in] pScSystemTime ʱ��
 *@param[in] ts ʱ���
 *@return ����pScSystemTime����ts��õ����µ�ʱ��
 *@see scGetSystemTimeSpan
 *@see scSystemTimeSub
 */
SCAPI(ScSystemTime) scSystemTimeAdd(const ScSystemTime *pScSystemTime,TIMESPAN ts);

/**
 *@brief ����ʱ���ȥʱ���õ���ʱ��
 *@param[in] pScSystemTime ʱ��
 *@param[in] ts ʱ���
 *@return ����pScSystemTime��ȥts��õ����µ�ʱ��
 *@see scGetSystemTimeSpan
 *@see scSystemTimeAdd
 */
SCAPI(ScSystemTime) scSystemTimeSub(const ScSystemTime *pScSystemTime,TIMESPAN ts);

/**
 *@brief �ж�ʱ��������պϷ���
 *@param[in] st ʱ��
 *@return �Ϸ�����TRUE����֮����FALSE
 *@see scIsTimeValidHMS_ms
 *@see scIsTimeValid
 */
SCAPI(BOOL) scIsTimeValidYMD(ScSystemTime st);

/**
 *@brief �ж�ʱ���ʱ����+����Ϸ���
 *@param[in] st ʱ��
 *@return �Ϸ�����TRUE����֮����FALSE
 *@see scIsTimeValidYMD
 *@see scIsTimeValid
 */
SCAPI(BOOL) scIsTimeValidHMS_ms(ScSystemTime st);

/**
 *@brief �ж�����ʱ��ĺϷ���
 *@param[in] st ʱ��
 *@return �Ϸ�����TRUE����֮����FALSE
 *@see scIsTimeValidYMD
 *@see scIsTimeValidHMS_ms
 */
SCAPI(BOOL) scIsTimeValid(ScSystemTime st);

/**
 *@brief ��ʱ�䰴ָ����ʽ���
 *@param[in] st ʱ��
 *@param[in] szFormat ָ��ʱ������ĸ�ʽ�������ʽ�����strftime
 *@param[out] szDest ������ַ���
 *@return SC_ErrSuccess �ɹ�
 *@return SC_ErrParamerErr ��������
 *@see scSystemTimeFormatYMDhms
 *@see scSystemTimeFormatYMDhms_ms
 *@see scSystemTimeFormatYMD
 *@see scSystemTimeLoadYMDhms
 *@see scSystemTimeLoadYMDhms_ms
 */
SCAPI(ScErr) scSystemTimeFormat(ScSystemTime st, const char* szFormat ,OUT char* szDest);

/**
 *@brief ��ʱ�䰴��YYYY-MM-DD hh:mm:ss����ʽ���
 *@param[in] st ʱ��
 *@param[out] szYMDhms ������ַ���
 *@return SC_ErrSuccess �ɹ�
 *@return SC_ErrParamerErr ��������
 *@see scSystemTimeFormat
 *@see scSystemTimeFormatYMDhms_ms
 *@see scSystemTimeFormatYMD
 *@see scSystemTimeLoadYMDhms
 *@see scSystemTimeLoadYMDhms_ms
 */
SCAPI(ScErr) scSystemTimeFormatYMDhms(ScSystemTime st, OUT char* szYMDhms); 

/**
 *@brief ��ʱ�䰴��YYYY-MM-DD hh:mm:ss.mms����ʽ���
 *@param[in] st ʱ��
 *@param[out] szYMDhms_ms ������ַ���
 *@return SC_ErrSuccess �ɹ�
 *@return SC_ErrParamerErr ��������
 *@see scSystemTimeFormat
 *@see scSystemTimeFormatYMDhms
 *@see scSystemTimeFormatYMD
 *@see scSystemTimeLoadYMDhms
 *@see scSystemTimeLoadYMDhms_ms
 */
SCAPI(ScErr) scSystemTimeFormatYMDhms_ms(ScSystemTime st, OUT char* szYMDhms_ms);

/**
 *@brief ��ʱ�䰴��YYYY-MM-DD����ʽ���
 *@param[in] st ʱ��
 *@param[out] szYMD ������ַ���
 *@return SC_ErrSuccess �ɹ�
 *@return SC_ErrParamerErr ��������
 *@see scSystemTimeFormat
 *@see scSystemTimeFormatYMDhms
 *@see scSystemTimeFormatYMDhms_ms
 *@see scSystemTimeLoadYMDhms
 *@see scSystemTimeLoadYMDhms_ms
 */
SCAPI(ScErr) scSystemTimeFormatYMD(ScSystemTime st, OUT char* szYMD); 

/**
 *@brief ����YYYY-MM-DD hh:mm:ss����ʽ���ַ�������ʱ��ṹ��
 *@param[out] st ����ʱ��
 *@param[in] szYMDhms ��YYYY-MM-DD hh:mm:ss����ʽ���ַ���
 *@return SC_ErrSuccess �ɹ�
 *@return SC_ErrParamerErr st��szYMDhmsΪNULL
 *@return SC_ErrDataTransErr szYMDhmsת��ʱ����һ�����Ϸ���ʱ��
 *@see scSystemTimeFormat
 *@see scSystemTimeFormatYMDhms
 *@see scSystemTimeFormatYMDhms_ms
 *@see scSystemTimeFormatYMD
 *@see scSystemTimeLoadYMDhms_ms
 */
SCAPI(ScErr) scSystemTimeLoadYMDhms(OUT ScSystemTime* st,const char* szYMDhms);

/**
 *@brief ����YYYY-MM-DD hh:mm:ss.mms����ʽ���ַ�������ʱ��ṹ��
 *@param[out] st ����ʱ��
 *@param[in] szYMDhms_ms ��YYYY-MM-DD hh:mm:ss.mms����ʽ���ַ���
 *@return SC_ErrSuccess �ɹ�
 *@return SC_ErrParamerErr st��szYMDhms_msΪNULL
 *@return SC_ErrDataTransErr szYMDhms_msת��ʱ����һ�����Ϸ���ʱ��
 *@see scSystemTimeFormat
 *@see scSystemTimeFormatYMDhms
 *@see scSystemTimeFormatYMDhms_ms
 *@see scSystemTimeFormatYMD
 *@see scSystemTimeLoadYMDhms
 */
SCAPI(ScErr) scSystemTimeLoadYMDhms_ms(OUT ScSystemTime* st,const char* szYMDhms_ms);

#ifdef __cplusplus
}
#endif /* __cplusplus */

#endif //_SCTIME_H
