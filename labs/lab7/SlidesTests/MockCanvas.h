#pragma once
#include "../Slides/ICanvas.h"
#include <iomanip>
#include <sstream>

namespace
{
std::string ToString(PointD const& point)
{
	std::stringstream ss;
	ss << "(" << point.x << ", " << point.y << ")";
	return ss.str();
}
} // namespace

class MockCanvas : public ICanvas
{
public:
	MockCanvas(std::ostream& out)
		: m_out(out)
	{
	}
	void SetLineColor(RGBAColor color) override
	{
		std::stringstream ss;
		ss << std::hex << std::setfill('0') << std::setw(8) << color;
		m_out << "SetLineColor #" << ss.str() << "\n";
	}
	void SetFillColor(RGBAColor color) override
	{
		std::stringstream ss;
		ss << std::hex << std::setfill('0') << std::setw(8) << color;
		m_out << "SetFillColor #" << ss.str() << "\n";
	}
	void SetLineThickness(double thickness) override
	{
		m_out << "SetLineThickness " << thickness << "\n";
	}
	void DrawLine(PointD const& from, PointD const& to) override
	{
		m_out << "DrawLine from " << ToString(from) << " to " << ToString(to) << "\n";
	}
	void FillPolygon(std::vector<PointD> const& vertexes) override
	{
		m_out << "FillPolygon with vertexes:\n";
		for (auto vertex : vertexes)
		{
			m_out << "\t" << ToString(vertex) << "\n";
		}
	}
	void DrawEllipse(double left, double top, double width, double height) override
	{
		m_out << "DrawEllipse left: " << left
			  << "; top: " << top
			  << "; width: " << width
			  << "; height: " << height << "\n";
	}
	void FillEllipse(double left, double top, double width, double height) override
	{
		m_out << "FillEllipse left: " << left
			  << "; top: " << top
			  << "; width: " << width
			  << "; height: " << height << "\n";
	}

private:
	std::ostream& m_out;
};