#ifndef _SCPROXML_H_
#define _SCPROXML_H_

#include "ScType.h"

#ifndef MAX_PATH
#define MAX_PATH 260
#endif

//#ifdef WIN32
//
//#ifndef SPAPNodePtr
//#import "msxml3.dll"
//#define SPAPNodePtr MSXML2::IXMLDOMNodePtr
//#endif
//
//#else
//typedef void* SPAPNodePtr;
//#endif
typedef void* SPAPNodePtr;
/** 
 *@class CSProXml 
 *@brief XML�ļ�������
 */
class SC_EXPORTS CSProXml
{
public:
	CSProXml();
	virtual ~CSProXml();
public:

public:	//
	/**
	*@brief װ��XML�ļ�
	*@param[in] cszFileFullPath XML�ļ���·��
	*@return �ɹ�����TRUE��ʧ�ܷ���FALSE
	*/
	BOOL LoadFromFile(const char* cszFileFullPath);
	/**
	*@brief ���ַ�����XML  ���鲻ʹ�ô˺����������һ��XML�ļ������紫������ֱ���ô˺������ؿ��ܻ���ز��ɹ�
	*@param[in] cszXML XML�ַ���
	*@return �ɹ�����TRUE��ʧ�ܷ���FALSE
	*/
	BOOL LoadFromXML(const char* cszXML);		
public:
	/**
	*@brief ����XML�ļ������ȫ·����Ŀ¼+�ļ�����
	*@param[in] cszFileFullPath XML�ļ����ȫ·��
	*@return �ɹ�����TRUE��ʧ�ܷ���FALSE
	*/
	BOOL SetOutputFile(const char* cszFileFullPath);
	/**
	*@brief ���ڴ������ݱ��浽�ļ�
	*@return �ɹ�����TRUE��ʧ�ܷ���FALSE
	*/
	BOOL SaveToFile();	// �����ļ�
	/**
	*@brief �õ�XML�ĳ���
	*@return ���س���
	*/
	int  GetDocXmlLen();
	/**
	*@brief �õ�XML������
	*@param[out] pszBuf ����XML������
	*@param[in] nBufLength pszBufָ���ڴ�Ĵ�С
	*@return �ɹ�����TRUE��ʧ�ܷ���FALSE
	*/
	BOOL GetDocXml(char* pszBuf,int nBufLength);
public:
	/**
	*@brief �������ڵ�
	*@param[in] cszNodeName ���ڵ������
	*@return ���ظ��ڵ��ָ��
	*/
	SPAPNodePtr CreateRootNode(const char* cszNodeName="");	 
	/**
	*@brief �����ڵ�
	*@param[in] cszNodeName �ڵ������
	*@return ���ؽڵ��ָ��
	*/
	SPAPNodePtr CreateNode(const char* cszNodeName);
	/**
	*@brief �õ��ڵ�ĳ���
	*@return ���س���
	*/
	int  GetPtrDocXmlLen(SPAPNodePtr nPtr);
	/**
	*@brief �õ��ڵ������
	*@param[out] pszBuf ���ؽڵ������
	*@param[in] nBufLength pszBufָ���ڴ�Ĵ�С
	*@return �ɹ�����TRUE��ʧ�ܷ���FALSE
	*/
	BOOL GetPtrDocXml(SPAPNodePtr nPtr,char* pszBuf,int nBufLength);
	/**
	*@brief �õ��ڵ���ַ���ֵ
	*@param[in] nodeFrom �ڵ��ָ��
	*@param[out] szText ���ؽڵ���ַ���ֵ
	*@param[int] nRecvBufLength szTextָ���ڴ�Ĵ�С
	*@param[out] nRecvedLen ʵ�ʽ��յ��ַ�������
	*@return �ɹ�����TRUE��ʧ�ܷ���FALSE
	*/
	BOOL GetText(SPAPNodePtr nodeFrom, IN OUT char * szText, const int& nRecvBufLength= -1);

