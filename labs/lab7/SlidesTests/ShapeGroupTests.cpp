#include "../Slides/Ellipse.h"
#include "../Slides/ShapeGroup.h"
#include "../Slides/Rectangle.h"
#include "../Slides/Triangle.h"
#include "MockCanvas.h"
#include "catch2/catch.hpp"
#include <sstream>

namespace
{
enum Color : RGBAColor
{
	Red = 0xFF0000FF,
	Green = 0x00FF00FF,
	Blue = 0x0000FFFF
};

const double ELLIPSE = 0.01;

std::shared_ptr<IShape> CreateTriangle()
{
	auto triangle = std::make_shared<CTriangle>(PointD{ 0, 0 }, PointD{ 10, 0 }, PointD{ 10, 10 });
	triangle->GetFillStyle()->SetColor(Color::Blue);
	triangle->GetOutlineStyle()->Enable(false);
	return triangle;
}

std::shared_ptr<IShape> CreateEllipse()
{
	auto ellipse = std::make_shared<CEllipse>(PointD{ 50, 50 }, 30, 20);
	ellipse->GetOutlineStyle()->SetColor(Color::Green);
	ellipse->GetOutlineStyle()->SetThickness(3);
	ellipse->GetFillStyle()->SetColor(Color::Red);
	return ellipse;
}

std::shared_ptr<IShape> CreateRectangle()
{
	auto rectangle = std::make_shared<CRectangle>(PointD{ 100, 80 }, 60, 30);
	rectangle->GetOutlineStyle()->SetColor(Color::Green);
	rectangle->GetFillStyle()->Enable(false);
	return rectangle;
}
std::shared_ptr<IShape> CreateEmptyGroup()
{
	return std::make_shared<CShapeGroup>();
}
bool IsEqualRect(RectD const& rect1, RectD const& rect2)
{
	return abs(rect1.leftTop.x - rect2.leftTop.x) < ELLIPSE
		&& abs(rect1.leftTop.y - rect2.leftTop.y) < ELLIPSE
		&& abs(rect1.width - rect2.width) < ELLIPSE
		&& abs(rect1.height - rect2.height) < ELLIPSE;
}
} // namespace

TEST_CASE("Draw() must draw all shapes on canvas")
{
	auto group = std::make_shared<CShapeGroup>();
	group->InsertShape(CreateEllipse());
	group->InsertShape(CreateTriangle());

	std::stringstream ss;
	MockCanvas canvas(ss);
	group->Draw(canvas);

	std::stringstream expect;
	expect << "SetFillColor #ff0000ff\n"
		   << "SetLineColor #00ff00ff\n"
		   << "SetLineThickness 3\n"
		   << "DrawEllipse left: 20; top: 30; width: 60; height: 40\n"
		   << "FillEllipse left: 20; top: 30; width: 60; height: 40\n"
		   << "SetFillColor #0000ffff\n"
		   << "FillPolygon with vertexes:\n"
		   << "\t(0, 0)\n"
		   << "\t(10, 0)\n"
		   << "\t(10, 10)\n";

	CHECK(ss.str() == expect.str());
}

TEST_CASE("GetFrame() returns the rectangle that bounds the shapes")
{
	auto group = std::make_shared<CShapeGroup>();
	group->InsertShape(CreateEllipse());
	group->InsertShape(CreateEmptyGroup());
	group->InsertShape(CreateRectangle());

	RectD expect = { PointD{ 20, 30 }, 140, 80 };
	RectD rect = *group->GetFrame();
	CHECK(IsEqualRect(rect, expect));

	SECTION("If group is empty GetFrame() returns null")
	{
		auto group = std::make_shared<CShapeGroup>();
		CHECK_FALSE(group->GetFrame());
	}
}

TEST_CASE("SetFrame() sets new coordinates for shapes")
{
	auto group = std::make_shared<CShapeGroup>();
	group->InsertShape(CreateEllipse());
	group->InsertShape(CreateRectangle());
	group->InsertShape(CreateTriangle());

	CHECK_NOTHROW(group->SetFrame(RectD{ PointD{ 0, 0 }, 30, 20 }));

	RectD expect = { PointD{ 3.75, 5.45 }, 11.25, 7.27 };
	auto ellipse = group->GetShapeAtIndex(0);
	CHECK(IsEqualRect(*ellipse->GetFrame(), expect));

	expect = { PointD{ 18.75, 14.54 }, 11.25, 5.45 };
	auto rectangle = group->GetShapeAtIndex(1);
	CHECK(IsEqualRect(*rectangle->GetFrame(), expect));

	expect = { PointD{ 0, 0 }, 1.88, 1.81 };
	auto triangle = group->GetShapeAtIndex(2);
	CHECK(IsEqualRect(*triangle->GetFrame(), expect));
}

