#include "RegularPolygon.h"

CRegularPolygon::CRegularPolygon(Color color, size_t vertexCount, Point const& center, double radius)
	: CShape(color)
	, m_vertexCount(vertexCount)
	, m_center(center)
	, m_radius(radius)
{
}

void CRegularPolygon::Draw(ICanvas& canvas) const
{
}

size_t CRegularPolygon::GetVertexCount() const
{
	return m_vertexCount;
}

Point CRegularPolygon::GetCenter() const
{
	return m_center;
}

double CRegularPolygon::GetRadius() const
{
	return m_radius;
}
