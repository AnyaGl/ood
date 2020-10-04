#include "Canvas.h"
#include "Designer.h"
#include "Painter.h"
#include "ShapeFactory.h"
#include <iostream>

const int WINDOW_WIDTH = 800;
const int WINDOW_HEIGHT = 600;

int main()
{

	std::cout << "Use:\n"
				 "rectangle <color> <left top vertex> <width> <height>\n"
				 "triangle <color> <vertex 1> <vertex 2> <vertex3>\n"
				 "ellipse <color> <center point> <horizontal radius> <vertical radius>\n"
				 "regularPolygon <color> <vertexe count> <center point> <radius>\n"
				 "to stop enter shapes write \"exit\"\n\n";

	CShapeFactory factory;
	CDesigner desinger(factory);
	CPictureDraft draft;

	draft = desinger.CreateDraft(std::cin);

	std::cout << "Do you want to draw draft? y/n" << std::endl;
	std::string answer;
	std::cin >> answer;

	if (answer == "y")
	{
		sf::RenderWindow window(sf::VideoMode(WINDOW_WIDTH, WINDOW_HEIGHT), "Shapes");
		CCanvas canvas(window);

		CPainter painter;

		while (window.isOpen())
		{
			sf::Event event;
			while (window.pollEvent(event))
			{
				if (event.type == sf::Event::Closed)
				{
					window.close();				
				}
			}

			window.clear(sf::Color::White);
			painter.DrawPicture(draft, canvas);
			window.display();
		}
	}

	return 0;
}