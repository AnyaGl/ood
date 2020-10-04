#include "Rectangle.h"

CRectangle::CRectangle(Color color, Point const& leftTop, double width, double height)
	: CShape(color)
	, m_leftTop(leftTop)
	, m_width(width)
	, m_height(height)
{
}

void CRectangle::Draw(ICanvas& canvas) const
{
}

Point CRectangle::GetLeftTop() const
{
	return m_leftTop;
}

Point CRectangle::GetRightBottom() const
{
	return { m_leftTop.x + m_width, m_leftTop.y - m_height };
}
