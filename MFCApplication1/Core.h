#pragma once

#include <random>
#include "pch.h"

#define MAX_CLICK 3

#include "MainCanvas.h"

class Core
{
private:
	std::unique_ptr<MainCanvas> mainCanvas;

	std::vector<CPoint> clickPoints;

public:
	Core();
	~Core();

	void Initialize(CRect& clientRect);

	void Draw(CDC& dc);
	void ReDraw();
	bool Addpoint(CPoint dialogPoint, int size);

	bool CalculateCircle(double thickness) const;
	void RandomCircle(int size);

	CString Core::GetCoordinateText() const;
};

