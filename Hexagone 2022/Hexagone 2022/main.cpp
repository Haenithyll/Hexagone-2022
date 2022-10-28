#include <vector>

#include "Window.hpp"
#include "Menu.hpp"
#include "Main.hpp"

#include "Log.hpp"

int main()
{
	sw::Window window("Hexagone 2022", 1368, 1368, 0u, 0u);

	AssetManager::LoadTextureFromFile("Character", "./sprites/character.png");
	AssetManager::LoadTextureFromFile("Obstacle", "./sprites/obstacle.png");
	AssetManager::LoadFontFromFile("Default", "./Roboto-Thin.ttf");
	AssetManager::LoadTextFromFile("Names", "names.txt");

	window.Create(false, 8u);

	int index = 0;

	std::vector<Screen*> screens = {
		new Menu(),
		new Main()
	};

	while (index >= 0)
	{
		index = screens[index]->Run(window);

		ImGui::SFML::Render();
	}

	ImGui::SFML::Shutdown();

	return 0;
}