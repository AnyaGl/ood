#include "Ellipse.h"
#include "Rectangle.h"
#include "RegularPolygon.h"
#include "ShapeFactory.h"
#include "Triangle.h"
#include "catch2/catch.hpp"

TEST_CASE("If description is invalid, an exception must be trown")
{
	CShapeFactory factory;
	CHECK_THROWS(factory.CreateShape(""));
	CHECK_THROWS(factory.CreateShape("circle red 10 10 2"));
	CHECK_THROWS(factory.CreateShape("triangle red z0 0 10 10 10 0"));
}

TEST_CASE("Factory must create shape from passed string")
{
	CShapeFactory factory;

	SECTION("create triangle")
	{
		auto shape = factory.CreateShape("triAngle RED 0 0 10   10 10  0  ");
		CTriangle triangle = dynamic_cast<CTriangle&>(*shape.get());

		CHECK(triangle.GetVertex1() == Point{ 0, 0 });
		CHECK(triangle.GetVertex2() == Point{ 10, 10 });
		CHECK(triangle.GetVertex3() == Point{ 10, 0 });
		CHECK(triangle.GetColor() == Color::Red);
	}

	SECTION("create rectangle")
	{
		auto shape = factory.CreateShape("rectangle blue 10.1 10 3 2");
		CRectangle rectangle = dynamic_cast<CRectangle&>(*shape.get());

		CHECK(rectangle.GetLeftTop() == Point{ 10.1, 10 });
		CHECK(rectangle.GetRightBottom() == Point{ 13.1, 8 });
		CHECK(rectangle.GetColor() == Color::Blue);
	}

	SECTION("create ellipse")
	{
		auto shape = factory.CreateShape("ellipse pink 5.4 4.2 3 2");
		CEllipse ellipse = dynamic_cast<CEllipse&>(*shape.get());

		CHECK(ellipse.GetCenter() == Point{ 5.4, 4.2 });
		CHECK(ellipse.GetColor() == Color::Pink);
		CHECK(ellipse.GetHorizontalRadius() == 3);
		CHECK(ellipse.GetVerticalRadius() == 2);
	}

	SECTION("create regular polygon")
	{
		auto shape = factory.CreateShape("regularpolygon green 6 10 10 5");
		CRegularPolygon polygon = dynamic_cast<CRegularPolygon&>(*shape.get());

		CHECK(polygon.GetVertexCount() == 6);
		CHECK(polygon.GetCenter() == Point{ 10, 10 });
		CHECK(polygon.GetRadius() == 5);
		CHECK(polygon.GetColor() == Color::Green);
	}
}
