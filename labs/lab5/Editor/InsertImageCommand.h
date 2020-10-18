#pragma once
#include "AbstractCommand.h"
#include "DocumentItem.h"
#include "Path.h"
#include <optional>
#include <vector>

class CInsertImageCommand : public CAbstractCommand
{
public:
	CInsertImageCommand(int width, int height, Path const& sourcePath, Path const& distPath, std::vector<CDocumentItem>& items, std::optional<size_t> index = std::nullopt);
	~CInsertImageCommand();

private:
	void DoExecute() override;
	void DoUnexecute() override;

	std::shared_ptr<IImage> SaveImage(int width, int height, Path const& sourcePath, Path const& distPath) const;

	std::vector<CDocumentItem>& m_items;
	std::optional<size_t> m_index;
	std::shared_ptr<IImage> m_image;
};
