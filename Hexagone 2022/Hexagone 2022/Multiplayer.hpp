#pragma once
#include "Screen.hpp"
#include "Button.hpp"
#include "Gomoku.hpp"

class Multiplayer : public Screen
{
	public:
		Multiplayer()
		{
			font.loadFromFile("Roboto-Thin.ttf");
		}

		int Run(sw::Window& window)
		{
			int size = 19;
			bool limitless = true;

			sw::Button minus(sf::FloatRect(35, 35, 10, 10), font, "-");
			minus.SetFillColor(sf::Color::Red);

			sw::Button sizeView(sf::FloatRect(50, 35, 15, 15), font, std::to_string(size));
			sizeView.SetFillColor(sf::Color::Black);

			sw::Button plus(sf::FloatRect(65, 35, 10, 10), font, "+");
			plus.SetFillColor(sf::Color::Green);

			sw::Button isLimitless(sf::FloatRect(50, 60, 30, 20), font, "Sans limite");
			isLimitless.SetFillColor(sf::Color::Blue);
			isLimitless.SetTextColor(sf::Color::Black);

			while (window.IsOpen())
			{
				sw::EventsData data = window.HandleEvents();

				if (data.close) return -1;
				else if (data.IsKeyPressed(sw::Key::Escape)) return 0;
				else if (data.IsKeyPressed(sw::Key::Enter)) break;

				if (minus.IsMouseClick() && data.leftClick && size > 6) size -= 2, sizeView.SetText(std::to_string(size));
				else if (plus.IsMouseClick() && data.leftClick) size += 2, sizeView.SetText(std::to_string(size));

				if (isLimitless.IsMouseClick() && data.leftClick)
				{
					limitless = !limitless;
					if (limitless) isLimitless.SetText("Sans Limite"), isLimitless.SetFillColor(sf::Color::Blue);
					else isLimitless.SetText("Avec Limite"), isLimitless.SetFillColor(sf::Color::Magenta);
				}

				window.Clear(sf::Color(220, 179, 92));

				window.Draw(minus);
				window.Draw(sizeView);
				window.Draw(plus);
				window.Draw(isLimitless);

				window.Display();
			}

			gk::Gomoku game;
			game.SetStartSize(size);
			game.SetLimitless(limitless);
			game.Reset();

			sw::View gridView = window.GetDefaultView();
			gridView.SetCenter(game.GetGameBounds().left + game.GetGameBounds().width / 2, game.GetGameBounds().top + game.GetGameBounds().height / 2);
			gridView.SetSize(game.GetGameBounds().width, game.GetGameBounds().height);
			gridView.SetScaleViewport(0.05f, 0.1f, 0.8f, 0.8f);
			gridView.SetMinZoom(5.f / (float)game.GetSize());
			gridView.SetMaxZoom(1.f);
			gridView.SetAutoLock(true);

			sw::Rectangle border(gridView.GetLocalBounds());
			border.SetTransform(sw::TopLeft, sw::Pixel, sw::World);
			border.SetOutline(1.f, sf::Color::Red);
			border.SetFillColor(sf::Color::Transparent);
			
			sw::Button victory(sf::FloatRect(55, 50, 40, 40), font, "");
			victory.SetOrigin(sw::Origin::Left);

			while (window.IsOpen())
			{
				sw::EventsData data = window.HandleEvents();
				
				if (data.close) return -1;
				else if (data.IsKeyPressed(sw::Key::Escape)) return 0;

				window.Clear(sf::Color(220, 179, 92));
				
				if (data.mouseWheelUp) gridView.Zoom(0.95f);
				if (data.mouseWheelDown) gridView.Zoom(1.f / 0.95f);

				if (data.IsKeyDown(sw::Key::Left) || data.IsKeyDown(sw::Key::Q) )
					gridView.Move(-1.f * game.GetSize() / game.GetStartSize() * gridView.GetZoom(), 0.f);
				if (data.IsKeyDown(sw::Key::Right) || data.IsKeyDown(sw::Key::D))
					gridView.Move(1.f * game.GetSize() / game.GetStartSize() * gridView.GetZoom(), 0.f);
				if (data.IsKeyDown(sw::Key::Up) || data.IsKeyDown(sw::Key::Z))
					gridView.Move(0.f, -1.f * game.GetSize() / game.GetStartSize() * gridView.GetZoom());
				if (data.IsKeyDown(sw::Key::Down) || data.IsKeyDown(sw::Key::S))
					gridView.Move(0.f, 1.f * game.GetSize() / game.GetStartSize() * gridView.GetZoom());

				window.SetView(gridView);

				window.Draw(game);

				if (game.IsPlaying())
				{
					if (data.leftClick && game.PlayWhiteAt(window.GetMousePosition(true)) && game.WhitesWon())
					{
						victory.SetFillColor(sf::Color::Black), victory.SetTextColor(sf::Color::White), victory.SetText("White victory !");
						clock.restart();
					}

					if (data.rightClick && game.PlayBlackAt(window.GetMousePosition(true)) && game.BlacksWon())
					{
						victory.SetFillColor(sf::Color::White), victory.SetTextColor(sf::Color::Black), victory.SetText("Black victory !");
						clock.restart();
					}

					gridView.SetSize(game.GetGameBounds().width, game.GetGameBounds().height, true);
				}
				else if (clock.getElapsedTime().asSeconds() > 2)
				{
					game.Reset();

					gridView.SetSize(game.GetGameBounds().width, game.GetGameBounds().height);
				}

				gridView.SetCenter(game.GetGameBounds().left + game.GetGameBounds().width / 2, game.GetGameBounds().top + game.GetGameBounds().height / 2);
				gridView.SetMinZoom(5.f / (float)game.GetSize());

				window.SetView(window.GetDefaultView());

				window.Draw(border);
				if (game.GameWon()) window.Draw(victory);

				window.Display();
			}

			return -1;
		}

	private:
		sf::Font font;
		sf::Clock clock;
};