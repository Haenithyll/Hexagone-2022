#pragma once

#include "Screen.hpp"
#include "Text.hpp"
#include "Button.hpp"

class Menu : public Screen
{
	public:
		Menu()
		{
			font.loadFromFile("Roboto-Thin.ttf");
		}

		int Run(sw::Window& window)
		{
			sw::Text title_name = sw::Text(font, "Hexagone", sw::Top);
			title_name.SetPosition(50.f, 20.f);
			title_name.SetSize(27.5f, 30.f);
			title_name.SetFillColor(sf::Color::Black);

			sw::Text title_year = sw::Text(font, "2022", sw::Top);
			title_year.SetParent(&title_name);
			title_year.SetSize(100.f, 100.f);
			title_year.SetPosition(50.f, 125.f);
			title_year.SetFillColor(sf::Color::Black);

			sw::Rectangle blue = sw::Rectangle(sf::FloatRect(0.f, 0.f, 33.333f, 100.f), sw::TopLeft);
			blue.SetFillColor(sf::Color(12, 28, 140));

			sw::Rectangle white = sw::Rectangle(sf::FloatRect(33.333f, 0.f, 33.333f, 100.f), sw::TopLeft);
			white.SetFillColor(sf::Color::White);

			sw::Rectangle red = sw::Rectangle(sf::FloatRect(66.666f, 0.f, 33.333f, 100.f), sw::TopLeft);
			red.SetFillColor(sf::Color(239, 43, 45));

			sw::Text space = sw::Text(font, "Appuyez sur espace pour continuer", sw::Down);
			space.SetPosition(50.f, 80.f);
			space.SetSize(27.5f, 30.f);
			space.SetFillColor(sf::Color::Black);

			bool out = true;

			while (window.IsOpen())
			{
				sw::EventsData data = window.HandleEvents();

				if (data.close || data.IsKeyPressed(sw::Key::Escape))
					return -1;

				if (data.IsKeyPressed(sw::Key::Space))
					return 1;

				return 1;

				float spaceAlpha = space.GetFillColor().a;

				if (out == true && spaceAlpha < 50.f)
					out = false;
				
				if (out == false && spaceAlpha == 255.f)
					out = true;

				if (out)
					space.FadeOut(2.f, window.GetDeltaTime());
				else
					space.FadeIn(2.f, window.GetDeltaTime());

				window.Clear(sf::Color::Black);

				window.Draw(blue);
				window.Draw(white);
				window.Draw(red);

				window.Draw(title_name);
				window.Draw(title_year);

				window.Draw(space);

				window.Display();
			}

			return -1;
		}

	private:
		sf::Font font;
};
