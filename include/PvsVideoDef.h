#ifndef __PVS_VIDEO_DEF_H__
#define __PVS_VIDEO_DEF_H__

#pragma pack(push)
#pragma pack(4)
#define CURRENT_CHL_SUM 16

struct VideoFrame
{
	enum FormatType
	{
		YV12 = 100, //4:2:0
		YUV420, // I420
		UYVY, // 4:2:2
		VYUY, // 4:2:2
		YUYV, // 4:2:2
		YVYU, // 4:2:2
		RGB24,
		RGB32,
		YUVUV, //UV����
		H264 ,//h264��׼��
		NVMM, // NVMM�ڴ�����
		Unknown = -1
	};

	VideoFrame()
	{
		width = 0;
		height = 0;
		data = NULL;
		py = NULL;
		pu = NULL;
		pv = NULL;
		vflip = FALSE;
		nCapture = 0;
	}

	int width; // ͼ���
	int height; // ͼ���
	FormatType type; // ͼ������
	unsigned long long timestamp; // ʱ���
	unsigned long size; // ���ݳ���

	/*RGB UYVY VYUY YUYV YVYU �������洢����*/
	unsigned char *data;
	int stride;
	BOOL vflip; // ͼ�������Ƿ��Ǵ�ֱ���õģ���һ�����ݴ洢�ڵ�һ��ΪFALSE��,����H264��������Ƿ�ΪI֡

	/*YV12 YUV420 ƽ��洢����*/
	unsigned char *py;
	unsigned char *pu;
	unsigned char *pv;
	int nCapture;
	int stride_y;
	int stride_uv;
};

#pragma pack(pop)

#endif //__PVS_VIDEO_DEF_H__
