#ifndef FILEUTILS_H
#define FILEUTILS_H
#include "ScType.h"

/** @file ScFileUtils.h
* ����Կ�ƽ̨���ļ���������֧�֣�������linux��windowsϵͳ
* �����ļ���Ŀ¼�����̿ռ�Ȳ���				
*/

#define   NORMAL_DEL   0x00000000 //ɾ������ͨģʽ
#define   FORCE_DEL    0x00000001 //ɾ����ǿ��ģʽ

#ifndef MAX_PATH

#define MAX_PATH 260

#endif

#ifdef __cplusplus
extern "C" {
#endif /* __cplusplus */


/**
*@brief ��ȡ��ִ�г�����ļ�·��
*@param[out] pszDstDirPath ���ڷ��ػ�ȡ���ı���·��
*@return SC_ErrSuccess �ɹ�
*@return SC_ErrNullReturn pszDstDirPathΪNULL
*@see scGetModulePath
*/
SCAPI(ScErr) scGetModulePath(char *pszDstDirPath);


/**
*@brief ��ȡ��ִ�г�����ļ���
*@param[out] pszDstModuleName ���ڷ��ؿ�ִ�г�����ļ���
*@return SC_ErrSuccess �ɹ�
*@return SC_ErrNullReturn pszDstModuleNameΪNULL
*@see scGetModuleName
*/
SCAPI(ScErr) scGetModuleName(char *pszDstModuleName);


/**
*@brief ��ȡĳ��Module���ڵĵ��ļ�·��
*@param[in] szModuleName ĳ��Module������
*@param[out] pszDstDirPath ��ȡ���ص�Module���ڵĵ��ļ�·��
*@return SC_ErrSuccess �ɹ�
*@return SC_ErrNullReturn pszDstDirPathΪNULL
*@see scGetModulePathEX
*/
SCAPI(ScErr) scGetModulePathEX(char* szModuleName,char pszDstDirPath[MAX_PATH]);

/**
*@brief ɾ���ļ�Ŀ¼
*@param[in] pszDirPath ����ɾ�����ļ�Ŀ¼·��
*@param[in] unMode ɾ��ģʽ NORMAL_DEL����ͨģʽ�����Ŀ¼�ļ��������ļ�����Ŀ¼��ɾ��ʧ��
*                  FORCE_DEL ǿ��ģʽ����ͬĿ¼�µ��ļ�����Ŀ¼һ��ɾ��
*@return SC_ErrSuccess �ɹ�
*@return SC_ErrNullReturn pszDirPathΪNULL
*@see scDeleteDir
*/

SCAPI(ScErr) scDeleteDir(const char* pszDirPath,unsigned int unMode);

/**
*@brief �����ļ�Ŀ¼
*@param[in] pszDirPath ���贴�����ļ�Ŀ¼·��
*@return SC_ErrSuccess �ɹ�
*@return SC_ErrNullReturn pszDirPathΪNULL
*@see scCreateDir
*/
SCAPI(ScErr) scCreateDir(const char* pszDirPath);

/**
*@brief �����ļ�Ŀ¼��չ�ӿ�
*@param[in] pszDirPath ���贴�����ļ�Ŀ¼·��
*@param[in] unMode  ģʽCREATE_FILE �������򴴽��ļ���NOCREATE_FILE�����ڲ�����
*@return SC_ErrSuccess �ɹ�
*@return SC_ErrNullReturn pszDirPathΪNULL
*@see scCreateDirEx
*/

SCAPI(ScErr) scCreateDirEx(const char* pszDirPath,unsigned int unMode);

/**
*@brief �ж��ļ��Ƿ����,�������򴴽�
*@param[in] pszFileName �ļ�����
*@return SC_ErrSuccess �ɹ�
*@return SC_ErrParamerErr ����ʧ��
*@see scMakeSureFileExist
*/
SCAPI(ScErr) scMakeSureFileExist(const char*  pszFileName);


/**
*@brief �ж�Ŀ¼�Ƿ���ڣ��������򴴽�
*@param[in] strDir Ŀ¼·��
*@return SC_ErrSuccess �ɹ�
*@return SC_ErrNullReturn strDirΪNULL
*@see scMakeSureDirExist
*/

SCAPI(ScErr) scMakeSureDirExist(const char*  strDir);

/**
*@brief ��ȡ�ļ�·���е��ļ�����
*@param[in] pszFullPath �ļ�ȫ·��
*@param[out] szFileName ����ļ������ڴ�
*@return SC_ErrSuccess �ɹ�
*@return SC_ErrNullReturn pszFullPath��szFileNameΪNULL
*@see scGetFileName
*/
SCAPI(ScErr) scGetFileName(const char *pszFullPath, char szFileName[MAX_PATH]);

/**
*@brief ��ȡ�ļ�ȫ·���е��ļ�Ŀ¼
*@param[in] pszFullPath �ļ�ȫ·��
*@param[out] szPath ����ļ�·�����ڴ�
*@return SC_ErrSuccess �ɹ�
*@return SC_ErrNullReturn pszFullPath��szPathΪNULL
*@see scGetFilePath
*/
SCAPI(ScErr) scGetFilePath(const char*  pszFullPath,char*  szPath);


/**
*@brief ��ȡ���̵��ܿռ�
*@param[in] pszDiskName �̷�����
*@param[out] pSize �����������������λ��M��
*@return SC_ErrSuccess �ɹ�
*@return SC_ErrNullReturn pszDiskNameΪNULL
*return  SC_ErrUnknow Ϊϵͳ����ʧ��δ֪����
*@see scGetDiskSpace
*/
SCAPI(ScErr) scGetDiskSpace(const char*  pszDiskName,int* pSize) ;


/**
*@brief ��ȡ���̵�ʣ��ռ�
*@param[in] pszDiskName �̷�����
*@param[out] pSize �����������������λ��M��
*@return SC_ErrSuccess �ɹ�
*@return SC_ErrNullReturn pszDiskNameΪNULL
*return  SC_ErrUnknow Ϊϵͳ����ʧ��δ֪����
*@see scGetDiskFreeSpace
*/
SCAPI(ScErr) scGetDiskFreeSpace(const char*  pszDiskName,int* pSize);


/**
*@brief ��ȡϵͳ�д��̵��̷�����
*@param[out] pszDisk �Ŵ����̷����Ƶ�����
*@param[out] nDiskNum �����������nDiskNum �����Ǳ�ʾ����ĸ����������ʾ���̸���
*@return SC_ErrSuccess �ɹ�
*@return SC_ErrNullReturn pszDiskΪNULL
*return  SC_ErrMemNotEnough Ϊ�ڴ治��
*@see scGetSystemAllDiskName
*/
SCAPI(ScErr) scGetSystemAllDiskName(char *pszDisk[4],unsigned int* nDiskNum);

/**
*@brief �жϴ����ܷ��
*@param[in] ch �����̷������� ��C�������ִ�Сд
*@return SC_ErrAlreadyExisted ����
*@return SC_ErrNotExist ������
*@see scIsDiskExist
*/

SCAPI(ScErr) scIsDiskExist(const char ch);

/**
*@brief �ж��ļ���Ŀ¼�ļ�
*@param[in] szFullName �ļ�����
*@return SC_ErrYes ��
*@return SC_ErrNo ����
*@return SC_ErrNullReturn szFullNameΪNULL
*@see scCheckFileIsDir
*/
SCAPI(ScErr) scCheckFileIsDir(const char * szFullName);

/**
*@brief �ж��ļ��Ƿ����
*@param[in] pszFileName�ļ�����
*@return SC_ErrAlreadyExisted ����
*@return SC_ErrNotExist ������
*@return SC_ErrNullReturn pszFileNameΪNULL
*@see scIsFileExist
*/

SCAPI(ScErr) scIsFileExist(const char*  pszFileName);

/**
*@brief �ж�Ŀ¼�Ƿ����
*@param[in] pszDirPathĿ¼����
*@return SC_ErrAlreadyExisted ����
*@return SC_ErrNotExist ������
*@return SC_ErrNullReturn pszDirPathΪNULL
*@see scIsDirExist
*/
SCAPI(ScErr) scIsDirExist(const char* pszDirPath);

/**
*@brief ɾ���ļ�
*@param[in] pszFileFULLPathName�ļ�����
*@return SC_ErrSuccess �ɹ�
*@return SC_ErrNullReturn pszFileFULLPathNameΪNULL
*@see scDelFile
*/
SCAPI(ScErr) scDelFile(const char* pszFileFULLPathName);


/**
*@brief ȡ���ļ��Ĵ���ʱ��
*@param[in] pszFileName �ļ�����
*@param[out] pTime ʱ��ָ��
*@return SC_ErrSuccess �ɹ�
*@return SC_ErrParamerErr pszFileName��pTimeΪNULL
*@return SC_ErrUnknow     δ֪����
*@return SC_ErrOpenFileFailed ��ʾpszFileName������
*@see scGetCreateTime
*/
SCAPI(ScErr) scGetCreateTime(const char*  pszFileName,ScSystemTime* pTime);

/**
*@brief ȡ���ļ������һ�η���ʱ��
*@param[in] pszFileName �ļ�����
*@param[out] pTime ʱ��ָ��
*@return SC_ErrSuccess �ɹ�
*@return SC_ErrParamerErr pszFileName��pTimeΪNULL
*@return SC_ErrUnknow     δ֪����
*@return SC_ErrOpenFileFailed ��ʾpszFileName������
*@see scGetLastAccessTime
*/
SCAPI(ScErr) scGetLastAccessTime(const char*  pszFileName,ScSystemTime* pTime);


/**
*@brief ȡ���ļ������һ��дʱ��
*@param[in] pszFileName �ļ�����
*@param[out] pTime ʱ��ָ��
*@return SC_ErrSuccess �ɹ�
*@return SC_ErrParamerErr pszFileName��pTimeΪNULL
*@return SC_ErrUnknow     δ֪����
*@return SC_ErrOpenFileFailed ��ʾpszFileName������
*@see scGetLastWriteTime
*/
SCAPI(ScErr) scGetLastWriteTime(const char*  pszFileName,ScSystemTime* pTime);

/**
*@brief �ж��ļ��Ƿ�����������
*@param[in] pszFileName �ļ�����
*@return SC_ErrYes ��ʾ�и�����
*@return SC_ErrNo ��ʾû�и�����
*@return SC_ErrNullReturn pszFileNameΪNULL
*@see scIsHidden
*/
SCAPI(ScErr) scIsHidden(const char*  pszFileName);

/**
*@brief �ж��ļ��Ƿ�����������
*@param[in] pszFileName �ļ�����
*@return SC_ErrYes ��ʾ�и�����
*@return SC_ErrNo ��ʾû�и�����
*@return SC_ErrNullReturn pszFileNameΪNULL
*@see scIsNormal
*/
SCAPI(ScErr) scIsNormal(const char*  pszFileName);

/**
*@brief �ж��ļ��Ƿ���ֻ������
*@param[in] pszFileName �ļ�����
*@return SC_ErrYes ��ʾ�и�����
*@return SC_ErrNo ��ʾû�и�����
*@return SC_ErrNullReturn pszFileNameΪNULL
*@see scIsReadOnly
*/
SCAPI(ScErr) scIsReadOnly(const char*  pszFileName);

/**
*@brief �ж��ļ��Ƿ���ϵͳ�ļ�
*@param[in] pszFileName �ļ�����
*@return SC_ErrYes ��ʾ��ϵͳ�ļ�
*@return SC_ErrNo ��ʾ����ϵͳ�ļ�
*@return SC_ErrNullReturn pszFileNameΪNULL
*@see scIsSystem
*/
SCAPI(ScErr) scIsSystem(const char*  pszFileName);

/**
*@brief �ļ��Ŀ���
*@param[in] srcFilePath �������ļ�·����
*@param[in] destFilePath Ŀ���ļ�·��(�����д�ļ��������ļ�����Դ�ļ���һ�¡������ļ��������ļ�������д�ļ���һ��)
*@return SC_ErrSuccess �ɹ�
*@return SC_ErrNullReturn srcFilePath��destFilePathΪNULL
*@return SC_ErrNo ����ʧ��
*@see scCopyFile
*/
SCAPI(ScErr) scCopyFile(const char *srcFilePath, const char *destFilePath);
#ifdef __cplusplus
}
#endif /* __cplusplus */



#endif
