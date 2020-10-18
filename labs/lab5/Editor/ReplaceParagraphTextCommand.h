#pragma once
#include "AbstractCommand.h"
#include "IParagraph.h"
class CReplaceParagraphTextCommand : public CAbstractCommand
{
public:
	CReplaceParagraphTextCommand(std::shared_ptr<IParagraph> paragraph, std::string const& newText);

private:
	void DoExecute() override;
	void DoUnexecute() override;

	std::shared_ptr<IParagraph> m_paragraph;
	std::string m_text;
	std::string m_newText;
};
