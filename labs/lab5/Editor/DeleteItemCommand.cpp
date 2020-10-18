#include "DeleteItemCommand.h"
#include <filesystem>
#include "Paragraph.h"

CDeleteItemCommand::CDeleteItemCommand(std::vector<CDocumentItem>& items, size_t index)
	: m_items(items)
	, m_index(index)
	, m_item(CDocumentItem(std::make_shared<CParagraph>("")))
{
	if (m_index >= m_items.size())
	{
		throw std::invalid_argument("Index cannot be greater than number of elements");
	}
	m_item = CDocumentItem(m_items.at(index));
}

CDeleteItemCommand::~CDeleteItemCommand()
{
	try
	{
		auto image = m_item.GetImage();
		if (IsExecuted() && image)
		{
			std::filesystem::remove(image->GetPath());
		}
	}
	catch (...)
	{
	}
}

void CDeleteItemCommand::DoExecute()
{
	m_items.erase(m_items.begin() + m_index);
}

void CDeleteItemCommand::DoUnexecute()
{
	m_items.emplace(m_items.begin() + m_index, m_item);
}
