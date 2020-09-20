#pragma once
#include "IBeverage.h"

class CBeverage : public IBeverage
{
public:
	CBeverage(const std::string& description)
		: m_description(description)
	{
	}

	std::string GetDescription() const override final
	{
		return m_description;
	}

protected:
	std::string m_description;
};

class CCoffee : public CBeverage
{
public:
	CCoffee(const std::string& description = "Coffee")
		: CBeverage(description)
	{
	}

	double GetCost() const override
	{
		return 60;
	}
};

enum class CappuccinoSize
{
	Standart,
	Double
};

class CCappuccino : public CCoffee
{
public:
	CCappuccino(CappuccinoSize size = CappuccinoSize::Standart)
		: CCoffee("Standart Cappuccino")
		, m_cost(80)
	{
		if (size == CappuccinoSize::Double)
		{
			m_description = "Double Cappuccino";
			m_cost = 120;
		}
	}

	double GetCost() const override
	{
		return m_cost;
	}

private:
	double m_cost;
};

enum class LatteSize
{
	Standart,
	Double
};

class CLatte : public CCoffee
{
public:
	CLatte(LatteSize size = LatteSize::Standart)
		: CCoffee("Standart Latte")
		, m_cost(90)
	{
		if (size == LatteSize::Double)
		{
			m_description = "Double Latte";
			m_cost = 130;
		}
	}

	double GetCost() const override
	{
		return m_cost;
	}

private:
	double m_cost;
};

enum class TeaType
{
	Black,
	Green,
	White,
	Herbal
};

class CTea : public CBeverage
{
public:
	CTea(TeaType teaType = TeaType::Black)
		: CBeverage("Black Tea")
	{
		switch (teaType)
		{
		case TeaType::Green:
			m_description = "Green Tea";
			break;
		case TeaType::White:
			m_description = "White Tea";
			break;
		case TeaType::Herbal:
			m_description = "Herbal Tea";
			break;
		}
	}

	double GetCost() const override
	{
		return 30;
	}
};

enum class MilkshakeSize
{
	Small,
	Medium,
	Large

};

class CMilkshake : public CBeverage
{
public:
	CMilkshake(MilkshakeSize milkshakeSize = MilkshakeSize::Medium)
		: CBeverage("Medium Milkshake")
		, m_cost(60)
	{
		switch (milkshakeSize)
		{
		case MilkshakeSize::Small:
			m_description = "Small Milkshake";
			m_cost = 50;
			break;
		case MilkshakeSize::Large:
			m_description = "Large Milkshake";
			m_cost = 80;
			break;
		}
	}

	double GetCost() const override
	{
		return m_cost;
	}

private:
	double m_cost;
};
