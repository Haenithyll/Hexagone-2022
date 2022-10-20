#pragma once

#include "Screen.hpp"
#include "Text.hpp"
#include "Button.hpp"
#include "Tilemap.hpp"
#include "Simulation.hpp"

class Main : public Screen
{
	public:
		Main()
		{
			font.loadFromFile("Roboto-Thin.ttf");
		}

		int Run(sw::Window& window)
		{
			Tilemap::getInstance()->InitTilemap();

			Simulation simulation;

			//sw::Rectangle a(50, 50, 50, 50);

			while (window.IsOpen())
			{
				sw::EventsData data = window.HandleEvents();

				if (data.close)
					return -1;

				if (data.IsKeyPressed(sw::Key::Escape))
					return 0;

				window.Clear(sf::Color::Black);

				window.Draw(simulation);

				window.Display();
			}

			return -1;
		}

	private:
		sf::Font font;
};
