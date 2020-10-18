#pragma once
#include "AbstractCommand.h"
#include "IImage.h"
class CResizeImageCommand : public CAbstractCommand
{
public:
	CResizeImageCommand(std::shared_ptr<IImage> image, int width, int height);

private:
	void DoExecute() override;
	void DoUnexecute() override;

	std::shared_ptr<IImage> m_image;
	int m_width;
	int m_newWidth;
	int m_height;
	int m_newHeight;
};
