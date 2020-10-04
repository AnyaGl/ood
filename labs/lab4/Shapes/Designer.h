#pragma once
#include "IDesigner.h"

class CDesigner : public IDesigner
{

public:
	CPictureDraft CreateDraft(std::istream& stream) const override;
};
