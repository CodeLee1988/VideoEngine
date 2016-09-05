#pragma once

#include "cv.h"
#include "cxcore.h"

void DrawCalibrationResult(Bitmap *m_pCurrFrameBitmap, 
	float PanAngle/*ˮƽ�ǣ��ȣ�*/, 
	float d/*�߶ȣ��ף�*/, 
	float f/*���ࣨ���ף�*/, 
	float TiltAngle/*�����ǣ��ȣ�*/, 
	float people_height/*С���ĸ߶ȣ��ף�*/, 
	float fCCDWidth/*CCD��ȣ����ף�*/, 
	float fCCDHeight/*CCD�߶ȣ����ף�*/,
	BOOL bShowVerticalLine/*�Ƿ���ʾ��ֱ����*/
	);

void DrawCalibrationBox(Bitmap *pBitmap, 
	float PanAngle/*ˮƽ�ǣ��ȣ�*/, 
	float d/*�߶ȣ��ף�*/, 
	float f/*���ࣨ���ף�*/, 
	float TiltAngle/*�����ǣ��ȣ�*/, 
	float fCCDWidth/*CCD��ȣ����ף�*/, 
	float fCCDHeight/*CCD�߶ȣ����ף�*/, 
	float xBottomMid/*���ӵ�ǰ���±ߵ������ĵ�x�������[0-1]*/, 
	float yBottomMid/*���ӵ�ǰ���±ߵ������ĵ�y�������[0-1]*/, 
	float wx/*���ӳ����ף�*/, 
	float wy/*���ӿ��ף�*/, 
	float wz/*���Ӹߣ��ף�*/
	);