#ifndef BASICTYPEDEF_H
#define BASICTYPEDEF_H

#ifdef _LINUX
#include "linuxdef.h"
#else
#include <tchar.h>
#endif
#include "PvsDef.h"

#define CHANNEL_COUNT 16

// string length
#define MAX_IP_LEN   64
#define MAX_URL_LEN  128
#define MAX_NAME_LEN 256
#define MAX_DESC_LEN 1024
#define MAX_LOG_LINE 512 // ��־�г���

// node
namespace node{
// �ڵ�����
enum NodeType
{
	VNT_ROOT = 0, // ���ڵ����ͣ�ȫ��������ֻ�������һ�����ڵ�
	VNT_GROUP, // ����ڵ����ͣ���ڵ�ֻ���ǳ��ҽڵ��µ��ӽڵ�����ӽڵ���ӽڵ��
	VNT_VENDOR, // ���ҽڵ����ͣ����ҽڵ�ĸ��ڵ�����Ǹ��ڵ�
	VNT_DEVICE, // �豸�ڵ����ͣ� Ҳ����˵��ƽ̨�ڵ㣬ֻ��һ����ͳ��˵��
	VNT_CAMERA //  ����ڵ㣬���ǿ��Բ��ŵĽڵ㣬Ҳ������Ľڵ㣬û���ӽڵ�
};
typedef struct PlayTypeCount
{
	volatile LONG nH264PlayCount;//H264�㲥�Ĵ���
	volatile LONG nRollDataCount;//RollData�㲥�Ĵ���
	volatile LONG nNvmmDataCount;//Nvmm�Ĳ��ż�����Ϊ���ò��֪���Ƿ����ϴ�NVMM����
}PlayCount;
// �豸��Ϣ����
class BaseNode
{
private:
	NodeType _nt; // �ýڵ����ͣ����븳ֵ
	BaseNode* pParent; // ָ���丸�ڵ㣬ֻ�и��ڵ��Ϊ�գ����ڵ���ǰ��ڵ�
	BaseNode* pChild; // ָ�����һ���ӽڵ�
	BaseNode* pNext; // ָ��ͬ������һ���ڵ�
	int nCamera; // ͳ�������ӽڵ���������
public:
	LPVOID hNode; // ��ʾ�ýڵ��������������������ڵ�ľ�������������ô�
	TCHAR szName[MAX_NAME_LEN]; // �ýڵ�����

	BaseNode(NodeType nt)
		:_nt(nt)
	{
		this->hNode = NULL;
		this->pParent = NULL;
		this->pChild = NULL;
		this->pNext = NULL;
		_tcscpy(this->szName, _T("δ����"));
		this->nCamera = 0;
	}
	virtual ~BaseNode()
	{
		// �Ӹ��ڵ����Ƴ���
		this->Remove();

		// ɾ���������ӽڵ�
		this->DeleteAllChild();

		this->pNext = NULL;
	}

