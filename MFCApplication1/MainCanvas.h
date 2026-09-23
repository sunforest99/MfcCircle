#pragma once

#include "pch.h"

class MainCanvas
{
private:
	CImage canvas;
	CRect canvasRect;

	const int bpp = 8;	// RGB 8bit 채널
public:
	MainCanvas();
	~MainCanvas();

	void InitCanvas(CRect& clientRect);
	void Draw(CDC& dc);
	void ClearCanvas();

	// 간단한 Get 함수
	bool Contains(CPoint point) const { return canvasRect.PtInRect(point); }
	CPoint ToCanvasPoint(CPoint point) const { return CPoint(point.x - canvasRect.left, point.y - canvasRect.top); }
	void DrawPointCircle(CPoint center, int radius);
};

