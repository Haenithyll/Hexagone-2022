#pragma once

#include "Screen.hpp"
#include "Text.hpp"
#include "Button.hpp"
#include "Tilemap.hpp"
#include "BasicSimulation.hpp"
#include "Log.hpp"

#include "imgui/imgui.h"
#include "imgui/imgui-SFML.h"

#include "PseudoRandom.hpp"

class Main : public Screen
{
	public:
		Main()
		{
			font.loadFromFile("Roboto-Thin.ttf");
		}

		int Run(sw::Window& window)
		{
			Log::Init();

			Simulation* simulation = new BasicSimulation(7, &Tilemap::FlowerPattern);

			#pragma region View

			sw::View gridView = window.GetDefaultView();

			gridView.SetScaleViewport(0.f, 0.f, 1.f, 1.f);

			gridView.SetCenter(simulation->GetGlobalBounds().left, simulation->GetGlobalBounds().top);
			gridView.SetSize(simulation->GetGlobalBounds().width, simulation->GetGlobalBounds().height);

			gridView.SetMinZoom(5.f / 25.f);
			gridView.SetMaxZoom(1.f);
			gridView.SetAutoLock(true);

			#pragma endregion

			sf::Clock timer;

			bool isPlaying = false;

			float period = 1.f;

			simulation->Reset();


			PseudoRandom::ResetSeed(); // The seed reset is here

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

					const int nbParti = 4;
					int order[4] = { 0 };

					PseudoRandom::GetOrder(nbParti, order);
					std::string orderString;
					for (short i = 0; i < nbParti; i++) {
						orderString += std::to_string(order[i]);
					}
					Log::Print("RandomOrd : " + orderString);

					Log::Print("RandomTyp : " + std::to_string(PseudoRandom::GetObstacleType(4)));

					Log::Print("RandomInt : " + std::to_string(PseudoRandom::GetInt(-Tilemap::Radius(), Tilemap::Radius())));

					sf::Vector3i position = PseudoRandom::GetPosition(Tilemap::Radius()); // Change the radius here
					Log::Print("RandomPos : " + std::to_string(position.x) + " " + std::to_string(position.y) + " " + std::to_string(position.z));

					sf::Vector3i direction = PseudoRandom::GetDirection();
					Log::Print("RandomDir : " + std::to_string(direction.x) + " " + std::to_string(direction.y) + " " + std::to_string(direction.z));

					isPlaying = false;

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
