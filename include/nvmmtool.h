/*
 * nvmmbuf.h
 *
 *  Created on: 2015��6��15��
 *      Author: luyongzhe
 */

#ifndef NVMMTOOL_H_
#define NVMMTOOL_H_

#include "vpk_common.h"
//#include "decode.h"

#ifdef __cplusplus
extern "C" {
#endif



typedef void * NvMMGstSampleHandle;
typedef void * NvMMBufferHandle;
typedef void * NvMMNV12toI420BufferHandle;
typedef void * NvMMStructBufferHandle;
typedef void * NvMMSurfaceHandle;

typedef struct _SNvMMInfo
{
//	NvMMGstSampleHandle hNVGstSample;
	NvMMBufferHandle hNVMMBuffer;
	unsigned char *pData[3];  // Y, U , V
	unsigned int nDataMapsize[3];
	unsigned int nPitch[3];
	unsigned int nWidth[3];
	unsigned int nHeight[3];
} NvMMInfo;

typedef NvMMInfo * NvMMHandle;

#define NVMMSIZE 304
typedef void * HDECODER;

/*
 *
 *
 *
 *
 *
  */

typedef struct _Rect
{
	unsigned int left;
	unsigned int top;
	unsigned int right;
	unsigned int bottom;
} Rect;

/*
	���ܣ�����ת����������NV12��ʽ��I420��ʽBUFFER
	������
	width  			�������ݿ��
	height       	�������ݸ߶�
	����ֵ  NvMM��ʽ���������ӳ�䣬���ţ�����
*/
VPKAPI(NvMMNV12toI420BufferHandle) NV12toI420_Buffer_Create(unsigned int width, unsigned int height);


/*
	���ܣ���ȡת����������NV12��ʽ��I420��ʽBUFFERʵ��Ӳ�����
	������
	hNVMMNV12toI420Buffer  			NV12toI420_Buffer_Create�������
	����ֵ  Ӳ�����������ӳ�䣬���ţ�����
*/
VPKAPI(NvMMBufferHandle) NV12toI420_Get_NvMM_Handle(NvMMNV12toI420BufferHandle hNVMMNV12toI420Buffer);


/*
	���ܣ�����ת����������NV12��ʽ��I420��ʽBUFFER
	������
	hNVMMNV12toI420Buffer  			NV12toI420_Buffer_Create�������
	����ֵ  
*/
VPKAPI(int) NV12toI420_Buffer_Destroy(NvMMNV12toI420BufferHandle hNVMMNV12toI420Buffer);

/*
	���ܣ�ת����������NV12��ʽ��I420��ʽ
	������
	hDecoder  				������
	hNVGstSample       	����ص�����pFrame
	����ֵ  NvMM��ʽ���������ӳ�䣬���ţ�����
*/
VPKAPI(NvMMBufferHandle)  ConvertNV12toI420(NvMMNV12toI420BufferHandle hNVMMNV12toI420Buffer, NvMMGstSampleHandle hNVGstSample);

/*
	�����ӿڣ���ʹ��
  */
VPKAPI(NvMMBufferHandle) Jpeg_Get_NvMM_Handle(NvMMGstSampleHandle hNVGstSample);



/*
	���ܣ�ӳ��NVMM�ڴ�
	������
	hNvMMBufferHandle  ��Ϣ�ص�����
	pUser         �ص������Ĵ�����
	����ֵ  0��ʾ�ɹ� ������ʾʧ��
  */
VPKAPI(NvMMHandle)   MapNvmmYuv(NvMMBufferHandle  hNvMMBufferHandle);

/*
	���ܣ���ӳ��NVMM�ڴ�
	������
	hNvMMBufferHandle  ��Ϣ�ص�����
	pUser         �ص������Ĵ�����
	����ֵ  0��ʾ�ɹ� ������ʾʧ��
*/
VPKAPI(int)   UnMapNvmmYuv(NvMMHandle  hNvMMHandle);

/*
	���ܣ�ͬ��NVMM�ڴ�
	������
	hNvMMBufferHandle  ��Ϣ�ص�����
	pUser         �ص������Ĵ�����
	����ֵ  0��ʾ�ɹ� ������ʾʧ��
*/
VPKAPI(int)   SyncNvmmYuv(NvMMHandle hNvMMHandle);

/*
	���ܣ��ͷŽ�����������
	������

	hNVGstSample       	����ص�����pFrame
	����ֵ  
 */
VPKAPI(int) ReleaseGstSample(NvMMGstSampleHandle hNVGstSample);

/*
���ܣ�����NVMM��ʽ����BUFFER
	������
	width  			�������ݿ��
	height       	�������ݸ߶�
	����ֵ  NvMM��ʽ���������ӳ�䣬���ţ�����
*/
VPKAPI(NvMMStructBufferHandle) Nvmm_Struct_Buffer_Create(unsigned int width, unsigned int height);

/*
	���ܣ���ȡ����NVMM��ʽ����BUFFERӲ�����
	������
	hNVMMStructBuffer Nvmm_Struct_Buffer_Create�������
	����ֵ  NvMM��ʽ���������ӳ�䣬���ţ�����
 */
VPKAPI(NvMMBufferHandle) Struct_Buffer_Get_NvMM_Handle(NvMMStructBufferHandle hNVMMStructBuffer);

/*
	���ܣ�����NVMM��ʽ����BUFFERӲ�����
	������
	hNVMMStructBuffer Nvmm_Struct_Buffer_Create�������
	����ֵ  NvMM��ʽ���������ӳ�䣬���ţ�����
 */
VPKAPI(int) Nvmm_Struct_Buffer_Destroy(NvMMStructBufferHandle hNVMMStructBuffer);

/*
	���ܣ�NVMMBUFER���ţ���ͼ�ӿ�
	������
	hDstNVMMStructBuffer  		Ŀ��NVMM��ʽ����BUFFER
	hSrcNVMMBuffer       		Դnvmm����
	hRect						��ͼͼ����������
	����ֵ  
*/
VPKAPI(NvMMBufferHandle) Nvmm_Struct_Buffer_Convert(NvMMStructBufferHandle  hDstNVMMStructBuffer, NvMMBufferHandle hSrcNVMMBuffer, Rect * hRect );



#ifdef __cplusplus
}
#endif


#endif /* NVMMBUF_H_ */
