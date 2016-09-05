#include <string>
#include "PlatformInterface.h"
using namespace std;

using namespace node;
template <typename T1, typename T2>
class CNodeManager
{
public:
	CNodeManager(IPlatformInterface* pPlugin, string sFilePath, string sNodeName, node::PVendorNode pNode)
	{m_pPlugin = pPlugin; m_sFilePath = sFilePath; m_sNodeName = sNodeName; m_pVendorNode = pNode; m_bDeviceModified = FALSE;};
	~CNodeManager(){};

public:

	BOOL LoadDevice();
	BOOL SaveDevice();

	// �豸�ڵ���(��ӣ��޸ģ�ɾ����
	//SaveXml�ò�������ѡ���Ƿ��޸ĵ����ݱ��浽xml��,����Ĭ�ϱ���
	BOOL DeviceChangedNotify(DeviceChanged* pdevc, BOOL SaveXml = TRUE);
	// ͬ���豸
	BOOL SynchDevice(long nOpCode, node::PBaseNode pOriginalNode/*ԭ�ڵ�����*/, node::PBaseNode pNode/*��ӻ��޸ĵ��豸��ʱ�ڵ�����*/);

private:
	string m_sFilePath; // �ļ�·��
	string m_sNodeName; // �ڵ�����
	node::PVendorNode m_pVendorNode; // ���ҽڵ����ݣ�ֻ��һ�� 
	BOOL m_bDeviceModified; // �豸�Ƿ��޸Ĺ�
	IPlatformInterface* m_pPlugin;
};

#include "xml_rw.h"

template <typename T1, typename T2>
BOOL CNodeManager<T1, T2>::LoadDevice()
{
	TCHAR szPath[MAX_PATH] = {0};
	_stprintf(szPath, _T("%svm%s.xml"), m_sFilePath.c_str(), m_sNodeName.c_str());

	CSProXml cfg;
	if (!cfg.LoadFromFile(szPath))
	{	
		m_bDeviceModified = TRUE;
		return FALSE;
	}

	BOOL fOk = TRUE; // ������Ϣ�Ƿ�����
	SPAPNodePtr RootNode = cfg.GetRootNode();
	SPAPNodePtr businessNode = cfg.FindNode_ByName(RootNode, CFG_BUSINESS_NODE);
	SPAPNodePtr vendorNode = cfg.FindNode_ByName(businessNode, m_sNodeName.c_str());

	if (vendorNode == NULL)
	{
		m_bDeviceModified = TRUE;
		m_pPlugin->OutputLog(_T("δ���ҵ����ҽڵ�"), WITH_ALL, LEV_ERROR);
		return FALSE;
	}

	// Get the vendor desc
	fOk &= cfg.GetAttributeValue(vendorNode, _T("desc"), m_pVendorNode->szName);


	// Read device nodes
	SPAPNodePtr deviceNode = cfg.GetFirstChildNode(vendorNode);
	for (; deviceNode != NULL; deviceNode = cfg.GetNextSiblingNode(deviceNode))
	{
		TCHAR name[256] = {0};
		cfg.GetName(deviceNode, name);
		if (_tcscmp(name, _T("device")) != 0)
			continue;

		T1 *pDev = new T1;
		m_pVendorNode->AddTail(pDev);
		pDev->pVendor = m_pVendorNode;

		fOk &= cfg.GetAttributeValue(deviceNode, _T("ip"), pDev->szIP);
		fOk &= cfg.GetAttributeValue(deviceNode, _T("desc"), pDev->szName);
		fOk &= cfg.GetAttributeValue(deviceNode, _T("port"), (int&)pDev->nPort);
		fOk &= cfg.GetAttributeValue(deviceNode, _T("user"), pDev->szUser);
		fOk &= cfg.GetAttributeValue(deviceNode, _T("pass"), pDev->szPwd);
		fOk &= cfg.GetAttributeValue(deviceNode, _T("expand"), pDev->szExpand);

		SPAPNodePtr camsNode = cfg.FindNode_ByName(deviceNode, _T("cams"));
		cfg.GetAttributeValue(camsNode, _T("sum"), (int&)pDev->chansum);

		// Read the cameras
		SPAPNodePtr camNode = cfg.GetFirstChildNode(camsNode);
		for (; camNode != NULL; camNode = cfg.GetNextSiblingNode(camNode))
		{	
			TCHAR name[MAX_NAME_LEN] = {0};
			cfg.GetName(camNode, name);
			if (_tcscmp(name, _T("cam")) != 0)
				continue;

			T2 *pCam = new T2;
			pDev->AddTail(pCam);
			pCam->pDevice = pDev;

			fOk &= cfg.GetAttributeValue(camNode, _T("gid"), pCam->szID);
			fOk &= cfg.GetAttributeValue(camNode, _T("gname"), pCam->szName);
			fOk &= cfg.GetAttributeValue(camNode, _T("channel"), pCam->szPlayContext);
		}
	}

	m_bDeviceModified = !fOk;
	return TRUE;
}

