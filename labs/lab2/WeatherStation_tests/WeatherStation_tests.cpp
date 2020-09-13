#include "../catch2/catch.hpp"
#include "Observer.h"
#include <sstream>

TEST_CASE("Removing yourself in method Update must not lead to UB")
{
	CWeatherDataTest wd;

	CRemovedObserver display(wd);
	wd.RegisterObserver(display, 0);

	wd.SetMeasurements(3, 0.7, 760);
}

TEST_CASE("High priority observers are alerted first")
{
	std::stringstream ss;
	CWeatherData wd;
	CPriorityObserver ob1(1, ss);
	CPriorityObserver ob2(2, ss);
	CPriorityObserver ob3(3, ss);

	wd.RegisterObserver(ob1, 2);
	wd.RegisterObserver(ob2, 3);
	wd.RegisterObserver(ob3, 1);

	wd.SetMeasurements(3, 0.7, 760);

	CHECK(ss.str() == "213");
}