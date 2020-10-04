#pragma once
#include "ICanvas.h"

class CMockCanvas : public ICanvas
{
public:
	void SetColor(Color color) override
	{
		m_color = color;
	}

	void DrawLine(Point const& from, Point const& to) override
	{
		++m_lineCounter;
	}

	void DrawEllipse(Point const& center, double horizontalRadius, double verticalRadius) override
	{
		++m_ellipseCounter;
	}

	int GetLineCounter() const
	{
		return m_lineCounter;
	}

	int GetEllipseCounter() const
	{
		return m_ellipseCounter;
	}

	Color GetColor() const 
	{
		return m_color;
	}

private:
	Color m_color = Color::Black;
	int m_lineCounter = 0;
	int m_ellipseCounter = 0;
};