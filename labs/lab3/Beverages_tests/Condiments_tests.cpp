#include "Beverages.h"
#include "Condiments.h"
#include "catch2/catch.hpp"

template <typename Condiment, typename... Args>
auto MakeCondiment(const Args&... args)
{
	return [=](auto&& b) {
		return std::make_unique<Condiment>(std::forward<decltype(b)>(b), args...);
	};
}

template <typename Component, typename Decorator>
auto operator<<(Component&& component, const Decorator& decorate)
{
	return decorate(std::forward<Component>(component));
}

TEST_CASE("Making a beverage with condiments changes the cost and description of the base beverage")
{
	auto beverage = std::make_unique<CLatte>()
		<< MakeCondiment<CCinnamon>()
		<< MakeCondiment<CLemon>(2)
		<< MakeCondiment<CIceCubes>(2, IceCubeType::Dry)
		<< MakeCondiment<CChocolateCrumbs>(2);

	CHECK(beverage->GetDescription() == "Standart Latte, Cinnamon, Lemon x 2, Dry ice cubes x 2, Chocolate crumbs 2g");
	CHECK(beverage->GetCost() == 154);

	SECTION("Making a beverage with cream")
	{
		auto beverage = std::make_unique<CCoffee>()
			<< MakeCondiment<CCream>();

		CHECK(beverage->GetDescription() == "Coffee, Cream");
		CHECK(beverage->GetCost() == 85);
	}

	SECTION("It is allowed to add a maximum of 5 pieces of chocolate to the beverage")
	{
		auto beverage = std::make_unique<CMilkshake>()
			<< MakeCondiment<CChocolate>(10);

		CHECK(beverage->GetDescription() == "Medium Milkshake, Chocolate x 5");
		CHECK(beverage->GetCost() == 110);
	}

	SECTION("Making a beverage with liqour")
	{
		auto beverage = std::make_unique<CCoffee>()
			<< MakeCondiment<CLiquor>(LiquorType::Chocolate)
			<< MakeCondiment<CLiquor>(LiquorType::Nut);

		CHECK(beverage->GetDescription() == "Coffee, Chocolate liquor, Nut liquor");
		CHECK(beverage->GetCost() == 160);
	}
}
