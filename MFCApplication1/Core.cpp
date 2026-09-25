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

bool Core::Addpoint(CPoint dialogPoint, int size)
{
	if (clickPoints.size() >= MAX_CLICK || !mainCanvas->Contains(dialogPoint))
	{
		return false;
	}

	CPoint point = mainCanvas->ToCanvasPoint(dialogPoint);

	clickPoints.push_back(point);

	mainCanvas->DrawPointCircle(point, size);

	return true;
}

bool Core::CalculateCircle(double thickness) const
{
	if (clickPoints.size() != MAX_CLICK)
	{
		return false;
	}

	double x1 = clickPoints[0].x;
	double y1 = clickPoints[0].y;

	double x2 = clickPoints[1].x;
	double y2 = clickPoints[1].y;

	double x3 = clickPoints[2].x;
	double y3 = clickPoints[2].y;

	// 일직선인지 확인
	double d = 2.0f *
			(x1 * (y2 - y3) +
			x2 * (y3 - y1) +
			x3 * (y1 - y2));

	if (std::abs(d) < 0.000001)
	{
		return false;
	}

	double a = x1 * x1 + y1 * y1;
	double b = x2 * x2 + y2 * y2;
	double c = x3 * x3 + y3 * y3;

	double centerX =
			(a * (y2 - y3) +
			b * (y3 - y1) +
			c * (y1 - y2)) / d;

	double centerY =
			(a * (x3 - x2) +
			b * (x1 - x3) +
			c * (x2 - x1)) / d;

	double dx = centerX - x1;
	double dy = centerY - y1;

	double radius = std::sqrt(dx * dx + dy * dy);

	mainCanvas->DrawCircleOutline(centerX, centerY, radius, thickness);

	return true;
}

void Core::RandomCircle(int size, int thickness)
{
	if (clickPoints.size() != MAX_CLICK)
	{
		return;
	}

	static std::mt19937 generator(std::random_device{}());

	int pointRadius = size;

	std::uniform_int_distribution<int> xDist(pointRadius, mainCanvas->GetWidth() - pointRadius - 1);
	std::uniform_int_distribution<int> yDist(pointRadius, mainCanvas->GetHeight() - pointRadius - 1);

	for (CPoint& point : clickPoints)
	{
		point.x = xDist(generator);
		point.y = yDist(generator);
	}

	mainCanvas->ClearCanvas();

	CalculateCircle(thickness);

	for (const CPoint& point : clickPoints)
	{
		mainCanvas->DrawPointCircle(point, pointRadius);
	}
}

int Core::FindPoint(CPoint mousePoint, int pointRadius) const
{
	if (!mainCanvas->Contains(mousePoint) || clickPoints.size() != MAX_CLICK)
	{
		return -1;
	}

	CPoint canvasPoint = mainCanvas->ToCanvasPoint(mousePoint);
	
	for (int i = 0; i < MAX_CLICK; ++i)
	{
		int dx = canvasPoint.x - clickPoints[i].x ;
		int dy = canvasPoint.y - clickPoints[i].y ;

		if (dx * dx + dy * dy <= pointRadius * pointRadius)
		{
			return i;
		}
	}
	
	return -1;
}

void Core::MovePoint(int index, CPoint mousePoint, int pointRadius, int thickness)
{
	clickPoints[index] = mousePoint;

	mainCanvas->ClearCanvas();

	CalculateCircle(thickness);

	for (const CPoint& point : clickPoints)
	{
		mainCanvas->DrawPointCircle(point, pointRadius);
	}

}

CString Core::GetCoordinateText() const
{
	CString result;

	for (size_t i = 0; i < clickPoints.size(); ++i)
	{
		CString line;

		line.Format(
			_T("P%d = (%d, %d)    "),
			static_cast<int>(i + 1),
			clickPoints[i].x,
			clickPoints[i].y
		);

		result += line;
	}

	return result;
}