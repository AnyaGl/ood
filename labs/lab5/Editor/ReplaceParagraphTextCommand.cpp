#include "ReplaceParagraphTextCommand.h"

CReplaceParagraphTextCommand::CReplaceParagraphTextCommand(std::shared_ptr<IParagraph> paragraph, std::string const& newText)
	: m_paragraph(paragraph)
	, m_newText(newText)
{
	m_text = m_paragraph->GetText();
}

void CReplaceParagraphTextCommand::DoExecute()
{
	m_paragraph->SetText(m_newText);
}

void CReplaceParagraphTextCommand::DoUnexecute()
{
	m_paragraph->SetText(m_text);
}
