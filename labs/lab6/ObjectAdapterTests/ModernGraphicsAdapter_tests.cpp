#include "../ObjectAdapter/app.h"
#include "catch2/catch.hpp"
#include <sstream>

TEST_CASE("When the adapter creates BeginDraw() in renderer isn't called")
{
	std::stringstream ss;
	modern_graphics_lib::CModernGraphicsRenderer renderer(ss);
	app::CModernGraphicsAdapter adapter(renderer);

	CHECK_THROWS(renderer.DrawLine({ 0, 0 }, { 20, 30 }));
}

TEST_CASE("After destroying the adapter EndDraw() in renderer isn't called")
{
	std::stringstream ss;
	modern_graphics_lib::CModernGraphicsRenderer renderer(ss);
	renderer.BeginDraw();
	{
		app::CModernGraphicsAdapter adapter(renderer);

		adapter.MoveTo(50, 50);
		adapter.LineTo(100, 100);
	}

	CHECK_NOTHROW(renderer.DrawLine({ 0, 0 }, { 20, 30 }));
}

TEST_CASE("Drawing a line using an adapter draws a line with renderer")
{
	std::stringstream ss;
	modern_graphics_lib::CModernGraphicsRenderer renderer(ss);
	
	app::CModernGraphicsAdapter adapter(renderer);
	renderer.BeginDraw();

	adapter.MoveTo(50, 50);
	adapter.LineTo(100, 100);
	
	renderer.EndDraw();

	std::string expectedStr = "<draw>\n  <line fromX=\"50\" fromY=\"50\" toX=\"100\" toY=\"100\"/>\n</draw>\n";

	CHECK(ss.str() == expectedStr);
}

TEST_CASE("If EndDraw() on renderer, then when you try to draw using the adapter, there will be an exception")
{
	std::stringstream ss;
	modern_graphics_lib::CModernGraphicsRenderer renderer(ss);
	app::CModernGraphicsAdapter adapter(renderer);

	renderer.BeginDraw();

	adapter.MoveTo(50, 50);
	adapter.LineTo(100, 100);

	renderer.EndDraw();
	CHECK_THROWS(adapter.LineTo(100, 200));
}
