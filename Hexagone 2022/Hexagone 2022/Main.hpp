#pragma once

#include "Screen.hpp"
#include "Text.hpp"
#include "Button.hpp"
#include "Tilemap.hpp"

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

			sw::Rectangle a(0, 0, 50, 50, sw::Center, sw::World, sw::Pixel);
			sw::View gridView = window.GetDefaultView();

			gridView.SetCenter(0, 0);
			gridView.SetSize(150, 150);
			gridView.SetScaleViewport(0.05f, 0.1f, 0.8f, 0.8f);
			gridView.SetMinZoom(5.f / 150.f);
			gridView.SetMaxZoom(1.f);
			gridView.SetAutoLock(true);

			while (window.IsOpen())
			{
				sw::EventsData data = window.HandleEvents();

				if (data.close)
					return -1;

				if (data.IsKeyPressed(sw::Key::Escape))
					return 0;

				if (data.mouseWheelUp) gridView.Zoom(0.95f);
				if (data.mouseWheelDown) gridView.Zoom(1.f / 0.95f);

				if (data.IsKeyDown(sw::Key::Left) || data.IsKeyDown(sw::Key::Q))
					gridView.Move(-1.f * gridView.GetZoom(), 0.f);
				if (data.IsKeyDown(sw::Key::Right) || data.IsKeyDown(sw::Key::D))
					gridView.Move(1.f * gridView.GetZoom(), 0.f);
				if (data.IsKeyDown(sw::Key::Up) || data.IsKeyDown(sw::Key::Z))
					gridView.Move(0.f, -1.f * gridView.GetZoom());
				if (data.IsKeyDown(sw::Key::Down) || data.IsKeyDown(sw::Key::S))
					gridView.Move(0.f, 1.f * gridView.GetZoom());

				window.SetView(gridView);

				window.Clear(sf::Color::Black);

				window.Draw(a);

				window.Display();
			}

			return -1;
		}

	private:
		sf::Font font;
};
