#include "Designer.h"
#include <iostream>

CDesigner::CDesigner(IShapeFactory& factory)
	: m_factory(factory)
{
}

CPictureDraft CDesigner::CreateDraft(std::istream& stream) const
{
	CPictureDraft draft;
	std::string line;

	while (std::getline(stream, line))
	{
		if (line == "exit")
		{
			break;
		}
		draft.AddShape(m_factory.CreateShape(line));
	}

	return draft;
}
