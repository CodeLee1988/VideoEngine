#pragma once

#include <vector>

typedef std::vector<POINTF> PointVector;

enum ShapeType
{
	stNone = -1,
	stSWLine = 0, //one way line
	stTWLine = 1, //two way line
	stPolygonOut = 2, //�ڵ���
	stPolygonIn		//�⵽��
};

struct Figure
{
	ShapeType type;
	int nLineWidth;
	COLORREF crLineColor;
	PointVector points;

	Figure()
	{
		type = stNone;
		nLineWidth = 1;
		crLineColor = 0x000000;
	}
};
typedef std::vector<Figure> FigureVector;

// Figure attribute changed flags
#define FAC_LINE_WIDTH  1
#define FAC_LINE_COLOR  2

#define FROMRGB(c,r,g,b) \
	b = (BYTE)(((COLORREF)c&0x00ff0000)>>16); \
	g = (BYTE)(((COLORREF)c&0x0000ff00)>>8); \
	r = (BYTE)((COLORREF)c&0x000000ff);

// CDrawCtrl �ؼ�

class IDrawNotify
{
public:
	virtual void OnFigureUpdate(FigureVector *pFigureList) = 0;
};

class CDrawCtrl : public CStatic
{
	DECLARE_DYNAMIC(CDrawCtrl)

public:
	CDrawCtrl(CWnd* pParent = NULL);   // ��׼���캯��
	virtual ~CDrawCtrl();

public:
	void SetBackgroundPicture(Gdiplus::Bitmap* pImage);
	void SetBackgroundPicture(const char* lpszImagePathName, const char* type);
	void SetDrawingParam(int nLineWidth, COLORREF crFigure, COLORREF crDrawing);
	void SetDrawType(ShapeType type);
	inline void SetNotify(IDrawNotify *pNotify){m_pDrawNofity = pNotify;}
	CSize GetSize() const;
	inline CSize GetImageSize() const { if (m_pBkgnImage) return CSize(m_pBkgnImage->GetWidth(), m_pBkgnImage->GetHeight()); else return CSize(0,0); }
	void SetFigures(const FigureVector& Figs);
	void AddFigures(const FigureVector& Figs);
	inline void ClearFigures() { m_Figures.clear(); this->Invalidate(); }
	inline void GetFigures(FigureVector& Figs) const { Figs = m_Figures; }

	void SetFigureAttributes(int nFigure, int nLineWidth, COLORREF crLineColor, DWORD dwChangedFlags);
	void RestoreFigureAttributes(int nFigure);
	void RestoreAllFiguresAttributes();
	void DeleteFigure(int nFigure);

protected:
	void DrawFigure(Gdiplus::Graphics* graphics, int width, int height, const Figure* pFig);
	void DrawCurFigure(Gdiplus::Graphics* graphics, int width, int height);
	POINTF ConvertToRelativeCoordinate(POINT* point); // ��Ļ����ת�������

protected:
	char* m_pDefPicData; // Ĭ�ϱ���ͼ������
	int m_nDefSizeImage; // Ĭ�ϱ���ͼ�����ݴ�С
	FigureVector m_Figures; // �洢��ͼ�μ�
	Figure m_curFigure; // ��ǰ���Ƶ�ͼ��
	POINTF m_ptMouse; // ��ǰ������꣨������꣩
	int m_nLineWidth;
	COLORREF m_crFigure;
	COLORREF m_crDrawing;
	IDrawNotify *m_pDrawNofity;	// ����֪ͨ�¼�
	Gdiplus::Bitmap* m_pBkgnImage; // ����ͼ

	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnPaint();
	afx_msg BOOL OnEraseBkgnd(CDC* pDC);
	afx_msg void OnLButtonDown(UINT nFlags, CPoint point);
	afx_msg void OnMouseMove(UINT nFlags, CPoint point);
	afx_msg void OnRButtonDown(UINT nFlags, CPoint point);
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
};
