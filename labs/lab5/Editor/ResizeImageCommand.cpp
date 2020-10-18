#include "ResizeImageCommand.h"

CResizeImageCommand::CResizeImageCommand(std::shared_ptr<IImage> image, int width, int height)
	: m_image(image)
	, m_newWidth(width)
	, m_newHeight(height)
{
	m_width = image->GetWidth();
	m_height = image->GetHeight();
}

void CResizeImageCommand::DoExecute()
{
	m_image->Resize(m_newWidth, m_newHeight);
}

void CResizeImageCommand::DoUnexecute()
{
	m_image->Resize(m_width, m_height);
}
