#include "Ellipse.h"
#include "MockCanvas.h"
#include "Painter.h"
#include "Rectangle.h"
#include "Triangle.h"
#include "catch2/catch.hpp"
#include <sstream>

TEST_CASE("Painter must draw all received shapes on canvas")
{
	CPainter painter;
	CMockCanvas canvas;
	CPictureDraft draft;

	auto triangle = std::make_unique<CTriangle>(Color::Pink, Point{ 0, 0 }, Point{ 5, 12 }, Point{ 5, 0 });
	auto ellipse = std::make_unique<CEllipse>(Color::Green, Point{ 10, 5 }, 3, 2);
	auto rectangle = std::make_unique<CRectangle>(Color::Blue, Point{ 5, 5 }, 4, 2);
	draft.AddShape(std::move(triangle));
	draft.AddShape(std::move(ellipse));
	draft.AddShape(std::move(rectangle));

	painter.DrawPicture(draft, canvas);

	CHECK(canvas.GetColor() == Color::Blue);
	CHECK(canvas.GetEllipseCounter() == 1);
	CHECK(canvas.GetLineCounter() == 7);
}
