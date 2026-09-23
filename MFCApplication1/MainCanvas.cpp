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
	canvasRect.SetRect(20, 40, clientRect.Width() - 20, clientRect.Height() - 20);

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

