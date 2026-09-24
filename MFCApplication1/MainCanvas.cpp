#include "pch.h"
#include "MainCanvas.h"

MainCanvas::MainCanvas()
{
}

MainCanvas::~MainCanvas()
{
}

void MainCanvas::InitCanvas(CRect& clientRect)
{
	canvasRect.SetRect(20, 60, clientRect.Width() - 20, clientRect.Height() - 20);

	if (!canvas.IsNull())
	{
		canvas.Destroy();
	}

	int width = canvasRect.Width();
	int height = canvasRect.Height();

	canvas.Create(width, -height, bpp);

	RGBQUAD colors[COLOR_RANGE] = {};

	for (int i = 0; i < COLOR_RANGE; ++i)
	{
		colors[i].rgbGreen = i;
		colors[i].rgbRed = i;
		colors[i].rgbBlue = i;
	}

	canvas.SetColorTable(0, COLOR_RANGE, colors);

	BYTE* pixels = reinterpret_cast<BYTE*>(canvas.GetBits());

	int pitch = canvas.GetPitch();

	for (int y = 0; y < height; ++y)
	{
		memset(pixels + y * pitch, 255, width);
	}
}

void MainCanvas::Draw(CDC& dc)
{
	if (canvas.IsNull())
	{
		return;
	}

	canvas.Draw(dc, canvasRect);
}

void MainCanvas::ClearCanvas()
{
	if (canvas.IsNull())
	{
		return;
	}

	int pitch = canvas.GetPitch();
	int height = canvas.GetHeight();

	BYTE* pixels = reinterpret_cast<BYTE*>(canvas.GetBits());

	for (int y = 0; y < height; ++y)
	{
		memset(pixels + y * pitch, 255, abs(pitch));
	}
}

void MainCanvas::DrawPointCircle(CPoint center, int radius)
{
	if (canvas.IsNull() || radius <= 0)
	{
		return;
	}

	BYTE* pixels = reinterpret_cast<BYTE*>(canvas.GetBits());

	int pitch = canvas.GetPitch();
	int width = canvas.GetWidth();
	int height = canvas.GetHeight();
	int diameter = radius * radius;

	for (int y = center.y - radius; y <= center.y + radius; ++y)
	{
		for (int x = center.x - radius; x <= center.x + radius; ++x)
		{
			if (x < 0 || x >= width || y < 0 || y >= height)
			{
				continue;
			}

			int dx = x - center.x;
			int dy = y - center.y;

			if (dx * dx + dy * dy <= diameter)
			{
				pixels[y * pitch + x] = 0;
			}
		}
	}
}

void MainCanvas::DrawCircleOutline(double centerX, double centerY, double radius, double thickness)
{
	if (canvas.IsNull() || radius <= 0)
	{
		return;
	}

	BYTE* pixels = reinterpret_cast<BYTE*>(canvas.GetBits());

	int pitch = canvas.GetPitch();
	int width = canvas.GetWidth();
	int height = canvas.GetHeight();

	double harf = thickness / 2.f;
	double inner = radius - harf;
	double outer = radius + harf;

	int left = static_cast<int>(std::floor(centerX - outer));

	int right = static_cast<int>(std::ceil(centerX + outer));

	int top = static_cast<int>(std::floor(centerY - outer));

	int bottom = static_cast<int>(std::ceil(centerY + outer));

	
    for (int y = top; y <= bottom; ++y)
    {
        for (int x = left; x <= right; ++x)
        {
			if (x < 0 || x >= width || y < 0 || y >= height)
			{
				continue;
			}

			double dx = x - centerX;
			double dy = y - centerY;

			double distanceSquared = dx * dx + dy * dy;

			if (distanceSquared >= inner * inner &&
				distanceSquared <= outer * outer)
			{
				pixels[y * pitch + x] = 0;
			}
		}
	}
}

