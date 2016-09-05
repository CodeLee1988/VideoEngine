#ifndef SCLOGGER_H
#define SCLOGGER_H

#include "ScType.h"
#include "ScSync.h"
#include "ScThread.h"
#include <list>
#include <string>
#include <map>
using namespace std;

/** @class SCLogger
    @brief д��־������
	@warning ÿ�����̲�Ҫʹ�ö����־ʵ��������һ��ʵ������SetFileSize�ͻ�����һ���̣߳�����ϵͳ����
*/

#define LT_OTHER		0 /** ��־���� - ������־*/
#define LT_RUNINFO      1 /** ��־���� - ������Ϣ*/
#define LT_OPERATION    2 /** ��־���� - ������־*/
#define LT_ERROR        3 /** ��־���� - ������־*/
#define LT_ALARM        4 /** ��־���� - ������־*/

#define FILT_NO         0 /** ���˼��� - ������*/
#define FILT_SAME       1 /** ���˼��� - ��ͬ���ˣ���ʱ����+������ͬ��*/
#define FILT_ALL        2 /** ���˼��� - �������еģ�ֻ��ʱ������*/

#ifndef MAX_PATH
#define MAX_PATH        260
#endif
#define MAX_SEC_LEN		64
#define MAX_CON_LEN		512
#define MAX_LOG_COUNT	30000
#define QL_OK			1 //�ɹ�
#define QL_ERROR		2 //ʧ��
#define QL_NOTENOUGH	3 //��־��������

/** @brief ��־�洢·������*/
typedef enum
{
	/** @brief �������ʽҪ��*/
    Enum_PathType_None = 0,
	/** @brief ����洢/YYYYMM/DD*/
    Enum_PathType_Day = 1, 
}EnumPathType;

struct LogItem
{
	/** @brief ����*/
    int   nType;          
	/** @brief ��־ʱ��*/
    ScSystemTime stLogTime;    
	/** @brief �ֿ�*/
    char  szSection[MAX_SEC_LEN];    
	/** @brief ��־����*/
    char  szLog[MAX_CON_LEN];      
};
class MyStringCmp;
class SCLogger
{
public:
    SCLogger(void);
    ~SCLogger(void);

	/**������־·��,������Ĭ��·��Ϊ D:\\log
	@param lpszLogPathName ��־�洢·��
	@return void 
	@par ʾ��:
	@code
	SCLogger log ; 
	log.SetPathName("d:/vionlog/nvr");
	@endcode
	*/
    void SetPathName(const char* lpszLogPathName );            

	/**���������Section��Ĭ��Ϊviontech���޶�SectionName�ĳ��Ȳ��ܳ���MAX_SEC_LEN���ֽ�
	@param lpszSectionName ��־�����֣�������.log
	@return ���Ƿ���TRUE�������������ɹ�
	@par ʾ����
	@code
	log.SetSectionName("test.log");//������־������ļ��� (�ͳн���������)
	@endcode
	*/
    BOOL SetSectionName(const char* lpszSectionName = "viontech");

	/**������־�ļ���С��λK�����ļ���С����nLogSize��ʱ����XX002��XX003����������־�ļ� ��nLogDays��ǰ�ڵ�ʱ��ʼɾ����־�� ������Ĭ��ֵΪ�����
	@param nLogSize �����־�ļ����ֽ���
	@param nLogDays ��־��������
	@return void
	@par ʾ����
	@code
	log.SetWatchInfo(1024,5); //��������ã��Ͳ������������־·���̣߳�
	@endcode
	*/
    void SetWatchInfo(int nLogSize = 0, int nLogDays = 0, int nType = 0);

	/**����nDebug=TRUE ��ʱ������AddLog������bDebug=TRUE����־
	@param bDebug ����nDebug=TRUE ��ʱ������AddLog������bDebug=TRUE����־��Ĭ��ΪFALSE
	@return void
	@par ʾ����
	@code
	log.SetWorkMode(FALSE);  //��DEBUGģʽ
	log.AddLog("my test debugmode",LT_ERROR,TRUE); //�����־  -----------�������
	log.AddLog("my test debugmode",LT_ERROR,FALSE); //�����־ -----------�����
	log.SetWorkMode(TRUE);
	log.AddLog("my test debugmode",LT_ERROR,TRUE); //�����־  -----------�����
	log.AddLog("my test debugmode",LT_ERROR,FALSE); //�����־ -----------�����
	@endcode
	*/
    void SetWorkMode(BOOL bDebug = FALSE);
	
