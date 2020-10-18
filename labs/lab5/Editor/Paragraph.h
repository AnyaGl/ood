#pragma once
#include "IParagraph.h"
class CParagraph : public IParagraph
{
public:
	CParagraph(std::string const& text);

	std::string GetText() const override;
	void SetText(std::string const& text) override;

private:
	std::string m_text;
};
