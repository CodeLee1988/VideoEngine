#include "stdafx.h"
#include "SecurityContentTransformer.h"
// #include "iconv.h"
#include "Base64.h"

//// ����ת��
//int code_convert(char *from_charset,char *to_charset,char *inbuf,int inlen,char *outbuf,int outlen)
//{
//	iconv_t cd;
//	char **pin = &inbuf;
//	char **pout = &outbuf;
//
//	cd = iconv_open(to_charset,from_charset);
//	if (cd == (iconv_t)-1)
//		return -1;
//
//	memset(outbuf,0,outlen);
//	size_t i = iconv(cd,pin,(size_t*)&inlen,pout,(size_t*)&outlen); 
//	iconv_close(cd);
//	if (i == -1)
//		return -1;
//	return 0;
//}
//// UTF-8��תΪGBK��
//int u2g(char *inbuf,int inlen,char *outbuf,int outlen)
//{
//	return code_convert("utf-8","GBK",inbuf,inlen,outbuf,outlen);
//}
////GBK��תΪUTF-8��
//int g2u(char *inbuf,size_t inlen,char *outbuf,size_t outlen)
//{
//	return code_convert("GBK","utf-8",inbuf,inlen,outbuf,outlen);
//}



// �����б�
int SceneListSetContent(CSProXml* pDoc, SPAPNodePtr cxParent, const SceneList* pContent)
{
	if (pDoc == NULL || cxParent == NULL || pContent == NULL)
		return 0;

	// �����б���
	SPAPNodePtr cxSceneList = pDoc->CreateNode("scenelist");
	pDoc->AppendNode(cxParent, cxSceneList);

	SceneList::const_iterator itrScene = pContent->begin();
	for (; itrScene != pContent->end(); ++itrScene)
	{
		SPAPNodePtr cxScene = pDoc->CreateNode("scene");
		pDoc->AppendNode(cxSceneList, cxScene);
		pDoc->SetAttribute(cxScene, "id", itrScene->sID.c_str());

		//char szUTF8Name[256], szGBKName[256];
		//memset(szUTF8Name, 0, 256);
		//memset(szGBKName, 0, 256);
		//strcpy(szGBKName, itrScene->sSceneName.c_str());
		//g2u(szGBKName, 256, szUTF8Name, 256);
		//pDoc->SetAttribute(cxScene, "scenename", szUTF8Name);

		pDoc->SetAttribute(cxScene, "scenename", itrScene->sSceneName.c_str());

		pDoc->SetAttribute(cxScene, "camid", itrScene->sCameraID.c_str());
		pDoc->SetAttribute(cxScene, "preset", itrScene->nPreset);

		// �궨��Ϣ
		SPAPNodePtr cxCalib = pDoc->CreateNode("calib");
		pDoc->AppendNode(cxScene, cxCalib);
		pDoc->SetAttribute(cxCalib, "ccdwidth", itrScene->calibration.fCCDWidth);
		pDoc->SetAttribute(cxCalib, "ccdheight", itrScene->calibration.fCCDHeight);
		pDoc->SetAttribute(cxCalib, "panangle", itrScene->calibration.fPanAngle);
		pDoc->SetAttribute(cxCalib, "tiltangle", itrScene->calibration.fTiltAngle);
		pDoc->SetAttribute(cxCalib, "camheight", itrScene->calibration.fCameraHeight);
		pDoc->SetAttribute(cxCalib, "focallen", itrScene->calibration.fFocalLength);

		// �����б�
		SPAPNodePtr cxROIList = pDoc->CreateNode("roilist");
		pDoc->AppendNode(cxScene, cxROIList);

		ROIList::const_iterator itrROI = itrScene->lsROIs.begin();
		for (; itrROI != itrScene->lsROIs.end(); ++itrROI)
		{
			SPAPNodePtr cxROI = pDoc->CreateNode("roi");
			pDoc->AppendNode(cxROIList, cxROI);
			pDoc->SetAttribute(cxROI, "type", itrROI->nROIType);

			SPAPNodePtr cxPoints = pDoc->CreateNode("points");
			pDoc->AppendNode(cxROI, cxPoints);

			ScPointFList::const_iterator itrPoint = itrROI->lsPoints.begin();
			for (; itrPoint != itrROI->lsPoints.end(); ++itrPoint)
			{
				SPAPNodePtr cxPoint = pDoc->CreateNode("point");
				pDoc->AppendNode(cxPoints, cxPoint);

				char x[64] = {0};
				char y[64] = {0};
				sprintf(x, "%f", itrPoint->x);
				sprintf(y, "%f", itrPoint->y);
				pDoc->SetAttribute(cxPoint, "x", x);
				pDoc->SetAttribute(cxPoint, "y", y);
			}
		}
#if 0
		// ���������б�
		SPAPNodePtr cxLinkageList = pDoc->CreateNode("linkagelist");
		pDoc->AppendNode(cxScene, cxLinkageList);
		StringList::const_iterator itrLinkage = itrScene->lsLinkageScene.begin();
		for (; itrLinkage != itrScene->lsLinkageScene.end(); ++itrLinkage)
		{
			SPAPNodePtr cxLinkage = pDoc->CreateNode("linkage");
			pDoc->AppendNode(cxLinkageList, cxLinkage);
			pDoc->SetAttribute(cxLinkage, "sceneid", itrLinkage->c_str());
		}
#endif
		// �㷨����
		SPAPNodePtr cxAlgoType = pDoc->CreateNode("algotype");
		pDoc->AppendNode(cxScene, cxAlgoType);
		pDoc->SetText(cxAlgoType, itrScene->nAlgoType);

		// �Ƿ�¼��
		SPAPNodePtr cxIsRecord = pDoc->CreateNode("isrecord");
		pDoc->AppendNode(cxScene, cxIsRecord);
		if (itrScene->bIsRecord)
			pDoc->SetText(cxIsRecord, 1);
		else
			pDoc->SetText(cxIsRecord, 0);

		// �㷨�����б�
		SPAPNodePtr cxAlgoParamList = pDoc->CreateNode("algoparamlist");
		pDoc->AppendNode(cxScene, cxAlgoParamList);
		//pDoc->SetText(cxAlgoParamList, itrScene->sAlgoParamlist.c_str());
		/*CSProXml docAlgo;
		if (docAlgo.LoadFromXML(itrScene->sAlgoParamlist.c_str()))
		{
			pDoc->AppendNode(cxAlgoParamList, docAlgo.GetRootNode());
		}*/
		CString strAlgoParamList = itrScene->sAlgoParamlist.c_str();
		////////////////////////////////////////////////////////////////////////////
		////����cdata����algoparam
		//strAlgoParamList.Replace("<?xml version=\"1.0\" encoding=\"GBK\"?>", "");
		//pDoc->SetCDATASectionData(cxAlgoParamList, strAlgoParamList);
		////////////////////////////////////////////////////////////////////////////

		//////////////////////////////////////////////////////////////////////////
		//base64���� ����algoparam
		int nLens = strAlgoParamList.GetLength();
		if (nLens!=0)
		{
			char *pAlgoEncBuf = new char[nLens*2];
			Base64Encode(pAlgoEncBuf, strAlgoParamList.GetBuffer(), nLens);
			pDoc->SetText(cxAlgoParamList, pAlgoEncBuf);
			delete[] pAlgoEncBuf;
		}

		//////////////////////////////////////////////////////////////////////////

		// ͼƬ
		SPAPNodePtr cxPic = pDoc->CreateNode("pic");
		pDoc->AppendNode(cxScene, cxPic);
		pDoc->SetAttribute(cxPic, "path", itrScene->sPic.c_str());

		// ��ǩ
		SPAPNodePtr cxTag = pDoc->CreateNode("tag");
		pDoc->AppendNode(cxScene, cxTag);
		pDoc->SetText(cxTag, itrScene->sTag.c_str());

		//�����Ƿ�����
		SPAPNodePtr cxIsRun = pDoc->CreateNode("isrun");
		pDoc->AppendNode(cxScene, cxIsRun);
		pDoc->SetText(cxIsRun, itrScene->bIsRun);

		// ������Ŵ�
		SPAPNodePtr cxPlayCamStr = pDoc->CreateNode("playcamstr");
		pDoc->AppendNode(cxScene, cxPlayCamStr);
		pDoc->SetText(cxPlayCamStr, itrScene->sPlayCamStr.c_str());
	}

	return 1;
}

