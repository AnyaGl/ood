#include "InsertImageCommand.h"
#include "Image.h"

CInsertImageCommand::CInsertImageCommand(int width, int height, Path const& sourcePath, Path const& distPath, std::vector<CDocumentItem>& items, std::optional<size_t> index)
	: m_items(items)
	, m_index(index)
{
	if (m_index >= m_items.size())
	{
		throw std::invalid_argument("Index cannot be greater than number of elements");
	}

	m_image = SaveImage(width, height, sourcePath, distPath);
}

CInsertImageCommand::~CInsertImageCommand()
{
	if (!IsExecuted())
	{
		Path filePath = m_image->GetPath();
		std::filesystem::remove(filePath);
	}
}

void CInsertImageCommand::DoExecute()
{
	auto index = (m_index) ? (m_items.begin() + m_index.value()) : (m_items.end());
	m_items.emplace(index, m_image);
}

void CInsertImageCommand::DoUnexecute()
{
	auto index = (m_index) ? (m_items.begin() + m_index.value()) : (--m_items.end());
	m_items.erase(index);
}

std::shared_ptr<IImage> CInsertImageCommand::SaveImage(int width, int height, Path const& sourcePath, Path const& distPath) const
{
	if (!std::filesystem::exists(sourcePath))
	{
		throw std::invalid_argument("invalid image path");
	}

	std::string newFileName = std::to_string(std::time(nullptr));
	std::string resultPath = distPath.string() + "/" + newFileName + sourcePath.extension().string();
	auto image = std::make_shared<CImage>(resultPath, width, height);

	if (!std::filesystem::is_directory(distPath))
	{
		std::filesystem::create_directory(distPath);
	}
	
	std::filesystem::copy_file(sourcePath, resultPath);

	return image;
}
