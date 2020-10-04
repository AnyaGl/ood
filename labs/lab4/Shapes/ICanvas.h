#pragma once
#include "Color.h"
#include "Point.h"

class ICanvas
{
public:
	virtual void SetColor(Color color) = 0;
	virtual void DrawLine(Point const& from, Point const& to) = 0;
	virtual void DrawEllipse(Point const& center, size_t horizontalRadius, size_t verticalRadius) = 0;

	virtual ~ICanvas() = default;
};