	/**
	*@brief �õ��ڵ���ַ���ֵ
	*@param[in] nodeFrom �ڵ��ָ��
	*@param[out] szText ���ؽڵ���ַ���ֵ
	*@param[in] nRecvBufLength szTextָ���ڴ�Ĵ�С
	*@param[out] nRecvedLen ʵ�ʽ��յ��ַ�������
	*@return �ɹ�����TRUE��ʧ�ܷ���FALSE
	*/
	BOOL GetText(SPAPNodePtr nodeFrom, IN OUT char * szText,const int &nRecvBufLength, int& nRecvedLen);
	/**
	*@brief �õ��ڵ������ֵ
	*@param[in] nodeFrom �ڵ��ָ��
	*@param[out] thevalue ���ؽڵ������ֵ
	*@return �ɹ�����TRUE��ʧ�ܷ���FALSE
	*/
	BOOL GetText(SPAPNodePtr nodeFrom, OUT int& thevalue);
	/**
	*@brief �õ��ڵ�ĸ�����ֵ
	*@param[in] nodeFrom �ڵ��ָ��
	*@param[out] thevalue ���ؽڵ�ĸ�����ֵ
	*@return �ɹ�����TRUE��ʧ�ܷ���FALSE
	*/
	BOOL GetText(SPAPNodePtr nodeFrom, OUT double& thevalue);
	/**
	*@brief �õ��ڵ��ʱ����ֵ
	*@param[in] nodeFrom �ڵ��ָ��
	*@param[out] thevalue ���ؽڵ��ʱ����ֵ
	*@return �ɹ�����TRUE��ʧ�ܷ���FALSE
	*/
	BOOL GetText(SPAPNodePtr nodeFrom, OUT ScSystemTime& thevalue);

	/**
	*@brief ���ýڵ���ַ���ֵ
	*@param[in] nodeDest �ڵ��ָ��
	*@param[in] cszText �ַ���ֵ
	*@return �ɹ�����TRUE��ʧ�ܷ���FALSE
	*/
	BOOL SetText(SPAPNodePtr nodeDest, const char* cszText);	
	/**
	*@brief ���ýڵ������ֵ
	*@param[in] nodeDest �ڵ��ָ��
	*@param[in] thevalue ����ֵ
	*@return �ɹ�����TRUE��ʧ�ܷ���FALSE
	*/
	BOOL SetText(SPAPNodePtr nodeDest, int thevalue);	
	/**
	*@brief ���ýڵ�ĸ�����ֵ
	*@param[in] nodeDest �ڵ��ָ��
	*@param[in] thevalue ������ֵ
	*@return �ɹ�����TRUE��ʧ�ܷ���FALSE
	*/
	BOOL SetText(SPAPNodePtr nodeDest, double thevalue);
	/**
	*@brief ���ýڵ��ʱ����ֵ
	*@param[in] nodeDest �ڵ��ָ��
	*@param[in] thevalue ʱ����ֵ
	*@return �ɹ�����TRUE��ʧ�ܷ���FALSE
	*/
	BOOL SetText(SPAPNodePtr nodeDest, ScSystemTime thevalue);

	/**
	*@brief ���ýڵ���ַ�������
	*@param[in] nodeDest �ڵ��ָ��
	*@param[in] cszAttributeName ��������
	*@param[in] cszAttributeValue ����ֵ
	*@return �ɹ�����TRUE��ʧ�ܷ���FALSE
	*/
	BOOL SetAttribute(  SPAPNodePtr nodeDest,			
		const char* cszAttributeName,		
		const char* cszAttributeValue		
		); 
	/**
	*@brief ���ýڵ����������
	*@param[in] nodeDest �ڵ��ָ��
	*@param[in] cszAttributeName ��������
	*@param[in] nszAttributeValue ����ֵ
	*@return �ɹ�����TRUE��ʧ�ܷ���FALSE
	*/
	BOOL SetAttribute(	SPAPNodePtr nodeDest,			
		const char* cszAttributeName,		
		int nszAttributeValue);	
	/**
	*@brief ���ýڵ�ĸ���������
	*@param[in] nodeDest �ڵ��ָ��
	*@param[in] cszAttributeName ��������
	*@param[in] dszAttributeValue ����ֵ
	*@return �ɹ�����TRUE��ʧ�ܷ���FALSE
	*/
	BOOL SetAttribute(	SPAPNodePtr nodeDest,
		const char* cszAttributeName, 
		double dszAttributeValue);	
	/**
	*@brief ���ýڵ��ʱ��������
	*@param[in] nodeDest �ڵ��ָ��
	*@param[in] cszAttributeName ��������
	*@param[in] stAttributeValue ����ֵ
	*@return �ɹ�����TRUE��ʧ�ܷ���FALSE
	*/
	BOOL SetAttribute(	SPAPNodePtr nodeDest,
		const char* cszAttributeName, 
		ScSystemTime stAttributeValue);	

	/**
	*@brief �õ��ڵ���ַ�������ֵ
	*@param[in] nodeDest �ڵ��ָ��
	*@param[in] cszAttributeName ��������
	*@param[out] pszValue ��������ֵ
	*@param[in] nValueLen pszValueָ���ڴ�Ĵ�С
	*@return �ɹ�����TRUE��ʧ�ܷ���FALSE
	*/
	BOOL GetAttributeValue(  	SPAPNodePtr nodeDest,
		const char* cszAttributeName,
		char * pszValue,
		const int &nValueLen = -1); 

