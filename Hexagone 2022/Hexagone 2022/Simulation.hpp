#pragma once

#include "Screen.hpp"
#include "Text.hpp"
#include "Button.hpp"

class Simulation : public Screen
{
public:
	Simulation()
	{
		font.loadFromFile("Roboto-Thin.ttf");
	}

	int Run(sw::Window& window)
	{
		while (window.IsOpen())
		{
			sw::EventsData data = window.HandleEvents();

			if (data.close)
				return -1;

			if (data.IsKeyPressed(sw::Key::Escape))
				return 0;

			window.Clear(sf::Color::Black);

			window.Display();
		}

		return -1;
	}

private:
	sf::Font font;
};