TEST_CASE("Outline or group fill styles should return if the group shapes have the same style")
{
	auto group = std::make_shared<CShapeGroup>();
	group->InsertShape(CreateEllipse());
	group->InsertShape(CreateRectangle());
	group->InsertShape(CreateTriangle());

	CHECK_FALSE(group->GetFillStyle()->GetColor());
	CHECK_FALSE(group->GetFillStyle()->IsEnabled());
	CHECK_FALSE(group->GetOutlineStyle()->GetColor());
	CHECK_FALSE(group->GetOutlineStyle()->IsEnabled());
	CHECK_FALSE(group->GetOutlineStyle()->GetThickness());

	group->GetFillStyle()->SetColor(Color::Blue);
	group->GetFillStyle()->Enable(true);
	group->GetOutlineStyle()->SetColor(Color::Green);
	group->GetOutlineStyle()->Enable(false);
	group->GetOutlineStyle()->SetThickness(30.);

	CHECK(*group->GetFillStyle()->GetColor() == Color::Blue);
	CHECK(*group->GetFillStyle()->IsEnabled() == true);
	CHECK(*group->GetOutlineStyle()->GetColor() == Color::Green);
	CHECK(*group->GetOutlineStyle()->IsEnabled() == false);
	CHECK(*group->GetOutlineStyle()->GetThickness() == 30.);
}

TEST_CASE("GetGroup() returns pointer to current group")
{
	auto group = std::make_shared<CShapeGroup>();
	group->InsertShape(CreateEllipse());

	CHECK(group == group->GetGroup());
}

TEST_CASE("InsertShape() must insert shape in group")
{
	auto group = std::make_shared<CShapeGroup>();
	SECTION("shape is null")
	{
		auto shape = std::shared_ptr<CShapeGroup>();
		CHECK_THROWS(group->InsertShape(shape));
	}
	SECTION("if position is not specified then shape must be inserted to the end")
	{
		auto ellipse = CreateEllipse();
		auto triangle = CreateTriangle();
		CHECK_NOTHROW(group->InsertShape(ellipse));
		CHECK_NOTHROW(group->InsertShape(triangle));

		CHECK(group->GetShapeAtIndex(0) == ellipse);
		CHECK(group->GetShapeAtIndex(1) == triangle);
	}
	SECTION("position is specified")
	{
		auto ellipse = CreateEllipse();
		auto triangle = CreateTriangle();
		CHECK_NOTHROW(group->InsertShape(ellipse));
		CHECK_NOTHROW(group->InsertShape(triangle, 0));

		CHECK(group->GetShapeAtIndex(1) == ellipse);
		CHECK(group->GetShapeAtIndex(0) == triangle);
	}
	SECTION("invalid position")
	{
		auto ellipse = CreateEllipse();
		auto triangle = CreateTriangle();
		CHECK_THROWS(group->InsertShape(ellipse, 0));
	}
}

TEST_CASE("GetShapeAtIndex() must return shape on specified position")
{
	auto group = std::make_shared<CShapeGroup>();
	auto ellipse = CreateEllipse();
	auto triangle = CreateTriangle();
	group->InsertShape(ellipse);
	group->InsertShape(triangle, 0);

	CHECK(group->GetShapeAtIndex(1) == ellipse);
	CHECK(group->GetShapeAtIndex(0) == triangle);

	SECTION("invalid position")
	{
		CHECK_THROWS(group->GetShapeAtIndex(2));
	}
}

TEST_CASE("RemoveShapeAtIndex() must remove shape from specified position")
{
	auto group = std::make_shared<CShapeGroup>();
	auto ellipse = CreateEllipse();
	auto triangle = CreateTriangle();
	group->InsertShape(ellipse);
	group->InsertShape(triangle, 0);

	CHECK(group->GetShapesCount() == 2);
	group->RemoveShapeAtIndex(0);

	CHECK(group->GetShapeAtIndex(0) == ellipse);
	CHECK(group->GetShapesCount() == 1);

	SECTION("invalid position")
	{
		CHECK_THROWS(group->RemoveShapeAtIndex(1));
	}
}