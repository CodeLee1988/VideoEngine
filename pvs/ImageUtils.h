#pragma once

//////////////////////////////////////////////////////////////////////////
// RGB -> RGB
BOOL  Convert_RGB32_To_RGB24_Resize(
							 void* pSrcBuffer,
							 int nSrcWidth,
							 int nSrcHeight, 
							 void* pDesBuffer, 
							 int nDstWidth, 
							 int nDstHeight
							 );

BOOL Convert_RGB24_RESIZE(
						void* pSrcBuffer,
						int nSrcWidth,
						int nSrcHeight, 
						void* pDesBuffer, 
						int nDesWidth, 
						int nDesHeight,
						BOOL vflip = FALSE // �Ƿ�ֱ��ת
						);

//////////////////////////////////////////////////////////////////////////
// YUV -> RGB
//////////////////////////////////////////////////////////////////////////
// YUV420 - RGB24
// �ı�ߴ����
BOOL Convert_YUV420_To_RGB24_Resize(int nSrcWidth,
							 int nSrcHeight, 
							 void *py, 
							 void *pu, 
							 void *pv, 
							 void *pDstBuf, 
							 int nDstWidth, 
							 int nDstHeight);
// ��ԭ�ߴ����
BOOL Convert_YUV420_To_RGB24(int nSrcWidth,
							 int nSrcHeight, 
							 void *py, 
							 void *pu, 
							 void *pv, 
							 void *pDstBuf);

//////////////////////////////////////////////////////////////////////////
// UYVY - RGB24
// �ı�ߴ����
BOOL Convert_UYVY_To_RGB24_Resize(int nSrcWidth,
								  int nSrcHeight, 
								  void *pSrc, 
								  void *pDst, 
								  int nDstWidth, 
								  int nDstHeight);

// ��ԭ�ߴ����
BOOL Convert_UYVY_To_RGB24(int nSrcWidth,
								  int nSrcHeight, 
								  void *pSrc, 
								  void *pDst);

//////////////////////////////////////////////////////////////////////////
// VYUY - RGB24
// �ı�ߴ����
BOOL Convert_VYUY_To_RGB24_Resize(int nSrcWidth,
	int nSrcHeight, 
	void *pSrc, 
	void *pDst, 
	int nDstWidth, 
	int nDstHeight);

// ��ԭ�ߴ����
BOOL Convert_VYUY_To_RGB24(int nSrcWidth,
	int nSrcHeight, 
	void *pSrc, 
	void *pDst);

//////////////////////////////////////////////////////////////////////////
// YUYV - RGB24
// �ı�ߴ����
BOOL Convert_YUYV_To_RGB24_Resize(int nSrcWidth,
	int nSrcHeight, 
	void *pSrc, 
	void *pDst, 
	int nDstWidth, 
	int nDstHeight);

// ��ԭ�ߴ����
BOOL Convert_YUYV_To_RGB24(int nSrcWidth,
	int nSrcHeight, 
	void *pSrc, 
	void *pDst);

//////////////////////////////////////////////////////////////////////////
// YVYU - RGB24
// �ı�ߴ����
BOOL Convert_YVYU_To_RGB24_Resize(int nSrcWidth,
	int nSrcHeight, 
	void *pSrc, 
	void *pDst, 
	int nDstWidth, 
	int nDstHeight);

// ��ԭ�ߴ����
BOOL Convert_YVYU_To_RGB24(int nSrcWidth,
	int nSrcHeight, 
	void *pSrc, 
	void *pDst);

//////////////////////////////////////////////////////////////////////////


void Convert_YUYV_TO_YUV420(
		void* pYUYV,
		void* pYUV420,
		int nWidth,
		int nHeight
		);

// ��24λλͼ�洢���ļ�
BOOL SaveRGBImg(const char* lpszFileName, void* pImgData, int nWidth, int nHeight);

// ��24λλͼת��JPGͼƬ���浽�ļ�
// nQuality(0-100)ѹ����
// vFlip 0-���ϵ��½���ѹ����1-���µ��Ͻ���ѹ��
BOOL SaveRGB24ToJpeg(const char* lpszFileName, void* pImgData, int nWidth, int nHeight, int nQuality=80, int vFlip=0);
