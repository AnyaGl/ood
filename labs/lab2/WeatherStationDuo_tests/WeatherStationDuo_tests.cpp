﻿#include "catch2/catch.hpp"
#include "Observer.h"
#include <sstream>

TEST_CASE("Observer must print indoor and outdoor statistics, if they are registered")
{
	std::stringstream ss;

	CWeatherData inWd;
	CWeatherData outWd;

	CStatsDisplayTest display(inWd, outWd, ss);
	inWd.RegisterObserver(display, 0);
	outWd.RegisterObserver(display, 1);

	CStatsDisplayTest display1(inWd, outWd, ss);
	outWd.RegisterObserver(display1, 2);

	inWd.SetMeasurements(3, 0.7, 760);
	std::stringstream expect;
	expect << "in \tmin: " << std::to_string(3.) << "\n\tmax: " << std::to_string(3.) << "\n\taverage: " << std::to_string(3.);
	CHECK(expect.str() == ss.str());

	outWd.SetMeasurements(4, 0.8, 761);
	expect << "out \tmin: " + std::to_string(4.) + "\n\tmax: " + std::to_string(4.) + "\n\taverage: " + std::to_string(4.) + 
			  "out \tmin: " + std::to_string(4.) + "\n\tmax: " + std::to_string(4.) + "\n\taverage: " + std::to_string(4.);
	CHECK(expect.str() == ss.str());
	
	outWd.RemoveObserver(display);

	inWd.SetMeasurements(9, 0.8, 761);
	expect << "in \tmin: " << std::to_string(3.) << "\n\tmax: " << std::to_string(9.) << "\n\taverage: " << std::to_string(6.);
	CHECK(expect.str() == ss.str());

	outWd.SetMeasurements(-10, 0.8, 761);
	expect << "out \tmin: " << std::to_string(-10.) << "\n\tmax: " << std::to_string(4.) << "\n\taverage: " << std::to_string(-3.);
	CHECK(expect.str() == ss.str());
}