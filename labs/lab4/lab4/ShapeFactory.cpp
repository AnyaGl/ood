#include "ShapeFactory.h"

std::unique_ptr<CShape> CShapeFactory::CreateShape(std::string const& description) const
{
	throw std::exception("need to write an implementation");
}