	/**
	*@brief �õ��ڵ���ַ�������ֵ
	*@param[in] nodeDest �ڵ��ָ��
	*@param[in] cszAttributeName ��������
	*@param[out] pszValue ��������ֵ
	*@param[in] nValueLen pszValueָ���ڴ�Ĵ�С,����Ϊ��ȡ�ĳ���
	*@param[out] nRecvedLen ʵ�ʽ��յ����ַ�������
	*@return �ɹ�����TRUE��ʧ�ܷ���FALSE
	*/
	BOOL GetAttributeValue(  	SPAPNodePtr nodeDest,
		const char* cszAttributeName,
		char * pszValue,
		const int &nValueLen,
		int& nRecvedLen
		); 


	/**
	*@brief �õ��ڵ����������ֵ
	*@param[in] nodeDest �ڵ��ָ��
	*@param[in] cszAttributeName ��������
	*@param[out] pnAttrValue ��������ֵ
	*@return �ɹ�����TRUE��ʧ�ܷ���FALSE
	*/
	BOOL GetAttributeValue(SPAPNodePtr nodeDest,
		const char* cszAttributeName, int &pnAttrValue);

	/**
	*@brief �õ��ڵ��ʱ��������ֵ
	*@param[in] nodeDest �ڵ��ָ��
	*@param[in] cszAttributeName ��������
	*@param[out] pnAttrValue ��������ֵ
	*@return �ɹ�����TRUE��ʧ�ܷ���FALSE
	*/
	BOOL GetAttributeValue(SPAPNodePtr nodeDest,
		const char* cszAttributeName, ScSystemTime& pnAttrValue);

	/**
	*@brief �õ��ڵ�ĸ���������ֵ
	*@param[in] nodeDest �ڵ��ָ��
	*@param[in] cszAttributeName ��������
	*@param[out] pnAttrValue ��������ֵ
	*@return �ɹ�����TRUE��ʧ�ܷ���FALSE
	*/
	BOOL GetAttributeValue(SPAPNodePtr nodeDest,
		const char* cszAttributeName, double &pnAttrValue);

	/**
	*@brief �õ��ڵ������
	*@param[in] nodeDest �ڵ��ָ��
	*@param[out] szName ���ؽڵ������
	*@param[in] nBufLength szNameָ���ڴ�Ĵ�С
	*@return �ɹ�����TRUE��ʧ�ܷ���FALSE
	*/
	BOOL GetName(SPAPNodePtr nodeDest, IN OUT LPTSTR szName,IN const int &nBufLength = -1);
	/**
	*@brief �õ��ڵ������
	*@param[in] nodeDest �ڵ��ָ��
	*@param[out] szName ���ؽڵ������
	*@param[in] nBufLength szNameָ���ڴ�Ĵ�С
	*@param[out] nRecvedLen ʵ�ʽ��յ��ַ�������
	*@return �ɹ�����TRUE��ʧ�ܷ���FALSE
	*/
	BOOL GetName(SPAPNodePtr nodeDest, IN OUT LPTSTR szName,IN const int &nBufLength,OUT int& nRecvedLen );
	/**
	*@brief ��ӽڵ�
	*@param[in] nodeParent ���ڵ�
	*@param[in] nodeChild Ҫ��ӵ��ӽڵ�
	*@return �ɹ�����TRUE��ʧ�ܷ���FALSE
	*/
	BOOL AppendNode(SPAPNodePtr nodeParent, SPAPNodePtr nodeChild);
	/**
	*@brief ��ӽڵ���
	*@param[in] nodeParent ���ڵ�
	*@param[in] nodeChild Ҫ��ӵ��ӽڵ���
	*@return �ɹ�����TRUE��ʧ�ܷ���FALSE
	*/
	BOOL AppendNodeTree(SPAPNodePtr nodeParent, SPAPNodePtr nodeChild);
	/**
	*@brief ��ӽڵ�
	*@param[in] nodeParent ���ڵ�
	*@param[in] cszNodeName Ҫ��ӵ��ӽڵ������
	*@param[in] cszAttrName1-cszAttrName5 Ҫ��ӵ��ӽڵ������
	*@param[in] cszAttrValue1-cszAttrValue5 Ҫ��ӵ��ӽڵ������ֵ
	*@return �ɹ���������ϵĽڵ��ָ�룬ʧ�ܷ���NULL
	*/
	SPAPNodePtr AppendNodeEx(SPAPNodePtr nodeParent, const char* cszNodeName,
		const char* cszAttrName1=NULL, const char* cszAttrValue1=NULL,
		const char* cszAttrName2=NULL, const char* cszAttrValue2=NULL,
		const char* cszAttrName3=NULL, const char* cszAttrValue3=NULL,
		const char* cszAttrName4=NULL, const char* cszAttrValue4=NULL,
		const char* cszAttrName5=NULL, const char* cszAttrValue5=NULL);

public:
	/**
	*@brief ���ظ��ڵ��ָ��
	*@return ���ظ��ڵ��ָ��
	*/
	SPAPNodePtr GetRootNode();
	/**
	*@brief �������ֲ��ҽڵ�
	*@param[in] nodeParent ���ڵ�
	*@param[in] cszDestNodeName Ҫ���ҵ��ӽڵ������
	*@return ���ҵ����ظýڵ��ָ�룬���򷵻�NULL
	*/
	SPAPNodePtr FindNode_ByName(SPAPNodePtr nodeParent, const char* cszDestNodeName);

