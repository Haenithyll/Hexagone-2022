#pragma once
#include "Screen.hpp"
#include "Button.hpp"

class Hub : public Screen
{
	public:
		Hub()
		{
			font.loadFromFile("Roboto-Thin.ttf");
		}

		int Run(sw::Window& window)
		{
			sw::Text title = sw::Text(font, "Gomoku", sw::Origin::Top);
			title.SetPosition(50, 5);
			title.SetSize(60, 30);
			title.SetFillColor(sf::Color::Black);

			sw::Button multiplayer = sw::Button(sf::FloatRect(50, 55, 40, 15), font, "Multiplayer");
			multiplayer.SetTextColor(sf::Color::Black);
			multiplayer.SetFillColor(sf::Color(255, 255, 255, 100));

			sw::Button lan = sw::Button(sf::FloatRect(50, 80, 40, 15), font, "Multiplayer lan");
			lan.SetTextColor(sf::Color::Black);
			lan.SetFillColor(sf::Color(255, 255, 255, 100));

			while (window.IsOpen())
			{
				sw::EventsData data = window.HandleEvents();

				if (data.close || data.IsKeyPressed(sw::Key::Escape)) return -1;
				else if (multiplayer.IsMouseClick()) return 1;
				else if (lan.IsMouseClick()) return 2;

				window.Clear(sf::Color(220, 179, 92));

				if (multiplayer.IsMouseHover()) multiplayer.SetFillColor(sf::Color(255, 255, 255, 200));
				else multiplayer.SetFillColor(sf::Color(255, 255, 255, 100));

				if (lan.IsMouseHover()) lan.SetFillColor(sf::Color(255, 255, 255, 200));
				else lan.SetFillColor(sf::Color(255, 255, 255, 100));

				window.Draw(title);
				window.Draw(multiplayer);
				window.Draw(lan);

				window.Display();
			}

			return -1;
		}

	private:
		sf::Font font;
};