#include "pch.h"
#include "Core.h"

Core::Core()
	:mainCanvas(std::make_unique<MainCanvas>())
{
}

Core::~Core()
{
}

void Core::Initialize(CRect& clientRect)
{
	mainCanvas->InitCanvas(clientRect);
}

void Core::Draw(CDC& dc)
{
	mainCanvas->Draw(dc);
}

void Core::ReDraw()
{
	clickPoints.clear();
	mainCanvas->ClearCanvas();
}

bool Core::Addpoint(CPoint dialogPoint)
{
	if (clickPoints.size() >= MAX_CLICK || !mainCanvas->Contains(dialogPoint))
	{
		return false;
	}

	CPoint point = mainCanvas->ToCanvasPoint(dialogPoint);

	clickPoints.push_back(point);

	mainCanvas->DrawPointCircle(point, MAX_SIZE);

	return true;
}