template <typename T1, typename T2>
BOOL CNodeManager<T1, T2>::SaveDevice()
{
	if (!m_bDeviceModified)
		return TRUE; // �豸δ�޸ģ�����Ҫ����

	TCHAR szPath[MAX_PATH];
	_stprintf(szPath, _T("%svm%s.xml"), m_sFilePath.c_str(), m_sNodeName.c_str());

	CSProXml cfg;

	cfg.SetOutputFile(szPath);

	SPAPNodePtr rootNode = cfg.GetRootNode();
	SPAPNodePtr businessNode = cfg.FindNode_ByName(rootNode, CFG_BUSINESS_NODE);
	SPAPNodePtr vendorNode = cfg.FindNode_ByName(businessNode, m_sNodeName.c_str());

	if (rootNode == NULL)
	{
		rootNode = cfg.CreateRootNode(CFG_ROOT_NODE);
		if (rootNode == NULL)
			return FALSE;
	}

	if (businessNode == NULL)
	{
		businessNode = cfg.CreateNode(CFG_BUSINESS_NODE);
		if (businessNode == NULL)
			return FALSE;

		if (!cfg.AppendNode(rootNode, businessNode))
			return FALSE;
	}

	if (vendorNode)
	{	
		cfg.SetAttribute(vendorNode, _T("desc"), m_pVendorNode->szName);

		// Ϊ�˱�֤���ҽڵ���������ļ��е�λ�ò���ı�
		// ֻɾ�����ҵ��ӽڵ�
		SPAPNodePtr pVendorChildNode = cfg.GetFirstChildNode(vendorNode);
		while (pVendorChildNode)
		{
			SPAPNodePtr pNextChildNode = cfg.GetNextSiblingNode(pVendorChildNode);
			TCHAR szNodeName[MAX_NAME_LEN] = {0};
			cfg.GetName(pVendorChildNode, szNodeName);
			if (0 == _tcscmp(szNodeName, _T("device")))
				cfg.RemoveChild(vendorNode, pVendorChildNode); // ֻɾ���豸�ڵ�

			pVendorChildNode = pNextChildNode;
		}
	}	
	else
	{
		vendorNode = cfg.CreateNode(m_sNodeName.c_str());
		cfg.AppendNode(businessNode, vendorNode);

		cfg.SetAttribute(vendorNode, _T("desc"), m_pVendorNode->szName);
	}

	T1 *pDevNode = (T1*)m_pVendorNode->GetChild();
	while (pDevNode != NULL)
	{
		SPAPNodePtr deviceNode = cfg.CreateNode(_T("device"));
		SPAPNodePtr camsNode = cfg.CreateNode(_T("cams"));
		cfg.AppendNode(vendorNode, deviceNode);
		cfg.AppendNode(deviceNode, camsNode);

		cfg.SetAttribute(deviceNode, _T("ip"), pDevNode->szIP);
		cfg.SetAttribute(deviceNode, _T("desc"), pDevNode->szName);
		cfg.SetAttribute(deviceNode, _T("port"), (int)pDevNode->nPort);
		cfg.SetAttribute(deviceNode, _T("user"), pDevNode->szUser);
		cfg.SetAttribute(deviceNode, _T("pass"), pDevNode->szPwd);
		cfg.SetAttribute(deviceNode, _T("expand"), pDevNode->szExpand);
		cfg.SetAttribute(camsNode, _T("sum"), pDevNode->chansum);

		T2 *pCamNode = (T2*)pDevNode->GetChild();
		while (pCamNode != NULL)
		{
			SPAPNodePtr camNode = cfg.CreateNode(_T("cam"));
			cfg.AppendNode(camsNode, camNode);

			cfg.SetAttribute(camNode, _T("gid"), pCamNode->szID);
			cfg.SetAttribute(camNode, _T("gname"), pCamNode->szName);
			cfg.SetAttribute(camNode, _T("channel"), pCamNode->szPlayContext);

			pCamNode = (T2*)pCamNode->Next();
		}

		pDevNode = (T1*)pDevNode->Next();
	}

	cfg.SaveToFile();

	return TRUE;
}

