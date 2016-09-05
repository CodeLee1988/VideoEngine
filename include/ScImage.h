/** @file ScImage.h
* ��ƽ̨ʵ��
* �����ṩ��scImage����Ӧ�������������������٣�ת�������Ƶ�  
* �漰��ת���Ľӿڣ���ı�DstImge��ͷ��Ϣ����������һ��Image�ظ�ʹ�õ������ÿ��ʹ��ǰ��Ҫ���¸�ֵ
* @warning ʹ�ñ��⣬�����ȵ��ó�ʼ������scImageLibInit()
* @see scImageLibInit() ScImageDraw.h  ScImagePlatForm.h 
*/

#ifndef SC_IMAGE_H
#define SC_IMAGE_H


#include "ScType.h"

#ifdef __cplusplus
extern "C" {
#endif /* __cplusplus */



//////////////////////////////////////////////////////////////////////////
//							���ʼ��������
//////////////////////////////////////////////////////////////////////////

/**
 @brief ��ʼ��image��,ʹ�øÿ�ǰ�����ȵ��ô˺��� (������ʽ���ɶ�ε��ã�
 @return ScErr
 @see ScImageLibUnInit() ScErr.h
 */
SC_EXTERN_C SC_EXPORTS ScErr SC_CDECL scImageLibInit();

/**
 @brief ����ʼ��image�⣬ϵͳ�˳�ʱ���á�(������ʽ���ɶ�ε��ã�Ҫ��ScImageLibInit�ɶ�ʹ�ã�
 @return ScErr
 @see ScImageLibInit() ScErr.h
 */
SC_EXTERN_C SC_EXPORTS ScErr SC_CDECL scImageLibUnInit();

/**
 @brief ��Image������ز���
 @param szKey��Э���ʶ
        ֵ1 IMAGE_WIDTHSTEP_ALIGN ͼ����뷽ʽ
 @param uiParam Ҫ���õ�ֵ��������ָ��ʹ�ã�
 @warning ��������ĳЩ���͵�ͼ���趨�ض��Ķ��뷽ʽʱ���˺��������ڴ���������ScImageCreate��֮ǰʹ�á�
 @return ScErr
 @see ScImageLibInit() ScImageLibUnInit() ScErr.h ScType.h
*/
SC_EXTERN_C SC_EXPORTS ScErr SC_CDECL scImageSetConfig(const char*szKey,unsigned int uiParam);


//��ĳЩ���͵�ͼ���趨�ض��Ķ��뷽ʽ�꡾�˺��������ڴ���������ScImageCreate��֮ǰʹ�á�,ͨ��
//Ĭ�϶��뷽ʽΪ4����
#define IMAGE_WIDTHSTEP_ALIGN "ImageWidthStepAlign"
//����ͼƬ�ڴ����ʹ�õ�����ڴ�
#define IMAGE_TOTAL_MEM_SIZE "ImageTotalMemSize"
//�����ڴ���ڴ�����
#define IMAGE_FREE_MEM_SIZE "ImageFreeMemSize"

//��ؽṹ�嶨��
typedef struct tag_imageStepAlignStruct
{
	ScImageType nType;  //ͼ������
	int nAlignValue;    //���뷽ʽ
}StepAlignStruct;//���뷽ʽ�ṹ��


/**
 @brief ��Image������ز���
 @param szKey��Э���ʶ
 @param uiParam Ҫ���õ�ֵ
 @param pData  ��õ�����ָ��
 @warning ���ڻ��ͼ�񲽳����뷽ʽ��uiParam �������ͼ�����ͣ�pDataΪ�������뷽ʽֵָ��
 @return ScErr
 @see ScImageLibInit() ScImageLibUnInit() ScErr.h ScType.h
*/
SC_EXTERN_C SC_EXPORTS ScErr SC_CDECL scImageGetData(const char*szKey,unsigned int uiParam,unsigned int* pData);

/**
 @brief ��Image������ز���
 @param szKey��Э���ʶ
 @param uiParam Ҫ���õ�ֵ
 @return ScErr
 @see ScImageLibInit() ScImageLibUnInit() ScErr.h ScType.h
*/

//�ӿڶ�Ӧ��ö��
typedef enum tagInterfaceKey
{
	IK_CONVERT = 0,
	IK_PASTE = 1,
	IK_COPY = 2,
	IK_INIT = 3,
	IK_UNINT = 4,
	IK_CREAT = 5,
	IK_DESTROY = 6,
	IK_DRAW_LINE = 7,
	IK_DRAW_CIRCLE = 8,
	IK_DRAW_RECT = 9,
	IK_DRAW_TEXT = 10,
	IK_DRAW_POLYLINE = 11,
	IK_CONVERTEX = 12,
	IK_CREATEFROM = 13,
	IK_CREATEFROMEX = 14
}InterfaceKey;

//��ʵ�ֵĻص�����
typedef ScErr (*InitPlatformSpecific)();
typedef ScErr (*PastePlatformspecific)(ScImage*pSrcImage,ScImage*pDstImage,ScRect rect);
typedef ScErr (*ConvertPlatFormSpecific)(ScImage*pSrcImage,ScImage*pDstImage,ScRect rect,int nDstType, int nDstWidth, int nDstHeight);
typedef ScErr (*ConvertPlatFormSpecificEx)(ScImage*pSrcImage,ScImage*pDstImage,ScRect rect,int nDstType, int nDstWidth, int nDstHeight,unsigned int UserData);
typedef ScErr (*CopyImagePlatformSpecific)(ScImage *pSrc, ScImage *pDst);
typedef ScErr (*ScDrawTextSpecific)(ScImage* pImage,ScPoint pt,const char* szText,int nSize,ScRGB col);
typedef ScErr (*ScCreateFromeFormSpecific)(ScImage*pSrcImage,ScImage**pDstImage,ScRect rect,ScImageType nDstType, int nDstWidth, int nDstHeight);
typedef ScErr (*ScCreateFromeFormExSpecific)(ScImage*pSrcImage,ScImage**pDstImage,ScRect rect,ScImageType nDstType, int nDstWidth, int nDstHeight,int UserData);

//ע��ص��Ľӿ� ������key Ҫע��Ļص���keyֵ��pInterface keyֵ��Ӧ���͵Ļص�����ָ��
/*��Ӧ��ʽ��
key       |       �ص�����                |    ����ֵ
IK_CONVERT       ConvertPlatFormSpecific           ScErr
IK_PASTE         PastePlatformspecific             ScErr
IK_COPY          CopyImagePlatformSpecific         ScErr
IK_INIT          InitPlatformSpecific              ScErr

IK_DRAW_TEXT     ScDrawTextSpecific				 ScErr
IK_CREATEFROM	 ScCreateFromeFormSpecific		 ScErr
������ʱԤ��
*/

/**
 @brief �ص�����ע��ӿ�
 @param key ע��ص���Key ö��InterfaceKey����
 @param pInterface �ص�ָ��
 @return ScErr
 @see ScImageLibInit() ScImageLibUnInit() ScErr.h ScType.h InterfaceKey 
      InitPlatformSpecific 
	  PastePlatformspecific 
	  ConvertPlatFormSpecific
      ConvertPlatFormSpecificEx 
	  CopyImagePlatformSpecific
	  ScDrawTextSpecific
	  ScCreateFromeFormSpecific
	  ScCreateFromeFormExSpecific
*/
SC_EXTERN_C SC_EXPORTS ScErr SC_CDECL scImageRegPlatformSpecificItf(InterfaceKey key,void *pInterface);



//////////////////////////////////////////////////////////////////////////
//					ͼ����
//////////////////////////////////////////////////////////////////////////


/**
 @brief ����image���� 
 @param nType image���� ���ScImageType
 @param nWidth ���
 @param nHeight �߶�
 @param uiParam ���Ӳ�����ĳЩ���Ϳ��ܻ���һЩ����Ĳ�����Ŀǰjpeg������Ҫͨ���ò����������ݵĴ�С��imagesize���������������С�������ڴ�
 @return ScImage����ScType.h)��ָ��
 @see ScImageLibInit() ScImageLibUnInit() ScType.h
 */
SC_EXTERN_C SC_EXPORTS ScImage* SC_CDECL scImageCreate(ScImageType nType,int nWidth,int nHeight,unsigned int uiParam);

/**
 @brief ��ScImageCreate�÷���ͬ,�˽ӿ�ֵ����Imageͷ�������ڴ棬�ڴ��ɵ����߷��䲢�ӵ����ص�Imageͷ��
 @param nType image���� ���ScImageType
 @param nWidth ���
 @param nHeight �߶�
 @param uiParam ���Ӳ�����ĳЩ���Ϳ��ܻ���һЩ����Ĳ�����Ŀǰjpeg������Ҫͨ���ò����������ݵĴ�С��imagesize���������������С�������ڴ�
 @return ScImage����ScType.h)��ָ��
 @see ScImageLibInit() ScImageLibUnInit() ScType.h ScImageCreate()
*/
SC_EXTERN_C SC_EXPORTS ScImage* SC_CDECL scImageCreateHeader(ScImageType nType,int nWidth,int nHeight,unsigned int uiParam);

/**
 @brief ����ͼ��
 @param pImage ����ScImage����ScType.h)��ָ���ָ��
 @return ScErr
 @see ScImageLibInit() ScImageLibUnInit() ScErr.h ScType.h ScImageCreate()
*/
SC_EXTERN_C SC_EXPORTS ScErr SC_CDECL scImageDestroy(ScImage** pImage);

/**
 @brief ����ͼ��ͷ
 @param pImage ����ScImage����ScType.h)��ָ���ָ��
 @return ScErr
 @see ScImageLibInit() ScImageLibUnInit() ScErr.h ScType.h ScImageCreateHeader()
*/
SC_EXTERN_C SC_EXPORTS ScErr SC_CDECL scImageDestroyHeader(ScImage** pImage);

/**
 @brief ����Դ���ݺ�Ŀ�����ʹ���Image��ͼ�����Ͳ�һ�»���ת���Ĳ���
 @param pSrcImage ����ScImage����ScType.h)��ָ�룬ԭͼ
 @param pDstImage ��OUT������ScImage����ScType.h)��ָ���ָ�룬Ŀ��ͼ
 @param rect ����ScRect(��ScType.h),ԭʼͼ�ϵ�һ��������Ϊ��ͼ�ķ�Χ
 @param nDstType image���� ���ScImageType����ScType.h) nDstTypeĿ����������
 @param nDstWidth Ŀ��ͼ�Ŀ��
 @param nDstHeight Ŀ��ͼ�ĸ߶�
 @warning ��Դͼ����ΪIT_JPEGʱ������nDstWidth��nDstHeight��Ч���������Ŷ���
 @warning ����IT_RGB �� IT_JPEGʱ������ rect nDstWidth nDstHeight ��Ч��������ͼ�����Ź���
 @return ScErr
 @see ScImageLibInit() ScImageLibUnInit() ScErr.h ScType.h ScImageConvert()
*/  
SC_EXTERN_C SC_EXPORTS ScErr SC_CDECL scImageCreateFrom(ScImage*pSrcImage,ScImage**pDstImage,ScRect rect,
							ScImageType nDstType, int nDstWidth, int nDstHeight);
/**
 @brief ����Դ���ݺ�Ŀ�����ʹ���Image��ͼ�����Ͳ�һ�»���ת���Ĳ���
 @param pSrcImage ����ScImage����ScType.h)��ָ�룬ԭͼ
 @param pDstImage ��OUT������ScImage����ScType.h)��ָ���ָ�룬Ŀ��ͼ
 @param rect ����ScRect(��ScType.h),ԭʼͼ�ϵ�һ�����򣬿�ͼ�ķ�Χ
 @param nDstType image���� ���ScImageType����ScType.h) ��Ŀ����������
 @param nDstWidth Ŀ��ͼ�Ŀ��
 @param nDstHeight Ŀ��ͼ�ĸ߶�
 @param UserData �ӿڵ�Ŀ�����ڽ�RGBͼ��ת����jpegͼ�� ����UserData����ѹ������ ��Χ�ǣ�1,100��
 @warning ��Դͼ����ΪIT_JPEGʱ������nDstWidth��nDstHeight��Ч���������Ŷ���
 @warning ����IT_RGB �� IT_JPEGʱ������ rect nDstWidth nDstHeight ��Ч��������ͼ�����Ź���
 @return ScErr
 @see ScImageLibInit() ScImageLibUnInit() ScErr.h ScType.h ScImageCreateFrom()
*/

SC_EXTERN_C SC_EXPORTS ScErr SC_CDECL scImageCreateFromEx(ScImage*pSrcImage,ScImage**pDstImage,ScRect rect,
								ScImageType nDstType, int nDstWidth, int nDstHeight,unsigned int UserData);


/**
 @brief ͼ�񿽱�
 @param pSrc ����ScImage����ScType.h)��ָ�룬ԭͼ
 @param pDst ����ScImage����ScType.h)��ָ�룬Ŀ��ͼ
 @warning ���ô˺���ǰ��������Ҫ��֤pSrc��pDst���Ѿ������˺��ʵ��ڴ档
 @return ScErr
 @see ScImageLibInit() ScImageLibUnInit() ScErr.h ScType.h
*/
SC_EXTERN_C SC_EXPORTS ScErr SC_CDECL scImageCopy(ScImage *pSrc, ScImage *pDst);



//////////////////////////////////////////////////////////////////////////
//							ͼ�񼸺��α�
//////////////////////////////////////////////////////////////////////////

/**
 @brief ��ͼƬpSrcImage����ͼƬpDstImage�ϣ� rectΪ����ͼƬpDstImage�ϵ�λ�ã����rect��pSrcImage�Ĵ�С��һ�£�����pSrcImage�������ź�����ͼ��
 @param pSrcImage ����ScImage����ScType.h)��ָ�룬ԭͼ
 @param pDstImage ����ScImage����ScType.h)��ָ�룬Ŀ��ͼ
 @param rect ����ScRect(��ScType.h),Ŀ��ͼ�ϵ�λ��
 @return ScErr
 @see ScImageLibInit() ScImageLibUnInit() ScErr.h ScType.h
*/
SC_EXTERN_C SC_EXPORTS ScErr SC_CDECL scImagePaste(ScImage*pSrcImage,ScImage*pDstImage,ScRect rect);

/**
 @brief ʵ��ͼ���ת��������ͼ��Ŀ�ȡ����С���н��������ֳ�3����
 @param pSrcImage ����ScImage����ScType.h)��ָ�룬ԭͼ
 @param pDstImage ����ScImage����ScType.h)��ָ�룬Ŀ��ͼ
 @param rect ����ScRect(��ScType.h),��ͼ�ķ�Χ
 @param nDstType image���� ���ScImageType����ScType.h) nDstTypeĿ����������
 @param nDstWidth Ŀ�Ľṹ��Ŀ��
 @param nDstHeight Ŀ�Ľṹ��ĸ߶�
 @warning ���ڴ˽ӿ�ֻ֧�ְ�������С����n : 1)��
 @warning ���ô˺���ǰ��������Ҫ��֤pSrcImage��pDstImage���Ѿ������˺��ʵ��ڴ档
 @return ScErr
 @see ScImageLibInit() ScImageLibUnInit() ScErr.h ScType.h
*/



//////////////////////////////////////////////////////////////////////////
//							ͼ�����ͱ任
//////////////////////////////////////////////////////////////////////////

SC_EXTERN_C SC_EXPORTS ScErr SC_CDECL scImageConvert(ScImage*pSrcImage,ScImage*pDstImage,ScRect rect,ScImageType nDstType, int nDstWidth, /*ͼ���� */ int nDstHeight /*ͼ��߶� */);

/**
 @brief ��չת����������ScImageConvert����һ�£���������һ��uiParam����������һЩ�������������ת��ʱ�������������
 @param pSrcImage ����ScImage����ScType.h)��ָ�룬ԭͼ
 @param pDstImage ����ScImage����ScType.h)��ָ�룬Ŀ��ͼ
 @param rect ����ScRect(��ScType.h),��ͼ�ķ�Χ
 @param nDstType image���� ���ScImageType����ScType.h) nDstTypeĿ����������
 @param nDstWidth Ŀ�Ľṹ��Ŀ��
 @param nDstHeight Ŀ�Ľṹ��ĸ߶�
 @param uiParam ��ʹ�ô˽ӿڽ���jpegѹ��ʱ��nDstType����ΪIT_JPEG������ѹ����
 @warning ���ڴ˽ӿ�ֻ֧�ְ�������С����n : 1)��
 @warning ���ô˺���ǰ��������Ҫ��֤pSrcImage��pDstImage���Ѿ������˺��ʵ��ڴ档
 @return ScErr
 @see ScImageLibInit() ScImageLibUnInit() ScErr.h ScType.h ScImageConvert()
*/
SC_EXTERN_C SC_EXPORTS ScErr SC_CDECL scImageConvertEx(ScImage*pSrcImage,ScImage*pDstImage,ScRect rect,ScImageType nDstType, int nDstWidth,int nDstHeight,unsigned int uiParam);




//////////////////////////////////////////////////////////////////////////
//								�ļ���д���
//////////////////////////////////////////////////////////////////////////

/**
 @brief �洢ͼƬ������ ���������洢BMPͼ��Jpegͼ
 @param pImage �洢��ͼƬ����Դ
 @param szFileName��Ҫ�洢���ļ�·��
 @param dwParam ���Ӳ��� ���洢���ļ���׺��Ϊ.jpg/.jpegʱ��dwParamָ��ѹ���ȣ�0~100��
 @return ScErr
 @see ScImageLibInit() ScImageLibUnInit() ScErr.h ScType.h
*/
SC_EXTERN_C SC_EXPORTS ScErr SC_CDECL scImageSave(ScImage *pImage, const char *szFileName, DWORD dwParam);

/**
 @brief �ӱ���Loadһ��ͼƬ
 @param pImage �����洢��ͼƬ���ݵ�ָ��
 @param szFileName ��ȡ���ļ�·��
 @return ScErr
 @see ScImageLibInit() ScImageLibUnInit() ScErr.h ScType.h
*/
SC_EXTERN_C SC_EXPORTS ScErr SC_CDECL scImageLoad(ScImage **pImage,const char *szFileName);

/**
 @brief �ӱ���Loadһ��ͼƬ,ָ�����ͼ��ĸ�ʽ
 @param pImage �����洢��ͼƬ���ݵ�ָ��
 @param szFileName ��ȡ���ļ�·��
 @param type ���ͼ���Ŀ���ʽ
 @return ScErr
 @see ScImageLibInit() ScImageLibUnInit() ScErr.h ScType.h
*/
SC_EXTERN_C SC_EXPORTS ScErr SC_CDECL scImageLoadEx(ScImage **pImage,const char *szFileName,ScImageType nDstType);

//////////////////////////////////////////////////////////////////////////
//						�ɰ溯�����°汾������Ӧ��(����ָ���滻�ɰ汾����)
//////////////////////////////////////////////////////////////////////////

/*

		�ɰ汾					�°汾
		ScImageLibInit 			scImageLibInit
		ScImageLibUnInit		scImageLibUnInit
		ScImageSetConfig		scImageSetConfig
		ScImageGetData			scImageGetData
		
		ScImageCreate			scImageCreate
		ScImageCreateHeader		scImageCreateHeader
		ScImageDestroy			scImageDestroy
		ScImageDestroyHeader	scImageDestroyHeader
		ScImageCreateFrom		scImageCreateFrom
		ScImageCreateFromEx		scImageCreateFromEx
		scCopyImage				scImageCopy
		scInitYImage			scImageCreateGray
		
		scPasteImage			scImagePaste
		scCropImage				scImageCrop
		scResize				scImageResize
		scCropResize			scImageCropResize
		
		ScImageConvert			scImageConvert
		ScImageConvertEx		scImageConvertEx
		
		
		ScImageSave				scImageSave
		ScImageLoad				scImageLoad


*/



#ifdef __cplusplus
}
#endif /* __cplusplus */

#endif
