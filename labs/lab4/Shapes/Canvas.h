#pragma once
#include "ICanvas.h"
#include "Color.h"

class CCanvas : public ICanvas
{

public:
	void SetColor(Color color) override;
	void DrawLine(Point const& from, Point const& to) override;
	void DrawEllipse(Point const& center, double horizontalRadius, double verticalRadius) override;

private:
	Color m_color;
};