	// �жϽڵ�����
	inline BOOL IsNodeType(NodeType nt) const
	{
		if (this->_nt == nt)
			return TRUE;
		return FALSE;
	}
	// �����ӽڵ�
	BaseNode* FindNode(const BaseNode* const pNode) const
	{
		if (pNode == NULL || this->pChild == NULL)
			return NULL;

		// ��ѯ
		BaseNode* pFindNode = NULL;
		BaseNode* pChildNode = this->pChild;

#if 1   // �����ѯ��
		do
		{
			if (*pChildNode == pNode)
			{
				pFindNode = pChildNode;
				break;
			}

			pChildNode = pChildNode->pNext;
		}while (pChildNode != NULL);

		if (pFindNode == NULL)
		{	
			// ��ǰ��û�в��ҵ�ָ���ڵ�����
			// ����������һ��
			pChildNode = this->pChild;
			do
			{
				pFindNode = pChildNode->FindNode(pNode);
				if (pFindNode != NULL)
				{
					break;
				}

				pChildNode = pChildNode->pNext;
			}while (pChildNode != NULL);
		}
#else   // �����ѯ��
		do
		{
			if (*pChildNode == pNode)
			{
				pFindNode = pChildNode;
				break;
			}

			pFindNode = pChildNode->FindNode(pNode);
			if (pFindNode != NULL)
			{	
				break;
			}

			pChildNode = pChildNode->pNext;
		}while (pChildNode != NULL);
#endif

		return pFindNode;
	}
	inline BaseNode* GetParent() const
	{
		return this->pParent;
	}
	// Get the first child node
	inline BaseNode* GetChild() const
	{
		return this->pChild;
	}
	// Get the next node
	inline BaseNode* Next() const
	{
		return this->pNext;
	}
	// ��ȡ�ýڵ��µ������������
	inline int GetCameraCount() const
	{
		return this->nCamera;
	}
	// ����ӽڵ㵽ĩβ
	void AddTail(BaseNode* pNode)
	{
		if (pNode == NULL)
			return;

		pNode->pParent = this;
		pNode->pNext = NULL;

		// ͳ���������
		int nAdd = 0; // ��ӵ��������
		if (pNode->IsNodeType(VNT_CAMERA))
		{
			nAdd = 1;
		}
		else
		{
			nAdd = pNode->nCamera;
		}
		// �ۼƵ�ǰ�ڵ��µ����
		this->nCamera += nAdd;
		// �ۼ����и��ڵ�����
		BaseNode* pParentNode = this->pParent;
		while (pParentNode)
		{
			pParentNode->nCamera += nAdd;
			pParentNode = pParentNode->pParent;
		}

		if (this->pChild == NULL)
		{
			// ��ǰ��ӵ��ӽڵ�Ϊ��һ���ӽڵ�
			this->pChild = pNode;
		}
		else
		{
			// ʹ��ǰ��ĩβ�ڵ�ָ�����һ�ڵ�Ϊ����ӵĽڵ�
			BaseNode* pChildNode = this->pChild;
			while (pChildNode->pNext != NULL)
			{
				pChildNode = pChildNode->pNext;
			}

			pChildNode->pNext = pNode;
		}
	}
	// ���ָ���ڵ��µ������ӽڵ㵽�ýڵ����ӽڵ�ĩβ
	// ����ָ���Ľڵ��µ��ӽڵ�ĸ��ڵ�ָ��ýڵ�
	void AddChildsToTail(BaseNode* pParent)
	{
		if (pParent == NULL || pParent->pChild == NULL)
			return;

		BaseNode* pChildAdd = pParent->pChild;
		if (this->pChild == NULL)
		{
			// ��ǰ��ӵ��ӽڵ�Ϊ��һ���ӽڵ�
			this->pChild = pChildAdd;
		}
		else
		{
			// ʹ��ǰ��ĩβ�ڵ�ָ�����һ�ڵ�Ϊ����ӵĽڵ�
			BaseNode* pChildNode = this->pChild;
			while (pChildNode->pNext != NULL)
			{
				pChildNode = pChildNode->pNext;
			}

			pChildNode->pNext = pChildAdd;
		}

		// �ۼƵ�ǰ�ڵ��µ����
		this->nCamera += pParent->nCamera;
		// �ۼ����и��ڵ�����
		BaseNode* pParentNode = this->pParent;
		while (pParentNode)
		{
			pParentNode->nCamera += pParent->nCamera;
			pParentNode = pParentNode->pParent;
		}

		// �Ӹ��ڵ��жϿ�
		pParent->RemoveAllChild();

		// �����ڵ�ָ��ýڵ�
		do 
		{
			pChildAdd->pParent = this;
			pChildAdd = pChildAdd->pNext;
		} while (pChildAdd);
	}
	// �Ӹ��ڵ����Ƴ��ýڵ㣬���ͷ���Դ
	void Remove()
	{
		// ��ǰһ���ڵ�ָ��ýڵ����һ���ڵ�
		if (!this->pParent) // ���ڵ�
			return;

		// ��ѯ�ýڵ��ǰһ���ڵ�
		BaseNode* pPrevNode = NULL;
		BaseNode* pNextNode = this->pParent->pChild;
		while (pNextNode != NULL)
		{
			if (pNextNode == this)
				break;

			pPrevNode = pNextNode;
			pNextNode = pPrevNode->pNext;
		}
        //assert(pNextNode); // pNextNode Can't be NULL

		// ʹ�ýڵ��ǰһ�ڵ�ָ����һ�ڵ�
		if (pPrevNode == NULL)
		{
			// �ýڵ��ǵ�ǰ���ĵ�һ���ڵ�
			this->pParent->pChild = this->pNext;
		}
		else
		{
			// �ýڵ��ǵ�ǰ�����м�������Ľڵ�
			pPrevNode->pNext = this->pNext;
		}

		// �������и��ڵ�����
		BaseNode* pParentNode = this->pParent;
		while (pParentNode)
		{
			pParentNode->nCamera -= this->nCamera;
			if (pParentNode->nCamera < 0)
				pParentNode->nCamera = 0;
			pParentNode = pParentNode->pParent;
		}

		this->pParent = NULL;
	}
	// �Ƴ������ӽڵ㣬�����ͷ��ӽڵ���Դ�������Ҫ�ͷ���ʹ��DeleteAllChild
	void RemoveAllChild()
	{
		if (this->pChild)
		{
			// �������и��ڵ�����
			BaseNode* pParentNode = this->pParent;
			while (pParentNode)
			{
				pParentNode->nCamera -= this->nCamera;
				if (pParentNode->nCamera < 0)
					pParentNode->nCamera = 0;
				pParentNode = pParentNode->pParent;
			}
			this->nCamera = 0;

			this->pChild = NULL;
		}
	}
	// ɾ�������ӽڵ㣬�ͷŽڵ���Դ
	void DeleteAllChild()
	{
		if (this->pChild != NULL)
		{
			// �������и��ڵ�����
			BaseNode* pParentNode = this->pParent;
			while (pParentNode)
			{
				pParentNode->nCamera -= this->nCamera;
				if (pParentNode->nCamera < 0)
					pParentNode->nCamera = 0;
				pParentNode = pParentNode->pParent;
			}
			this->nCamera = 0;

			BaseNode* pCurrChild = this->pChild;
			BaseNode* pNextChild;
			while (1)
			{
				pNextChild =  pCurrChild->pNext;
				delete pCurrChild;
				if (pNextChild == NULL)
					break;
				pCurrChild = pNextChild;
				pNextChild = pCurrChild->pNext;
			}

			this->pChild = NULL;
		}
	}

