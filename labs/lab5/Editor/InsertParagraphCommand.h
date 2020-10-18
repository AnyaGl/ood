#pragma once
#include "AbstractCommand.h"
#include "DocumentItem.h"
#include <optional>

class CInsertParagraphCommand : public CAbstractCommand
{
public:
	CInsertParagraphCommand(std::string const& text, std::vector<CDocumentItem>& items, std::optional<size_t> index = std::nullopt);

private:
	void DoExecute() override;
	void DoUnexecute() override;

	std::string m_text;
	std::vector<CDocumentItem>& m_items;
	std::optional<size_t> m_index;
};