int SceneListGetContent(CSProXml* pDoc, SPAPNodePtr cxParent, SceneList* pContent)
{
	if (pDoc == NULL || cxParent == NULL || pContent == NULL)
		return 0;

	// �����б���
	SPAPNodePtr cxSceneList = pDoc->FindNode_ByName(cxParent, "scenelist");
	if (cxSceneList == NULL)
		return 0;

	char szValue[512] = {0};
	SPAPNodeListPtr cxSceneNodeList = pDoc->FindNodes_ByName(cxSceneList, "scene");
	SPAPNodePtr cxScene = cxSceneNodeList->nextNode();
	for (; cxScene; cxScene = cxSceneNodeList->nextNode())
	{
		Scene scene;
		if (pDoc->GetAttributeValue(cxScene, "id", szValue))
			scene.sID = szValue;

		//char szUTF8Name[256], szGBKName[256];
		//memset(szUTF8Name, 0, 256);
		//memset(szGBKName, 0, 256);
		//if (pDoc->GetAttributeValue(cxScene, "scenename", szUTF8Name))
		//{
		//	u2g(szUTF8Name, 256, szGBKName, 256);
		//	scene.sSceneName = szGBKName;
		//}
		if (pDoc->GetAttributeValue(cxScene, "scenename", szValue))
		{
			scene.sSceneName = szValue;
		}

		if (pDoc->GetAttributeValue(cxScene, "camid", szValue))
			scene.sCameraID = szValue;

		pDoc->GetAttributeValue(cxScene, "preset", scene.nPreset);

		// �궨��Ϣ
		SPAPNodePtr cxCalib = pDoc->FindNode_ByName(cxScene, "calib");
		pDoc->GetAttributeValue(cxCalib, "ccdwidth", scene.calibration.fCCDWidth);
		pDoc->GetAttributeValue(cxCalib, "ccdheight", scene.calibration.fCCDHeight);
		pDoc->GetAttributeValue(cxCalib, "panangle", scene.calibration.fPanAngle);
		pDoc->GetAttributeValue(cxCalib, "tiltangle", scene.calibration.fTiltAngle);
		pDoc->GetAttributeValue(cxCalib, "camheight", scene.calibration.fCameraHeight);
		pDoc->GetAttributeValue(cxCalib, "focallen", scene.calibration.fFocalLength);

		// �����б�
		SPAPNodePtr cxROIList = pDoc->FindNode_ByName(cxScene, "roilist");
		SPAPNodeListPtr cxROINodeList = pDoc->FindNodes_ByName(cxROIList, "roi");
		SPAPNodePtr cxROI = cxROINodeList->nextNode();
		for (; cxROI; cxROI = cxROINodeList->nextNode())
		{
			ROI roi;
			pDoc->GetAttributeValue(cxROI, "type", (int&)roi.nROIType);

			SPAPNodePtr cxPoints = pDoc->FindNode_ByName(cxROI, "points");
			SPAPNodeListPtr cxPointNodeList = pDoc->FindNodes_ByName(cxPoints, "point");
			SPAPNodePtr cxPoint = cxPointNodeList->nextNode();
			for (; cxPoint; cxPoint = cxPointNodeList->nextNode())
			{
				ScPointF pointf;
				pDoc->GetAttributeValue(cxPoint, "x", pointf.x);
				pDoc->GetAttributeValue(cxPoint, "y", pointf.y);
				roi.lsPoints.push_back(pointf);
			}

			scene.lsROIs.push_back(roi);
		}
#if 0
		// ���������б�
		SPAPNodePtr cxLinkageList = pDoc->FindNode_ByName(cxScene, "linkagelist");
		SPAPNodeListPtr cxLinkageNodeList = pDoc->FindNodes_ByName(cxLinkageList, "linkage");
		SPAPNodePtr cxLinkage = cxLinkageNodeList->nextNode();
		for (; cxLinkage; cxLinkage = cxLinkageNodeList->nextNode())
		{
			if (pDoc->GetAttributeValue(cxLinkage, "sceneid", szValue))
				scene.lsLinkageScene.push_back(szValue);
		}
#endif
		// �㷨����
		SPAPNodePtr cxAlgoType = pDoc->FindNode_ByName(cxScene, "algotype");
		pDoc->GetText(cxAlgoType, scene.nAlgoType);

		// �Ƿ�¼��
		SPAPNodePtr cxIsRecord = pDoc->FindNode_ByName(cxScene, "isrecord");
		pDoc->GetText(cxIsRecord, scene.bIsRecord);

		// �㷨�����б�
		////////////////////////////////////////////////////////////////////////////
		////���� cdata����
		//SPAPNodePtr cxAlgoParamList = pDoc->FindNode_ByName(cxScene, "algoparamlist");
		////if (pDoc->GetText(cxAlgoParamList, szValue))
		//	//scene.sAlgoParamlist = szValue;
		//SPAPNodePtr cxAlgoParam = pDoc->GetFirstChildNode(cxAlgoParamList);
		//if (cxAlgoParam)
		//{
		//	scene.sAlgoParamlist = "<?xml version=\"1.0\" encoding=\"GBK\"?>";
		//	scene.sAlgoParamlist += (LPCTSTR)pDoc->GetCDATASectionData(cxAlgoParam);
		//}
		////////////////////////////////////////////////////////////////////////////

		//////////////////////////////////////////////////////////////////////////
		//����base64���� 
		char* pAlgoParamBuf = new char[1024*1024];
		char* pAlgoDecBuf = new char[1024*1024];
		SPAPNodePtr cxAlgoParamList = pDoc->FindNode_ByName(cxScene, "algoparamlist");
		if (pDoc->GetText(cxAlgoParamList, pAlgoParamBuf))
		{
			Base64Decode(pAlgoDecBuf,pAlgoParamBuf , strlen(pAlgoParamBuf));
			scene.sAlgoParamlist = pAlgoDecBuf;
		}
		//AfxMessageBox(pAlgoParamBuf);
		//AfxMessageBox(scene.sAlgoParamlist.c_str());
		delete[] pAlgoDecBuf;
		delete[] pAlgoParamBuf;
		//////////////////////////////////////////////////////////////////////////

		// ͼƬ
		SPAPNodePtr cxPic = pDoc->FindNode_ByName(cxScene, "pic");
		if (pDoc->GetAttributeValue(cxPic, "path", szValue))
			scene.sPic = szValue;

		// ��ǩ
		SPAPNodePtr cxTag = pDoc->FindNode_ByName(cxScene, "tag");
		if (pDoc->GetText(cxTag, szValue))
			scene.sTag = szValue;

		//�����Ƿ�����
		SPAPNodePtr cxIsRun = pDoc->FindNode_ByName(cxScene, "isrun");
		pDoc->GetText(cxIsRun, scene.bIsRun);

		// ������Ŵ�
		SPAPNodePtr cxPlayCamStr = pDoc->FindNode_ByName(cxScene, "playcamstr");
		if (pDoc->GetText(cxPlayCamStr, szValue))
			scene.sPlayCamStr = szValue;

		pContent->push_back(scene);
	}

	return 1;
}