	/**���ù��˼���ͼ�� nFLevel ���˼���nMS ʱ�������루 ����ʱ���ڣ������ظ��Ͳ�д��־�� �� ������Ĭ��Ϊ������
    @param nFLevel���˼���
	@param nMS ʱ��������
	@return void
	@par ʾ����
	@code
	log.SetFilter(FILT_SAME,5) ;//��ʾ5����������ͬ�����ݻᱻ����
	@endcode
	*/
	void SetFilter(int nFLevel, int nMS);

	/**����Ϊѹ��ģʽ,������Ĭ��Ϊ��ѹ��
	@param nCompress ѹ��ģʽ
	@return void
	@code
	�˺���������
	@endcode
	*/
    void SetCompressMode(BOOL nCompress = FALSE);

    /**����·������,��������Enum_PathType_None��û���ر��·����ʽ����������Enum_PathType_Day��·��������/���ʽ�洢
    @param umPathType ��־·����ʽ
	@return void
	@code
	log.SetPathType(Enum_PathType_Day);
	@endcode
	*/
	void SetPathType(EnumPathType umPathType);

	/**�����־, �޶�lpszText�ĳ��Ȳ��ܳ���MAX_CON_LEN���ֽ�,�����Ĳ��ֻᱻ�ض�
	@param lpszText ��־����
	@param nType ��־����
	@param bDebug ���ģʽ
	@return �Ƿ�ɹ�
	@code
	log.SetWorkMode();
	log.AddLog(szBuffer, LT_RUNINFO);
	@endcode
	*/
	BOOL AddLog(const char* lpszText, int nType ,BOOL bDebug=FALSE);//������־, lpszText��־���� nType��־���� nDebug���ģʽ

    /**��־��ѯ
	@param nType �ڵ�ǰ��־Ŀ¼����ǰSection����������ΪnType(-1��ʾ����)
	@param stBegin  ��־��ʼʱ��
	@param stEnd ��־����ʱ��
	@param listLogItems �����ǰMAX_LOG_COUNT����¼
	@return QL_OK�ɹ���QL_ERRORʧ�ܣ�QL_NOTENOUGH��־��������MAX_LOG_COUNT
	*/
	long QueryLog(int nType, ScSystemTime stBegin, ScSystemTime stEnd, std::list<LogItem>& listLogItems);

	/**��־��ѯ
	@param nType �ڵ�ǰ��־Ŀ¼����ǰSection����������ΪnType(-1��ʾ����)
	@param listLogItems �����ǰMAX_LOG_COUNT����¼
	@return QL_OK�ɹ���QL_ERRORʧ�ܣ�QL_NOTENOUGH��־��������MAX_LOG_COUNT
	*/
    long QueryLog(int nType, std::list<LogItem>& listLogItems);

	/**��־��ѯ
	@param lpszLogPathName ������lpszLogPathName��־Ŀ¼
	@param lpszSectionName ����SectionΪlpszSectionName(lpszSectionNameΪNULL�򳤶�Ϊ0ʱ��ʾ����section)����־��
	@param nType ��������ΪnType(-1��ʾ����).
	@param stBegin ��־��ʼʱ��
	@param stEnd ��־����ʱ��
	//����ֵ��QL_OK�ɹ���QL_ERRORʧ�ܣ�QL_NOTENOUGH��־��������MAX_LOG_COUNT��listLogItems������ǰMAX_LOG_COUNT����¼
	*/
	static long QueryLog(const char* lpszLogPathName,const char* lpszSectionName, int nType, ScSystemTime stBegin, ScSystemTime stEnd, std::list<LogItem>& listLogItems);
	
	/**��־��ѯ
	@param lpszLogPathName ������־Ŀ¼
	@param lpszSectionName SectionΪlpszSectionName(lpszSectionNameΪNULL�򳤶�Ϊ0ʱ��ʾ����section)����־
	@param nType ��������ΪnType(-1��ʾ����)����־
	@param listLogItems �����ǰMAX_LOG_COUNT����¼
	@return QL_OK�ɹ���QL_ERRORʧ�ܣ�QL_NOTENOUGH��־��������MAX_LOG_COUNT
	*/
	static long QueryLog(const char* lpszLogPathName,const char* lpszSectionName, int nType, std::list<LogItem>& listLogItems);
	
