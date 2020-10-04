#include "PictureDraft.h"

size_t CPictureDraft::GetShapeCount() const
{
	return m_shapes.size();
}

CShape& CPictureDraft::GetShape(size_t index) const
{
	throw std::exception("need to write an implementation");
}

void CPictureDraft::AddShape(std::unique_ptr<CShape>&& shape)
{
}
