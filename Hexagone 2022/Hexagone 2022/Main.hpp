#pragma once

#include "Screen.hpp"
#include "Text.hpp"
#include "Button.hpp"
#include "Tilemap.hpp"
#include "BasicSimulation.hpp"
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
			Tilemap::Init(5);

			Log::Init();

			Simulation* simulation = new BasicSimulation();

			#pragma region View

			sw::View gridView = window.GetDefaultView();

			gridView.SetScaleViewport(0.f, 0.f, 1.f, 1.f);

			gridView.SetCenter(simulation->GetGlobalBounds().left, simulation->GetGlobalBounds().top);
			gridView.SetSize(simulation->GetGlobalBounds().width, simulation->GetGlobalBounds().height);

			gridView.SetMinZoom(5.f / 150.f);
			gridView.SetMaxZoom(1.f);
			gridView.SetAutoLock(true);

			#pragma endregion

			sf::Clock timer;

			bool isPlaying = false;

			int turn = 0;
			float period = 1.f;

			simulation->Reset();

			while (window.IsOpen())
			{
				sw::EventsData data = window.HandleEvents();

				if (data.close)
					return -1;

				if (data.IsKeyPressed(sw::Key::Escape))
					return 0;

				#pragma region Camera

				if (data.mouseWheelUp)
					gridView.Zoom(0.95f);

				if (data.mouseWheelDown)
					gridView.Zoom(1.f / 0.95f);

				if (data.IsKeyDown(sw::Key::Left) || data.IsKeyDown(sw::Key::Q))
					gridView.Move(-1.f * 10.f * gridView.GetZoom(), 0.f);

				if (data.IsKeyDown(sw::Key::Right) || data.IsKeyDown(sw::Key::D))
					gridView.Move(1.f * 10.f * gridView.GetZoom(), 0.f);

				if (data.IsKeyDown(sw::Key::Up) || data.IsKeyDown(sw::Key::Z))
					gridView.Move(0.f, -1.f * 10.f * gridView.GetZoom());

				if (data.IsKeyDown(sw::Key::Down) || data.IsKeyDown(sw::Key::S))
					gridView.Move(0.f, 1.f * 10.f * gridView.GetZoom());

				#pragma endregion

				#pragma region Simulation

				ImGui::Begin("Simulation", nullptr, ImGuiWindowFlags_AlwaysAutoResize);

				if (ImGui::Button(isPlaying ? "Pause" : "Play"))
				{
					isPlaying = !isPlaying;

					if (isPlaying)
						timer.restart();
				}

				ImGui::SameLine();

				if (ImGui::Button("Reset"))
				{
					isPlaying = false;
					turn = 0;

					simulation->Reset();
				}

				ImGui::Spacing();

				if (ImGui::Button("Update"))
				{
					isPlaying = false;

					simulation->Update();
				}

				ImGui::SameLine();

				if (ImGui::Button("EndTurn"))
				{
					isPlaying = false;

					simulation->EndTurn();
				}

				ImGui::Spacing();

				ImGui::SliderFloat("Period", &period, 0.01f, 5.f);

				ImGui::Spacing();

				ImGui::Text("Pas %i / %i", simulation->GetIndex() + 1, simulation->GetCount());

				ImGui::Text("Tour %i", simulation->GetTurn() + 1);

				ImGui::End();

				#pragma endregion

				if (isPlaying && timer.getElapsedTime().asSeconds() >= period)
				{
					simulation->Update();

					timer.restart();

					++turn;
				}

				#pragma region Console

				ImGui::Begin("Console");

				for (const std::string& message : Log::GetMessages())
					ImGui::Text(message.c_str());

				ImGui::SetScrollHereY(1.f);

				ImGui::End();

				#pragma endregion

				#pragma region Draw

				window.Clear(sf::Color::Black);

				window.SetView(gridView);

				window.Draw(*simulation);

				window.ResetView();

				window.Display();

				#pragma endregion
			}

			return -1;
		}

	private:
		sf::Font font;
};
