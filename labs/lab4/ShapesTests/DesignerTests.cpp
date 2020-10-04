#include "Designer.h"
#include "ShapeFactory.h"
#include "Triangle.h"
#include "catch2/catch.hpp"
#include <sstream>

TEST_CASE("Designer must create picture draft from input stream")
{
	CShapeFactory factory;
	CDesigner designer(factory);

	std::stringstream ss;
	ss << "Rectangle red 5.1 4.2 2 1\nTriangle blue 0 0 10 10 10 0";

	CPictureDraft draft = designer.CreateDraft(ss);

	CHECK(draft.GetShapeCount() == 2);

	CTriangle draftTriangle = dynamic_cast<CTriangle&>(draft.GetShape(1));
	CHECK(draftTriangle.GetColor() == Color::Blue);
	CHECK(draftTriangle.GetVertex1() == Point{ 0, 0 });
	CHECK(draftTriangle.GetVertex2() == Point{ 10, 10 });
	CHECK(draftTriangle.GetVertex3() == Point{ 10, 0 });
}
