#include "../ClassAdapter/app.h"
#include "catch2/catch.hpp"
#include <sstream>

TEST_CASE("When the adapter creates BeginDraw() isn't called")
{
	std::stringstream ss;
	app::CModernGraphicsAdapter adapter(ss);

	adapter.MoveTo(50, 50);

	CHECK_THROWS(adapter.LineTo(100, 100));
	adapter.BeginDraw();
	CHECK_NOTHROW(adapter.LineTo(100, 100));
}

TEST_CASE("After destroying the adapter EndDraw() is called")
{
	std::stringstream ss;
	{
		app::CModernGraphicsAdapter adapter(ss);
		adapter.BeginDraw();
		adapter.MoveTo(50, 50);
		adapter.LineTo(100, 100);
	}
	std::string expectedStr = "<draw>\n  <line fromX=\"50\" fromY=\"50\" toX=\"100\" toY=\"100\">\n    <color r=\"0\" g=\"0\" b=\"0\" a=\"1\" />\n  </line>\n</draw>\n";

	CHECK(ss.str() == expectedStr);
}

TEST_CASE("EndDraw() finishes drawing")
{
	std::stringstream ss;

	app::CModernGraphicsAdapter adapter(ss);
	adapter.BeginDraw();
	adapter.MoveTo(50, 50);
	adapter.LineTo(100, 100);
	adapter.EndDraw();

	std::string expectedStr = "<draw>\n  <line fromX=\"50\" fromY=\"50\" toX=\"100\" toY=\"100\">\n    <color r=\"0\" g=\"0\" b=\"0\" a=\"1\" />\n  </line>\n</draw>\n";

	CHECK(ss.str() == expectedStr);
}

TEST_CASE("Drawing a line using an adapter draws a line with renderer")
{
	std::stringstream ss;
	app::CModernGraphicsAdapter adapter(ss);
	adapter.BeginDraw();
	adapter.MoveTo(50, 50);
	adapter.LineTo(100, 100);

	std::string expectedStr = "<draw>\n  <line fromX=\"50\" fromY=\"50\" toX=\"100\" toY=\"100\">\n    <color r=\"0\" g=\"0\" b=\"0\" a=\"1\" />\n  </line>\n";

	CHECK(ss.str() == expectedStr);
}

TEST_CASE("SetColor() converts hex color to rgba")
{
	std::stringstream ss;
	app::CModernGraphicsAdapter adapter(ss);
	adapter.BeginDraw();
	adapter.SetColor(0xAA12B0);
	adapter.MoveTo(50, 50);
	adapter.LineTo(100, 100);

	std::string expectedStr = "<draw>\n  <line fromX=\"50\" fromY=\"50\" toX=\"100\" toY=\"100\">\n    <color r=\"0.67\" g=\"0.07\" b=\"0.69\" a=\"1\" />\n  </line>\n";

	CHECK(ss.str() == expectedStr);
}
