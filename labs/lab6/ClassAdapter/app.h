#pragma once
#include "modern_graphics_lib.h"
#include "shape_drawing_lib.h"

namespace app
{
class CModernGraphicsAdapter : public graphics_lib::ICanvas
	, public modern_graphics_lib::CModernGraphicsRenderer
{
public:
	CModernGraphicsAdapter(std::ostream& strm)
		: modern_graphics_lib::CModernGraphicsRenderer(strm)
	{
	}

	void MoveTo(int x, int y) override
	{
		m_start = { x, y };
	}
	void LineTo(int x, int y) override
	{
		modern_graphics_lib::CPoint end(x, y);
		DrawLine(m_start, end);
	}

private:
	modern_graphics_lib::CPoint m_start;
};

void PaintPicture(shape_drawing_lib::CCanvasPainter& painter)
{
	using namespace shape_drawing_lib;

	CTriangle triangle({ 10, 15 }, { 100, 200 }, { 150, 250 });
	CRectangle rectangle({ 30, 40 }, 18, 24);

	painter.Draw(triangle);
	painter.Draw(rectangle);
}

void PaintPictureOnCanvas()
{
	graphics_lib::CCanvas simpleCanvas;
	shape_drawing_lib::CCanvasPainter painter(simpleCanvas);
	PaintPicture(painter);
}

void PaintPictureOnModernGraphicsRenderer()
{
	CModernGraphicsAdapter canvas(std::cout);
	canvas.BeginDraw();
	shape_drawing_lib::CCanvasPainter painter(canvas);
	PaintPicture(painter);
}
} // namespace app