	/**������lpszLogPathName��־Ŀ¼�����е�SectionName
	@param lpszLogPathName ��־��ѯ·��
	@param listSectionItems ���Section
	@return void
	*/
	static void QuerySection(const char* lpszLogPathName,std::list<std::string>& listSectionItems);

	friend class MyStringCmp;
public:
	/** @brief ���治ͬ��־���Ͷ�Ӧ��ʱ��*/
	map<int , int> m_nTypeSaveDay;
private:
	/** @brief �����־·���߳�*/
	static void CALLBACK WatchFileThread(void *pParam);
	/** @brief ��־���Ӻ���*/
	void WatchFileThreadFun();
	/** @brief �ж��Ƿ������־���������������־���ͺ���־������������m_nMsʱ��������ͬ������Ϲ�����������TRUE�����򲻷��Ϸ���FALSE*/
	BOOL IsFiltLogText(int nType, const char* lpszLogText);//
	/** @brief �ж���־�ļ�������*/
	void ReadLogType(const char * szFileFullPath, OUT int * nType );
	/** @brief �����ɾ����־��Ϣ*/
	void AddDelLog(const char *szBuf);
	/** @brief ������־·��*/
	char m_szLogPathName[MAX_PATH];
	/** @brief ��������ļ���*/
	char m_szSectionName[MAX_SEC_LEN]; 
	/** @brief �ļ���ȫ·��*/
	char m_szFullFileName[MAX_PATH];
	/** @brief ������־����*/
	char m_szPreLogText[MAX_CON_LEN];  
	/** @brief ������־����*/
	int m_nPreType;                 
	/** brief �ϴ���־������ʱ��*/
	unsigned int m_dwPreTickCount; 
	/** @brief ���ģʽ*/
	BOOL m_bDebug; 
	/** @brief ���˼���*/
	int m_nFLevel;
	/** @brief ʱ����*/
	int m_nMs;
	/** @brief �Ƿ�Ϊѹ��ģʽ*/
	BOOL m_bCompress;      
	/** brief �Ƿ������˼����߳�*/
	BOOL m_bIsRunThread;             
	/** @brief �����ļ���С ��λK*/
	int m_nLogSize;
	//** @brief ����Ŀ¼��С ��λ��*/
	int m_nLogok;
	//** @brief ���Ƽ��Ƶ����*/
	int m_nWatchContrl ;          

	/** @brief �߳�*/
	CSCThread m_WatchThread;    
	/** @brief ��*/
	CSCLock   m_Lock;            

	/** @brief ���Ƽ����־·���̱߳���*/
	BOOL m_bExitThread; 
	/** @brief ��־·�����ͣ�����EnumPathType����*/
	EnumPathType m_LogPathType;
	/** @brief ��¼��Ŀ¼/����*/
    list<string> m_szLogPath;
	/** @brief ��¼��Ŀ¼/����/�գ������Ĳ�ѯ·����*/
    list<string> m_szLogPath2;
private:
	static long QueryLog(const char* lpszLogPathName,const char* lpszSectionName, int nType, ScSystemTime stBegin, ScSystemTime stEnd, std::list<LogItem>& listLogItems, BOOL bJudgeTime);
	static BOOL IsSectionMatch(const char* lpszFileName, const char* lpszSectionName);
	static BOOL ReadLogFile(const char* lpszPathName, const char* lpszFileName, const char* lpszSectionName,int nType, ScSystemTime stBegin, ScSystemTime stEnd, std::list<LogItem>& listLogItems,BOOL bJudgeTime);
	static void FindMatchFileName(const char* lpszPathName, const char* lpszSectionName, std::list<std::string>& listFileName);
	static void GetSectionFromFileName(const char* lpszFileName,char* pSectionName);
	static BOOL GetTimeFromFileName(const char* lpszFileName,ScSystemTime& stTime);

    /**���ҳ���·���µ������ļ���,���͸�·���ϲ���������Ĳ�ѯ·��,�˽ӿڲ�����ʹ��*/
    void FindAllPath();
};

#endif
