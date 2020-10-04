#pragma once
#include "IShapeFactory.h"

class CShapeFactory : public IShapeFactory
{

public:
	std::unique_ptr<CShape> CreateShape(std::string const& description) const override;
};
