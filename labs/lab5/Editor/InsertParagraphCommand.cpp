#include "InsertParagraphCommand.h"
#include "Paragraph.h"

CInsertParagraphCommand::CInsertParagraphCommand(std::string const& text, std::vector<CDocumentItem>& items, std::optional<size_t> index)
	: m_text(text)
	, m_items(items)
	, m_index(index)
{
	if (m_index >= m_items.size())
	{
		throw std::invalid_argument("Index cannot be greater than number of elements");
	}
}

void CInsertParagraphCommand::DoExecute()
{
	std::shared_ptr<CParagraph> paragraph = std::make_shared<CParagraph>(m_text);
	CDocumentItem documentItem(paragraph);

	if (m_index)
	{
		m_items.emplace(m_items.begin() + m_index.value(), documentItem);
	}
	else
	{
		m_items.push_back(documentItem);
	}
	//auto index = (m_index) ? (m_items.begin() + m_index.value()) : (m_items.end());
	//m_items.emplace(index, documentItem);
}

void CInsertParagraphCommand::DoUnexecute()
{
	auto index = (m_index) ? (m_items.begin() + m_index.value()) : (--m_items.end());
	m_items.erase(index);
}
