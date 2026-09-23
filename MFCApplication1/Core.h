#pragma once

#include "pch.h"

#define MAX_CLICK 3
#define MAX_SIZE 10

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

	bool Addpoint(CPoint dialogPoint);
};

