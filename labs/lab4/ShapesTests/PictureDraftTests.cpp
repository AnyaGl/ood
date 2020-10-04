#include "Ellipse.h"
#include "PictureDraft.h"
#include "Triangle.h"
#include "catch2/catch.hpp"
#include <memory>

TEST_CASE("Empty draft must be created by default")
{
	CPictureDraft draft;
	CHECK(draft.GetShapeCount() == 0);
	CHECK_THROWS(draft.GetShape(0));
}

TEST_CASE("Creating draft")
{
	CPictureDraft draft;

	CTriangle triangle(Color::Pink, Point{ 0, 0 }, Point{ 5, 12 }, Point{ 5, 0 });
	CEllipse ellipse(Color::Blue, Point{ 10, 5 }, 3, 2);
	auto trianglePtr = std::make_unique<CTriangle>(triangle);
	auto ellipsePtr = std::make_unique<CEllipse>(ellipse);

	draft.AddShape(std::move(trianglePtr));
	draft.AddShape(std::move(ellipsePtr));

	SECTION("GetShapeCount() must return number of shapes in draft")
	{
		CHECK(draft.GetShapeCount() == 2);
	}

	SECTION("GetShape() must return shape with specified index")
	{
		CHECK_NOTHROW(draft.GetShape(0));

		CTriangle draftTriangle = dynamic_cast<CTriangle&>(draft.GetShape(0)); 
		CHECK(draftTriangle.GetColor() == triangle.GetColor());
		CHECK(draftTriangle.GetVertex1() == triangle.GetVertex1());
		CHECK(draftTriangle.GetVertex2() == triangle.GetVertex2());
		CHECK(draftTriangle.GetVertex3() == triangle.GetVertex3());

		CHECK_NOTHROW(draft.GetShape(1));

		CEllipse draftEllipse = dynamic_cast<CEllipse&>(draft.GetShape(1));
		CHECK(draftEllipse.GetCenter() == ellipse.GetCenter());
		CHECK(draftEllipse.GetColor() == ellipse.GetColor());
		CHECK(draftEllipse.GetHorizontalRadius() == ellipse.GetHorizontalRadius());
		CHECK(draftEllipse.GetVerticalRadius() == ellipse.GetVerticalRadius());
	}
}