	virtual bool operator == (const BaseNode* const pNode) const = 0;
};
typedef BaseNode* PBaseNode;

// ���ڵ�
class RootNode : public BaseNode
{
public:
	RootNode()
		:BaseNode(VNT_ROOT)
	{
	}

	inline bool operator == (const BaseNode* const pNode) const
	{
		return ((this == pNode) ? true:false);
	}
};
typedef RootNode* PRootNode;

// ����ڵ�
class GroupNode : public BaseNode
{
public:
	TCHAR szID[MAX_NAME_LEN]; // �����ID 

	GroupNode()
		:BaseNode(VNT_GROUP)
	{
		this->szID[0] = _T('\0');
	}

	inline bool operator == (const BaseNode* const pNode) const
	{
		return ((this == pNode) ? true:false);
	}
};
typedef GroupNode* PGroupNode;

// ���ҽڵ�
class VendorNode : public BaseNode
{
public:
	LPVOID hVendor; // ���Ҷ��󣬲���Ϊ��
	TCHAR szID[MAX_NAME_LEN]; // ����Ψһ��ʶ�������޸�

	VendorNode()
		:BaseNode(VNT_VENDOR)
	{
		this->hVendor = NULL;
		this->szID[0] = _T('\0');
	}

	inline bool operator == (const BaseNode* const pNode) const
	{
		if (pNode == this)
			return true;

		if (pNode == NULL || !pNode->IsNodeType(VNT_VENDOR))
			return false;

		const VendorNode* const pVenNode = (VendorNode*)pNode;
		if (pVenNode->hVendor == this->hVendor 
			|| _tcscmp(pVenNode->szID, this->szID) == 0)
			return true;

		return false;
	}
};
typedef VendorNode* PVendorNode;

// �豸�ڵ�
class DeviceNode : public BaseNode
{
public:
	PVendorNode pVendor; // ָ����豸�����ĳ��ң�����Ϊ��
	TCHAR szIP[MAX_IP_LEN]; // ���豸��IP
	TCHAR szUser[MAX_NAME_LEN]; // �û�
	TCHAR szPwd[MAX_NAME_LEN]; // ����
	TCHAR szExpand[2048]; // ��չ�ֶ�
	LONG  nPort; // �˿�
	LONG  nPlayingCamera; // ���豸�����ڲ��ŵ����������
	int chansum;	// ͨ������(0,1,4,8,16)

