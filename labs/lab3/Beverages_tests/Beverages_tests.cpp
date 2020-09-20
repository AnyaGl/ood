#include "Beverages.h"
#include "Condiments.h"
#include "catch2/catch.hpp"

TEST_CASE("Cappuccino must be the size passed to constructor")
{
	CCappuccino standartCappuccino{ CappuccinoSize::Standart };
	CHECK(standartCappuccino.GetDescription() == "Standart Cappuccino");
	CHECK(standartCappuccino.GetCost() == 80);

	CCappuccino doubleCappuccino{ CappuccinoSize::Double };
	CHECK(doubleCappuccino.GetDescription() == "Double Cappuccino");
	CHECK(doubleCappuccino.GetCost() == 120);

	SECTION("Default Cappuccino must be standard size")
	{
		CCappuccino cappuccino{};
		CHECK(cappuccino.GetDescription() == "Standart Cappuccino");
		CHECK(cappuccino.GetCost() == 80);
	}
}

TEST_CASE("Latte must be the size passed to constructor")
{
	CLatte standartLatte{ LatteSize::Standart };
	CHECK(standartLatte.GetDescription() == "Standart Latte");
	CHECK(standartLatte.GetCost() == 90);

	CLatte doubleLatte{ LatteSize::Double };
	CHECK(doubleLatte.GetDescription() == "Double Latte");
	CHECK(doubleLatte.GetCost() == 130);

	SECTION("Default Latte must be standard size")
	{
		CLatte latte{};
		CHECK(latte.GetDescription() == "Standart Latte");
		CHECK(latte.GetCost() == 90);
	}
}

TEST_CASE("Tea must be the type passed to constructor")
{
	CTea blackTea{ TeaType::Black };
	CHECK(blackTea.GetDescription() == "Black Tea");
	CHECK(blackTea.GetCost() == 30);

	CTea greenTea{ TeaType::Green };
	CHECK(greenTea.GetDescription() == "Green Tea");
	CHECK(greenTea.GetCost() == 30);

	CTea whiteTea{ TeaType::White };
	CHECK(whiteTea.GetDescription() == "White Tea");
	CHECK(whiteTea.GetCost() == 30);

	CTea herbalTea{ TeaType::Herbal };
	CHECK(herbalTea.GetDescription() == "Herbal Tea");
	CHECK(herbalTea.GetCost() == 30);

	SECTION("Default tea must be black")
	{
		CTea tea{};
		CHECK(blackTea.GetDescription() == "Black Tea");
		CHECK(blackTea.GetCost() == 30);
	}
}

TEST_CASE("Milkshake must be the size passed to constructor")
{
	CMilkshake smallMilkshake{ MilkshakeSize::Small };
	CHECK(smallMilkshake.GetDescription() == "Small Milkshake");
	CHECK(smallMilkshake.GetCost() == 50);

	CMilkshake mediumMilkshake{ MilkshakeSize::Medium };
	CHECK(mediumMilkshake.GetDescription() == "Medium Milkshake");
	CHECK(mediumMilkshake.GetCost() == 60);

	CMilkshake largeMilkshake{ MilkshakeSize::Large };
	CHECK(largeMilkshake.GetDescription() == "Large Milkshake");
	CHECK(largeMilkshake.GetCost() == 80);

	SECTION("Default Milkshake must be medium size")
	{
		CMilkshake milkshake{};
		CHECK(milkshake.GetDescription() == "Medium Milkshake");
		CHECK(milkshake.GetCost() == 60);
	}
}