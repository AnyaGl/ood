#pragma once
#include "Shape.h"

class CRectangle : public CShape
{

public:
	CRectangle(Color color, Point const& leftTop, Point const& rightBottom);

	void Draw(ICanvas& canvas) const override;
	Point GetLeftTop() const;
	Point GetRightBottom() const;

private:
	Point m_leftTop;
	Point m_rightBottom;
};