// �豸�ڵ���(��ӣ��޸ģ�ɾ����
template <typename T1, typename T2>
BOOL CNodeManager<T1, T2>::DeviceChangedNotify(DeviceChanged* pdevc, BOOL SaveXml)
{
	TCHAR szLog[MAX_LOG_LINE] = {0};

	if (!pdevc)
		return FALSE;

	DeviceChanged* pnextdev = pdevc;
	for (; pnextdev; pnextdev=pnextdev->next)
	{
		if (pnextdev->mode == PVS_DEVICE_ADD) // ���
		{
			if (!pnextdev->channels)
				continue; // ����豸����������һ��ͨ��


			T1* pDstDev = NULL;
			T1* pDev = new T1;

			pDev->pVendor = m_pVendorNode;

			_tcscpy(pDev->szIP, pnextdev->ip);
			pDev->nPort = pnextdev->port;
			_tcscpy(pDev->szName, pnextdev->name);
			_tcscpy(pDev->szUser, pnextdev->user);
			_tcscpy(pDev->szPwd, pnextdev->pass);
			_tcscpy(pDev->szExpand, pnextdev->szExpand);

			int sum = 0;
			T1* pTempDev =(T1*) m_pVendorNode->FindNode((BaseNode*)pDev);
			if (pTempDev!=NULL) {
				//���豸�Ѵ���
				pDstDev = pTempDev;
				delete pDev;
				pDev = NULL;
				sum = pTempDev->chansum;
			}
			else
			{
				//�豸������
				m_pVendorNode->AddTail(pDev);
				m_bDeviceModified = TRUE;
				pDstDev = pDev;
			}

			ChannelChanged* pcc = pnextdev->channels;
			while (pcc)
			{
				T2* pCam = new T2;
				_tcscpy(pCam->szPlayContext, pcc->szPlayContext);
				_tcscpy(pCam->szID, pcc->id);
				_tcscpy(pCam->szName, pcc->name);
				pCam->pDevice = pDstDev;
				if (pDstDev->FindNode((BaseNode*)pCam) == NULL) {
					pDstDev->AddTail(pCam);
					++sum;
					m_bDeviceModified = TRUE;
				}
				else
				{
					delete pCam;
				}
				pcc = pcc->next;

			}

			pDstDev->SetChannelSize(sum);
		}
		else if (pnextdev->mode == PVS_DEVICE_DELETE) // �豸ɾ��
		{
			T1* pDev = new T1;

			pDev->pVendor = m_pVendorNode;

			_tcscpy(pDev->szIP, pnextdev->ip);
			pDev->nPort = pnextdev->port;
			_tcscpy(pDev->szName, pnextdev->name);
			_tcscpy(pDev->szUser, pnextdev->user);
			_tcscpy(pDev->szPwd, pnextdev->pass);
			_tcscpy(pDev->szExpand, pnextdev->szExpand);

			T1* pTempDev =(T1*)m_pVendorNode->FindNode((BaseNode*)pDev);
			if (pTempDev!=NULL) {
				//���豸�Ѵ���
				pTempDev->Remove();
				pTempDev->DeleteAllChild();
			}
			
			if (NULL != pDev)
			{
				delete pDev;
				pDev = NULL;
			}
		}
		else if (pnextdev->mode == PVS_DEVICE_MODIFY) // �豸�޸�
		{
			T1* pDev = new T1;

			pDev->pVendor = m_pVendorNode;

			_tcscpy(pDev->szIP, pnextdev->ip);
			pDev->nPort = pnextdev->port;
			_tcscpy(pDev->szName, pnextdev->name);
			_tcscpy(pDev->szUser, pnextdev->user);
			_tcscpy(pDev->szPwd, pnextdev->pass);
			_tcscpy(pDev->szExpand, pnextdev->szExpand);

			T1* pTempDev =(T1*)m_pVendorNode->FindNode((BaseNode*)pDev);
			if (pTempDev!=NULL) {
				//���豸�Ѵ���
				_tcscpy(pTempDev->szIP, pDev->szIP);
				pTempDev->nPort = pDev->nPort;
				_tcscpy(pTempDev->szName, pDev->szName);
				_tcscpy(pTempDev->szUser, pDev->szUser);
				_tcscpy(pTempDev->szPwd, pDev->szPwd);
				_tcscpy(pTempDev->szExpand, pDev->szExpand);
				m_bDeviceModified = TRUE;
			}
			
			if (NULL != pDev)
			{
				delete pDev;
				pDev = NULL;
			}

		}
		else if (pnextdev->mode == PVS_CAMERA_DELETE || pnextdev->mode == PVS_CAMERA_MODIFY)  // ɾ��,�޸���ƵԴ
		{
			T1* pDstDev = NULL;
			T1* pDev = new T1;

			pDev->pVendor = m_pVendorNode;

			_tcscpy(pDev->szIP, pnextdev->ip);
			pDev->nPort = pnextdev->port;
			_tcscpy(pDev->szName, pnextdev->name);
			_tcscpy(pDev->szUser, pnextdev->user);
			_tcscpy(pDev->szPwd, pnextdev->pass);
			_tcscpy(pDev->szExpand, pnextdev->szExpand);

			int sum = 0;
			T1* pTempDev =(T1*) m_pVendorNode->FindNode((BaseNode*)pDev);
			if (pTempDev!=NULL) 
			{
				pDstDev = pTempDev;
				
				T2 *pCamNode = (T2*)pDstDev->GetChild();
				while (pCamNode != NULL)
				{
					ChannelChanged* pcc = pnextdev->channels;
					while (pcc)
					{
						if (_tcscmp(pcc->id, pCamNode->szID) == 0)
						{
							if (pnextdev->mode == PVS_CAMERA_DELETE)
							{
								// ���ڴ���ɾ��Ҫɾ������ƵԴ�ڵ�
								++sum;
								pCamNode->Remove();
								m_bDeviceModified = TRUE;
								pCamNode->DeleteAllChild();
							}
							else if (pnextdev->mode == PVS_CAMERA_MODIFY)
							{
								// �޸���ƵԴ�ڵ�
								if (0 != _tcscmp(pcc->szPlayContext, pCamNode->szPlayContext))
									_tcscpy(pCamNode->szPlayContext, pcc->szPlayContext);
								if (0 != _tcscmp(pcc->name, pCamNode->szName))
									_tcscpy(pCamNode->szName, pcc->name);
								m_bDeviceModified = TRUE;
							}
							break;
						}
						pcc = pcc->next;
					}

					pCamNode = (T2*)pCamNode->Next();
				}
			}


			if (NULL != pDev)
			{
				delete pDev;
				pDev = NULL;
			}

			pDstDev->SetChannelSize(pDstDev->chansum - sum);
		}
		else // ������ʱ��ʵ��
		{
			continue;
		}
	}
	if(SaveXml)//�Ƿ��޸ĵ����ݱ�����xml��
	SaveDevice();

	return TRUE;
}
// ͬ���豸
template <typename T1, typename T2>
BOOL CNodeManager<T1, T2>::SynchDevice(long nOpCode, node::PBaseNode pOriginalNode/*ԭ�ڵ�����*/, node::PBaseNode pNode/*��ӻ��޸ĵ��豸��ʱ�ڵ�����*/)
{
	BOOL result = FALSE;

	if (nOpCode == PVS_DEVICE_ADD)
	{
		if (pNode == NULL)
			return FALSE;

		if (!pNode->IsNodeType(VNT_DEVICE))
			return FALSE; // ֻ��������豸���ͽڵ�

		// �¼��豸
		PDeviceNode pAddNode = (PDeviceNode)pNode;
		T1* pDev = new T1;
		if (pDev == NULL)
		{
			m_pPlugin->OutputLog(_T("����豸ʧ��"), WITH_ALL, LEV_ERROR);
			return FALSE;
		}

		pDev->pVendor = m_pVendorNode;
		_tcscpy(pDev->szIP, pAddNode->szIP);
		_tcscpy(pDev->szName, pAddNode->szName);
		_tcscpy(pDev->szUser, pAddNode->szUser);
		_tcscpy(pDev->szPwd, pAddNode->szPwd);
		_tcscpy(pDev->szExpand, pAddNode->szExpand);
		pDev->nPort = pAddNode->nPort;

		int sum = 0;
		PCameraNode pAddCam = (PCameraNode)pAddNode->GetChild();
		while (pAddCam != NULL)
		{
			T2* pCam = new T2;
			if (pCam == NULL)
			{
				delete pDev;
				m_pPlugin->OutputLog(_T("������ʧ��"), WITH_ALL, LEV_ERROR);
				return FALSE;
			}

			pCam->pDevice = pDev;
			_tcscpy(pCam->szID, pAddCam->szID);
			_tcscpy(pCam->szName, pAddCam->szName);
			_stprintf(pCam->szPlayContext, "%d", sum);
			//pCam->nChanNo = sum;
			++sum;

			pDev->AddTail(pCam);
			pAddCam = (PCameraNode)pAddCam->Next();
		}
		// ͨ����
		pDev->SetChannelSize(sum);

		m_pVendorNode->AddTail(pDev);

		// ���µ�������
		//m_pTrdNotify->OnDeviceChanged(m_pVendorNode);

		result = TRUE;
	}
	else if (nOpCode == PVS_DEVICE_DELETE)
	{
		if (pOriginalNode == NULL)
			return FALSE;

		if (!pOriginalNode->IsNodeType(VNT_DEVICE))
			return FALSE; // ֻ����ɾ���豸���ͽڵ�

		delete pOriginalNode;
		// ���µ�������
		//m_pTrdNotify->OnDeviceChanged(m_pVendorNode);

		result = TRUE;
	}
	else if (nOpCode == PVS_DEVICE_MODIFY)
	{
		if (pOriginalNode == NULL || pNode == NULL)
			return FALSE;

		if (!(*pOriginalNode == pNode))
			return FALSE;

		// �޸�����
		if (pNode->szName[0] != '\0' && _tcscmp(pNode->szName, pOriginalNode->szName) != 0)
		{
			_tcscpy(pOriginalNode->szName, pNode->szName);
		}

		if (pOriginalNode->IsNodeType(VNT_DEVICE) && pNode->IsNodeType(VNT_DEVICE))
		{
			PDeviceNode pDevNode = (PDeviceNode)pOriginalNode;

			// �޸��û�
			if (_tcscmp((PDeviceNode(pNode))->szUser, pDevNode->szUser) != 0)
			{
				_tcscpy(pDevNode->szUser, (PDeviceNode(pNode))->szUser);
			}
			// �޸�����
			if (_tcscmp((PDeviceNode(pNode))->szPwd, pDevNode->szPwd) != 0)
			{
				_tcscpy(pDevNode->szPwd, (PDeviceNode(pNode))->szPwd);
			}
			// �޸Ķ˿�
			pDevNode->nPort = (PDeviceNode(pNode))->nPort;
		}

		result = TRUE;
	}

	if (result && !m_bDeviceModified)
		m_bDeviceModified = TRUE;

	return TRUE;
}