	/**
	*@brief �������ֺ����Բ��ҽڵ�
	*@param[in] nodeParent ���ڵ�
	*@param[in] cszDestNodeName Ҫ���ҵ��ӽڵ������
	*@param[in] cszAttrName1-cszAttrName3 Ҫ���ҵ��ӽڵ������
	*@param[in] cszAttrValue1-cszAttrValue3 Ҫ���ҵ��ӽڵ������ֵ
	*@return ���ҵ����ظýڵ��ָ�룬���򷵻�NULL
	*/
	SPAPNodePtr FindNode_ByAttr( SPAPNodePtr nodeParent, const char* cszDestNodeName,
		const char* cszAttrName1, const char* cszAttrValue1,
		const char* cszAttrName2="", const char* cszAttrValue2="",
		const char* cszAttrName3="", const char* cszAttrValue3=""
		);

public:
	/**
	*@brief ɾ���ڵ�
	*@param[in] nodeParent ���ڵ�
	*@param[in] nodeRemoving Ҫɾ�����ӽڵ�
	*@return �ɹ�����TRUE��ʧ�ܷ���FALSE
	*/
	BOOL RemoveChild(SPAPNodePtr nodeParent, SPAPNodePtr nodeRemoving);

	/**
	*@brief �ж��Ƿ����ӽڵ�
	*@param[in] nodeDest Ҫ�жϵĽڵ�
	*@return ���ֽڵ㷵��TRUE�����򷵻�FALSE
	*/
	BOOL IsHasChilds(SPAPNodePtr nodeDest);
	/**
	*@brief ȡ���ӽڵ�ĸ���
	*@param[in] nodeDest �ڵ�
	*@return �����ӽڵ�ĸ���
	*/
	long GetChildCount(SPAPNodePtr nodeDest);
	/**
	*@brief ȡ�õ�һ���ӽڵ��ָ��
	*@param[in] nodeParent ���ڵ�
	*@return ���ص�һ���ӽڵ��ָ��
	*/
	SPAPNodePtr GetFirstChildNode(SPAPNodePtr nodeParent);
	/**
	*@brief ȡ��ǰһ���ֵܽڵ��ָ��
	*@param[in] nodeFrom �ڵ�
	*@return ����ǰһ���ֵܽڵ��ָ��
	*/
	SPAPNodePtr GetPrevSiblingNode(SPAPNodePtr nodeFrom);
	/**
	*@brief ȡ����һ���ֵܽڵ��ָ��
	*@param[in] nodeFrom �ڵ�
	*@return ������һ���ֵܽڵ��ָ��
	*/
	SPAPNodePtr GetNextSiblingNode(SPAPNodePtr nodeFrom);
	/**
	*@brief �жϽڵ��Ƿ���Ԫ��
	*@param[in] nodeDest �ڵ�
	*@return �Ƿ���TRUE�����Ƿ���FALSE
	*/
	BOOL IsDomElement(SPAPNodePtr nodeDest);	

	/**
	*@brief �滻�ڵ�         //�����⣬��Ҫʹ��
	*@param[in] nodeParent ���ڵ�
	*@param[in] nodeNewChild �½ڵ�
	*@param[in] nodeOldChild Ҫ�滻�Ľڵ�
	*@return �ɹ������滻����½ڵ��ָ�룬���򷵻�NULL
	*/
	SPAPNodePtr ReplaceChild(SPAPNodePtr nodeParent, SPAPNodePtr nodeNewChild, SPAPNodePtr nodeOldChild);


private:
	void* m_pSpapDocument;//
};

#endif //
