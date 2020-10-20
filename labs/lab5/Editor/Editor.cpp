#include "Editor.h"
#include "Document.h"
#include <functional>
#include <iostream>

using namespace std::placeholders;

CEditor::CEditor()
	: m_document(std::make_unique<CDocument>())
{
	m_menu.AddItem("help", "Help", [this](std::istream&) { m_menu.ShowInstructions(); });
	m_menu.AddItem("exit", "Exit", [this](std::istream&) { m_menu.Exit(); });
	m_menu.AddItem("insertParagraph", "Inserting paragraph. Args: <position>|end <text>", std::bind(&CEditor::InsertParagraph, this, _1));
	m_menu.AddItem("insertImage", "Inserting image. Args: <position>|end <width> <height> <path>", std::bind(&CEditor::InsertImage, this, _1));
	m_menu.AddItem("setTitle", "Changes title. Args: <new title>", std::bind(&CEditor::SetTitle, this, _1));
	m_menu.AddItem("list", "Show document", std::bind(&CEditor::List, this, _1));
	m_menu.AddItem("replaceText", "Replace paragraph text. Args: <position> <text>", std::bind(&CEditor::ReplaceText, this, _1));
	m_menu.AddItem("resizeImage", "Resize image. Args: <position> <width> <height>", std::bind(&CEditor::ResizeImage, this, _1));
	m_menu.AddItem("deleteItem", "Delete item. Args: <position>", std::bind(&CEditor::DeleteItem, this, _1));
	m_menu.AddItem("undo", "Undo command", std::bind(&CEditor::Undo, this, _1));
	m_menu.AddItem("redo", "Redo undone command", std::bind(&CEditor::Redo, this, _1));
	m_menu.AddItem("save", "Save to HTML file. Args: <path>", std::bind(&CEditor::Save, this, _1));
}

void CEditor::Run()
{
	m_menu.Run();
}

void CEditor::InsertParagraph(std::istream& in)
{
	std::string positionStr;
	std::string text;

	if (!(in >> positionStr) || !getline(in, text))
	{
		std::cout << "invalid arguments" << std::endl;
		return;
	}
	text.erase(text.begin());	

	std::optional<size_t> position = std::nullopt;
	try
	{
		if (positionStr != "end")
		{
			position = std::stoi(positionStr);
		}
		m_document->InsertParagraph(text, position);
	}
	catch (const std::exception& e)
	{
		std::cout << e.what() << std::endl;
	}
}

void CEditor::InsertImage(std::istream& in)
{
	std::string positionStr;
	int width = 0;
	int height = 0;
	std::string path;

	if (!((in >> positionStr) && (in >> width) && (in >> height) && (in >> path)))
	{
		std::cout << "invalid arguments" << std::endl;
		return;
	}

	std::optional<size_t> position = std::nullopt;
	try
	{
		if (positionStr != "end")
		{
			position = stoi(positionStr);
		}
		m_document->InsertImage(path, width, height, position);
	}
	catch (const std::exception& e)
	{
		std::cout << e.what() << std::endl;
	}
}

void CEditor::SetTitle(std::istream& in)
{
	std::string title;
	std::getline(in, title);
	m_document->SetTitle(title);
}

void CEditor::List(std::istream&)
{
	std::cout << "  Title: " << m_document->GetTitle() << std::endl;

	for (size_t i = 0; i < m_document->GetItemsCount(); i++)
	{
		std::cout << " \t" << i << ". ";
		auto item = m_document->GetItem(i);
		if (auto paragraph = item.GetParagraph())
		{
			std::cout << "Paragraph: " << paragraph->GetText() << std::endl;
		}
		if (auto image = item.GetImage())
		{
			std::cout << "Image: " << image->GetWidth() << " " << image->GetHeight() << " " << image->GetPath() << std::endl;
		}
	}
}

void CEditor::ReplaceText(std::istream& in)
{
	size_t position;
	std::string text;

	if (!(in >> position) || !getline(in, text))
	{
		std::cout << "invalid arguments" << std::endl;
		return;
	}

	try
	{
		m_document->ReplaceParagraphText(position, text);
	}
	catch (const std::exception& e)
	{
		std::cout << e.what() << std::endl;
	}
}

void CEditor::ResizeImage(std::istream& in)
{
	size_t position;
	int width;
	int height;

	if (!((in >> position) && (in >> width) && (in >> height)))
	{
		std::cout << "invalid arguments" << std::endl;
		return;
	}

	try
	{
		m_document->ResizeImage(position, width, height);
	}
	catch (const std::exception& e)
	{
		std::cout << e.what() << std::endl;
	}
}

void CEditor::DeleteItem(std::istream& in)
{
	size_t position;

	if (!(in >> position))
	{
		std::cout << "invalid arguments" << std::endl;
		return;
	}

	try
	{
		m_document->DeleteItem(position);
	}
	catch (const std::exception& e)
	{
		std::cout << e.what() << std::endl;
	}
}

void CEditor::Undo(std::istream&)
{
	if (m_document->CanUndo())
	{
		m_document->Undo();
	}
	else
	{
		std::cout << "Can't undo" << std::endl;
	}
}

void CEditor::Redo(std::istream&)
{
	if (m_document->CanRedo())
	{
		m_document->Redo();
	}
	else
	{
		std::cout << "Can't redo" << std::endl;
	}
}

void CEditor::Save(std::istream& in)
{
	std::string path;
	in >> path;
	m_document->Save(path);
}