#include "Image.h"

const std::string JPG = ".jpg";
const std::string PNG = ".png";
const std::string SVG = ".svg";

CImage::CImage(Path const& path, int width, int height)
{
	if (!IsImage(path))
	{
		throw std::invalid_argument("no image selected");
	}
	if (width < 1 || height < 1 || width > 10000 || height > 10000)
	{
		throw std::invalid_argument("image size must be in [1; 10000]");
	}
	m_path = path;
	m_width = width;
	m_height = height;
}

Path CImage::GetPath() const
{
	return m_path;
}

int CImage::GetWidth() const
{
	return m_width;
}

int CImage::GetHeight() const
{
	return m_height;
}

void CImage::Resize(int width, int height)
{
	if (width < 0 || height < 0)
	{
		throw std::invalid_argument("image size cannot be negative");
	}
	m_width = width;
	m_height = height;
}

bool CImage::IsImage(Path const& path)
{
	auto extension = path.extension();
	if (extension == JPG || extension == PNG || extension == SVG)
	{
		return true;
	}
	return false;
}
