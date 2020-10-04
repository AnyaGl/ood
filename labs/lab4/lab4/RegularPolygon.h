#pragma once
#include "Shape.h"

class CRegularPolygon : public CShape
{

public:
	CRegularPolygon(Color color, size_t vertexCount, Point const& center, double radius);

	void Draw(ICanvas& canvas) const override;
	size_t GetVertexCount() const;
	Point GetCenter() const;
	double GetRadius() const;

private:
	size_t m_vertexCount;
	Point m_center;
	double m_radius;
};