	DeviceNode()
		:BaseNode(VNT_DEVICE)
	{
		this->pVendor = NULL;
		this->szIP[0] = _T('\0');
		this->szUser[0] = _T('\0');
		this->szPwd[0] = _T('\0');
		this->szExpand[0] = _T('\0');
		this->nPort = 0;
		this->nPlayingCamera = 0;
	}

	inline bool operator == (const BaseNode* const pNode) const
	{
		if (pNode == this)
			return true;

		if (pNode == NULL || !pNode->IsNodeType(VNT_DEVICE))
			return false;

		const DeviceNode* const pDevNode = (DeviceNode*)pNode;
		if (_tcscmp(pDevNode->szIP, this->szIP) == 0)
			return true;

		return false;
	}
	
	void SetChannelSize(int nCount)
	{
		if (nCount < 0)
			return;

		this->chansum = nCount;
	}
};
typedef DeviceNode* PDeviceNode;



// ����ڵ�
class CameraNode : public BaseNode
{
public:
	PDeviceNode pDevice; // ָ�������������豸������Ϊ��
	void* pvPlayUser; // ���Ÿ�������û�����
	BOOL bPlaying; // ͨ������״̬
	TCHAR szID[MAX_NAME_LEN]; // �����ID 
	TCHAR szPlayContext[MAX_NAME_LEN]; // ���Ų���
	HPVSPLAY hPlayHandle;

	// �㷨����
	void* pEngine;
	void *pInvadeDetectParam;
	void *pAlgOutInfo;
	void *pIDVoilateData;
	void *pAlgAnalysisParam;
	BOOL bAnalyzing;

	CameraNode()
		:BaseNode(VNT_CAMERA)
	{
		this->pDevice = NULL;
		this->pvPlayUser = 0;
		this->bPlaying = FALSE;
		this->szID[0] = _T('\0');
		hPlayHandle = NULL;

		pEngine = NULL;
		pIDVoilateData = NULL;
		pInvadeDetectParam = NULL;
		pAlgAnalysisParam = NULL;
		pAlgOutInfo = NULL;
		bAnalyzing = FALSE;
	}

	inline bool operator == (const BaseNode* const pNode) const
	{
		if (pNode == this)
			return true;

		if (pNode == NULL || !pNode->IsNodeType(VNT_CAMERA))
			return false;

		const CameraNode* const pCamNode = (CameraNode*)pNode;
		if (_tcscmp(pCamNode->szID, this->szID) == 0)
			return true;

		return false;
	}
	// ͳһ��CPlatformVideoService���������
	inline void StartPlay(void* pvPlayUser = 0)
	{
		// ���ڸ�����������ųɹ�֮����ܵ��øú���
		this->pvPlayUser = pvPlayUser;
		this->bPlaying = TRUE;
		this->pDevice->nPlayingCamera++;
	}
	// ͳһ��CPlatformVideoService���������
	inline void StopPlay()
	{
		// ���ڸ�������ڲ���״̬���ܵ��øú���
		if (this->bPlaying)
		{
			this->pvPlayUser = 0;
			this->bPlaying = FALSE;
			this->pDevice->nPlayingCamera--;
			if (this->pDevice->nPlayingCamera < 0)
				this->pDevice->nPlayingCamera = 0;
		}
	}
};
typedef CameraNode* PCameraNode;

}; // end of node name space

// Config
#define  CFG_FILE_NAME        _T("config.xml")
#define  CFG_ROOT_NODE        _T("root")
#define  CFG_BUSINESS_NODE    _T("business")
#define  CFG_PVS_NODE         _T("pvs")

#endif // BASICTYPEDEF_H
