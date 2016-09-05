#ifndef SC_NET_CONFIG_H
#define SC_NET_CONFIG_H

#include "ScType.h"

#  ifdef __cplusplus
extern "C" {
#  endif /* __cplusplus */

/** @file ScNetConfig.h
* ������Ϣ��ȡ�������ຯ��		
���ڶ�����������ֻ�Ե�һ���������л�ȡ������*/

/**
 @brief ��ȡ������
 @param szHostName ������[�������]
 @return ScErr
 @see scSetHostName() ScErr.h
 */
SCAPI(ScErr)  scGetHostName(char  szHostName[256]);

/**
 @brief ��ȡ����ip��ַ
 @param szLocalIP ip��ַ[�������]
 @return ScErr
 @see scSetLocalIPAddr() ScErr.h
 */
SCAPI(ScErr)  scGetLocalIPAddr(char szLocalIP[16]);

/**
 @brief ��ȡip��ַ����
 @param szLocalIPMask ip��ַ����[�������]
 @return ScErr
 @see scSetLocalIPMask() ScErr.h
 */
SCAPI(ScErr)  scGetLocalIPMask(char szLocalIPMask[16]);

/**
 @brief ��ȡ����ip
 @param szGateWay ���ص�ַ[�������]
 @return ScErr
 @see scSetGatewayIP() ScErr.h
 */
SCAPI(ScErr)  scGetGatewayIP(char szGateWay[16]);

/**
 @brief ��ȡ����
 @param szDomainName ����[�������]
 @return ScErr
 @see scSetDomainName() ScErr.h
 */
SCAPI(ScErr)  scGetDomainName(char szDomainName[256]);

/**
 @brief ��ȡdns������ip
 @param szDNSServer DNS��������ַ[�������]
 @return ScErr
 @see scSetDNSServer() ScErr.h
 */
SCAPI(ScErr)  scGetDNSServer(char szDNSServer[16]);

/**
 @brief ��ȡ����mac��ַ����binary��ʽ��
 @param bMac mac��ַ[�������]
 @return ScErr
 @see scSetLocalMac()��scGetLocalMacFormat() ScErr.h
 */
SCAPI(ScErr)  scGetLocalMac(unsigned char bMac[6]);

/**
 @brief ��ȡ����mac��ַ��6λʮ�������ַ�����ʽxx-xx-xx-xx-xx-xx��
 @param szMacFormat mac��ַ[�������]
 @return ScErr
 @see scSetLocalMac()scGetLocalMac() ScErr.h
 */
SCAPI(ScErr)  scGetLocalMacFormat(char szMacFormat[64]);


/**
 @brief ����������
 @param szHostName ������
 @return ScErr
 @see scGetHostName() ScErr.h
 */
SCAPI(ScErr) scSetHostName(char * szHostName);


/**
 @brief ���ñ���ip��ַ
 @param szIPAddr ip��ַ
 @return ScErr
 @see scGetLocalIPAddr() ScErr.h
 */
SCAPI(ScErr) scSetLocalIPAddr(const char * szIPAddr);
/**
 @brief ����ip��ַ����
 @param szMask ip��ַ����
 @return ScErr
 @see scGetLocalIPMask() ScErr.h
 */
SCAPI(ScErr) scSetLocalIPMask(char * szMask);

/**
 @brief ��������ip
 @param szGatewayIP ���ص�ַ
 @return ScErr
 @see scGetGatewayIP() ScErr.h
 */
SCAPI(ScErr) scSetGatewayIP(char *szGatewayIP);

/**
 @brief ��������
 @param szDomainName ����
 @return ScErr
 @see scGetDomainName() ScErr.h
 */
SCAPI(ScErr) scSetDomainName(char * szDomainName);

/**
 @brief ����dns������ip
 @param szServer DNS��������ַ
 @return ScErr
 @see scGetDNSServer() ScErr.h
 */
SCAPI(ScErr) scSetDNSServer(char * szServer);

/**
 @brief ���ñ���mac��ַ����binary��ʽ��
 @param bMac mac��ַ
 @return ScErr
 @see scGetLocalMac()��scGetLocalMacFormat() ScErr.h
 */
SCAPI(ScErr) scSetLocalMac(unsigned char  bMac[6]);

/************************************************************************/
/* ������������CheckNetCharRationality��CheckNetMsgRationality�Ƿ�񲻺õĽӿڣ�Ŀǰ����scframework��ʹ�ã����������벻Ҫʹ��������������
scframework�����Ҳ����ȥ���öԺ����ĵ��ã���ʱҲ����scfl����ɾ��*/
/************************************************************************/
//����һ���ַ����Ƿ��Ǻ���ĵ��ʮ����ip
SCAPI(int) CheckNetCharRationality(char * szValue);
//����������Ϣ�Ƿ�Ϸ�
SCAPI(int) CheckNetMsgRationality(char * szIP,char * szMask,char * szGateWay,unsigned char * pMac);




/**
 @brief �ж�һ���ַ����Ƿ�����Ч�ĵ��ʮ����ip
 @param szIP ip��ַ
 @return TRUE��Ч FALSE ��Ч
 @see IsMacVaild()
 */
SCAPI(BOOL) IsIPValid(const char* szIP);

/**
 @brief �ж�һ��mac��ַ�Ƿ���Ч���Ϸ���mac��ַ���2bit���붼��00
 @param mac mac��ַ
 @return TRUE��Ч FALSE ��Ч
 @see IsIPValid()
 */
SCAPI(BOOL) IsMacVaild(unsigned char mac[6]);

//
/**
 @brief ��������IPת��Ϊ���ʮ����
 @param szIP ���ʮ����ip��ַ[�������]
 @param nIPValue ������ip��ַ
 @return ScErr
 @see ScErr.h
 */
SCAPI(ScErr) scNet_ntoa(/*InOut*/ char  szIP[16],unsigned int nIPValue);



#ifdef __cplusplus
}
#endif /* __cplusplus */


#endif