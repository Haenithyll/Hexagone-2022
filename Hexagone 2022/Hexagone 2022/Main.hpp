#pragma once

#include "Screen.hpp"
#include "Text.hpp"
#include "Button.hpp"
#include "Tilemap.hpp"
#include "Simulation.hpp"
#include "Log.hpp"

#include "imgui/imgui.h"
#include "imgui/imgui-SFML.h"

class Main : public Screen
{
	public:
		Main()
		{
			font.loadFromFile("Roboto-Thin.ttf");
		}

		int Run(sw::Window& window)
		{
			Tilemap::Init(3);
			Log::Init();

			Simulation simulation;

			simulation.Reset();

			sw::View gridView = window.GetDefaultView();
			
			sf::Vector2f scale = gridView.SetScaleViewport(0.f, 0.f, 1.f, 1.f);
			
			gridView.SetCenter(simulation.GetGlobalBounds().left, simulation.GetGlobalBounds().top);
			gridView.SetSize(simulation.GetGlobalBounds().width, simulation.GetGlobalBounds().height);
			
			gridView.SetMinZoom(5.f / 150.f);
			gridView.SetMaxZoom(1.f);
			gridView.SetAutoLock(true);

			sf::Rect frame = gridView.GetLocalBounds();

			frame.left += 5.f;
			frame.top += 5.f;

			frame.width -= 10.f;
			frame.height -= 10.f;

			sw::Button gameFrame(frame);
			gameFrame.SetOrigin(sw::TopLeft);
			gameFrame.SetUnit(sw::Pixel);

			frame.left += frame.width;
			frame.width = window.GetSize().x - frame.width;

			gameFrame.SetOutline(5.f, sf::Color(56, 56, 56));
			gameFrame.SetFillColor(sf::Color::Transparent);

			frame.width -= 10.f;

			sw::Rectangle infoFrame(frame, sw::TopLeft, sw::Parent, sw::Pixel);

			infoFrame.SetOutline(5.f, sf::Color(56, 56, 56));
			infoFrame.SetFillColor(sf::Color::Transparent);

			sw::Text frameText(font, "", sw::Left);
			frameText.SetParent(&infoFrame);
			frameText.SetSize(100.f, 2.5f);
			frameText.SetPosition(5.f, 2.5f);

			sw::Text roundText(font, "", sw::Left);
			roundText.SetParent(&infoFrame);
			roundText.SetSize(100.f, 2.5f);
			roundText.SetPosition(5.f, 7.5f);

			int nFrame = 0;

			while (window.IsOpen())
			{
				window.ResetView();

				sw::EventsData data = window.HandleEvents();

				if (data.close)
					return -1;

				if (data.IsKeyPressed(sw::Key::Escape))
					return 0;

				if (gameFrame.IsMouseHover())
				{
					if (data.mouseWheelUp)
						gridView.Zoom(0.95f);

					if (data.mouseWheelDown)
						gridView.Zoom(1.f / 0.95f);
				}

				if (data.IsKeyDown(sw::Key::Left) || data.IsKeyDown(sw::Key::Q))
					gridView.Move(-1.f * 10.f * gridView.GetZoom(), 0.f);

				if (data.IsKeyDown(sw::Key::Right) || data.IsKeyDown(sw::Key::D))
					gridView.Move(1.f * 10.f * gridView.GetZoom(), 0.f);

				if (data.IsKeyDown(sw::Key::Up) || data.IsKeyDown(sw::Key::Z))
					gridView.Move(0.f, -1.f * 10.f * gridView.GetZoom());

				if (data.IsKeyDown(sw::Key::Down) || data.IsKeyDown(sw::Key::S))
					gridView.Move(0.f, 1.f * 10.f * gridView.GetZoom());

				window.SetView(gridView);

				window.Clear(sf::Color::Black);

				window.Draw(simulation);

				window.ResetView();

				if (nFrame % 100 == 0)
					simulation.Update(), Log::Print("fdp");

				ImGui::Begin("Console");

				for (const std::string& message : Log::GetMessages())
					ImGui::Text(message.c_str());

				ImGui::SetScrollHereY(1.f);

				ImGui::End();

				ImGui::Begin("Infos");

				ImGui::Button("agrougrou");

				ImGui::End();

				window.Display();

				++nFrame;
			}

			return -1;
		}

	private:
		sf::Font font;
};
