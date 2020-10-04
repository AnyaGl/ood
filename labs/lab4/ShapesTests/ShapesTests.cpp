#include "Ellipse.h"
#include "MockCanvas.h"
#include "Rectangle.h"
#include "RegularPolygon.h"
#include "Triangle.h"
#include "catch2/catch.hpp"

TEST_CASE("Rectangle")
{
	Point leftTop = { 5, 5.5 };
	double width = 10;
	double height = 5;
	Point rightBottom = { 15, 0.5 };

	CRectangle rectangle(Color::Black, leftTop, width, height);

	SECTION("must be initialized with the passed values")
	{
		CHECK(rectangle.GetLeftTop() == leftTop);
		CHECK(rectangle.GetRightBottom() == rightBottom);
		CHECK(rectangle.GetColor() == Color::Black);
	}

	SECTION("must draw 4 colored lines on Canvas")
	{
		CMockCanvas canvas;
		rectangle.Draw(canvas);

		CHECK(canvas.GetColor() == Color::Black);
		CHECK(canvas.GetLineCounter() == 4);
		CHECK(canvas.GetEllipseCounter() == 0);
	}
}

TEST_CASE("Triangle")
{
	Point vertex1 = { 0, 0 };
	Point vertex2 = { 5, 12 };
	Point vertex3 = { 5, 0 };
	Color color = Color::Pink;

	CTriangle triangle(color, vertex1, vertex2, vertex3);

	SECTION("must be initialized with the passed values")
	{
		CHECK(triangle.GetVertex1() == vertex1);
		CHECK(triangle.GetVertex2() == vertex2);
		CHECK(triangle.GetVertex3() == vertex3);
		CHECK(triangle.GetColor() == color);
	}

	SECTION("must draw 3 colored lines on Canvas")
	{
		CMockCanvas canvas;
		triangle.Draw(canvas);

		CHECK(canvas.GetColor() == color);
		CHECK(canvas.GetLineCounter() == 3);
		CHECK(canvas.GetEllipseCounter() == 0);
	}
}

TEST_CASE("Ellipse")
{
	Point center = { 5, 0 };
	double horizontalRadius = 10;
	double verticalRadius = 5;
	Color color = Color::Green;

	CEllipse ellipse(color, center, horizontalRadius, verticalRadius);

	SECTION("must be initialized with the passed values")
	{
		CHECK(ellipse.GetCenter() == center);
		CHECK(ellipse.GetColor() == color);
		CHECK(ellipse.GetHorizontalRadius() == horizontalRadius);
		CHECK(ellipse.GetVerticalRadius() == verticalRadius);
	}

	SECTION("must draw 1 colored ellipse on Canvas")
	{
		CMockCanvas canvas;
		ellipse.Draw(canvas);

		CHECK(canvas.GetColor() == color);
		CHECK(canvas.GetLineCounter() == 0);
		CHECK(canvas.GetEllipseCounter() == 1);
	}
}

TEST_CASE("RegularPolygon")
{
	size_t vertexCount = 5;
	Point center = { 10, 10 };
	double radius = 5.1;
	Color color = Color::Yellow;

	CRegularPolygon polygon(color, vertexCount, center, radius);

	SECTION("must be initialized with the passed values")
	{
		CHECK(polygon.GetCenter() == center);
		CHECK(polygon.GetRadius() == radius);
		CHECK(polygon.GetVertexCount() == vertexCount);
		CHECK(polygon.GetColor() == color);
	}

	SECTION("vertex count must be more than 2")
	{
		CHECK_THROWS(CRegularPolygon(color, 2, center, radius));
	}

	SECTION("must draw transmitted number of colored lines on Canvas")
	{
		CMockCanvas canvas;
		polygon.Draw(canvas);

		CHECK(canvas.GetColor() == color);
		CHECK(canvas.GetLineCounter() == vertexCount);
		CHECK(canvas.GetEllipseCounter() == 0);
	}
}
