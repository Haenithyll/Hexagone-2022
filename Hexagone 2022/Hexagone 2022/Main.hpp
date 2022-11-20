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

#include "BenjaminVouallion.hpp"
#include "JeanneOskour.hpp"
#include "JosephRepublique.hpp"
#include "MerlinPimpain.hpp"

class Main : public Screen
{
	public:
		int Run(sw::Window& window)
		{
			PseudoRandom::ResetSeed();

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

			bool gameOver = false;

			simulation->Reset();

			while (window.IsOpen())
			{
				sw::EventsData data = window.HandleEvents();

				if (data.close)
					return -1;

				if (data.IsKeyPressed(sw::Key::Escape))
					return 0;

				gameOver = simulation->Over();

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

				if (!gameOver)
				{
					if (ImGui::Button(isPlaying ? "Pause" : "Play"))
					{
						isPlaying = !isPlaying;

						if (isPlaying)
							timer.restart();
					}

					ImGui::SameLine();
				}

				if (ImGui::Button("Reset"))
				{
					isPlaying = false;
					simulation->Reset();
				}

				if (!gameOver)
				{
					ImGui::Spacing();

					if (ImGui::Button("Update"))
					{
						isPlaying = false;

						simulation->Step(period);
					}

					ImGui::SameLine();

					if (ImGui::Button("EndTurn"))
					{
						isPlaying = false;

						simulation->EndTurn();
					}

					ImGui::Spacing();

					ImGui::SliderFloat("Period", &period, 1.f, 5.f);
				}

				ImGui::Spacing();

				ImGui::Text("Pas %i / %i", simulation->GetIndex() + 1, simulation->GetCount());

				ImGui::Text("Tour %i", simulation->GetTurn() + 1);

				ImGui::End();

				#pragma endregion

				#pragma region Debug

				Messages messages = BenjaminVouallion::GetInstance()->GetMessages();

				ImGui::Begin("Benjamin Vouallion");

				ImGui::Text("Messages (%i / %i) :", messages.size(), BenjaminVouallion::GetInstance()->GetTotalMessagesCount());

				for (const std::string* message : messages)
					ImGui::Text(message->c_str());

				ImGui::End();
				
				messages = JosephRepublique::GetInstance()->GetMessages();

				ImGui::Begin("Joseph Republique");

				ImGui::Text("Messages (%i / %i) :", messages.size(), JosephRepublique::GetInstance()->GetTotalMessagesCount());

				for (const std::string* message : messages)
					ImGui::Text(message->c_str());

				ImGui::End();

				messages = MerlinPimpain::GetInstance()->GetMessages();

				ImGui::Begin("Merlin Pimpain");

				ImGui::Text("Messages (%i / %i) :", messages.size(), MerlinPimpain::GetInstance()->GetTotalMessagesCount());

				for (const std::string* message : messages)
					ImGui::Text(message->c_str());

				ImGui::End();

				messages = JeanneOskour::GetInstance()->GetMessages();

				ImGui::Begin("Jeanne Oskour");

				ImGui::Text("Messages (%i / %i) :", messages.size(), JeanneOskour::GetInstance()->GetTotalMessagesCount());

				for (const std::string* message : messages)
					ImGui::Text(message->c_str());

				ImGui::End();

				#pragma endregion

				simulation->Update(window.GetDeltaTime());

				if (isPlaying && timer.getElapsedTime().asSeconds() >= period)
				{
					simulation->Step(period);

					timer.restart();
				}

				Log::Show();
;
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
};
