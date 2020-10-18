#pragma once
#include "IImage.h"

class CImage : public IImage
{
public:
	CImage(Path const& path, int width, int height);

	Path GetPath() const override;
	int GetWidth() const override;
	int GetHeight() const override;

	void Resize(int width, int height) override;

private:
	static bool IsImage(Path const& path);

	Path m_path;
	int m_width;
	int m_height;
};
