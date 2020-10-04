#include "Designer.h"

CDesigner::CDesigner(IShapeFactory& factory)
	: m_factory(factory)
{
}

CPictureDraft CDesigner::CreateDraft(std::istream& stream) const
{
	return CPictureDraft{};
}
