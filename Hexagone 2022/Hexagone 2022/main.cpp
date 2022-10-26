#include <vector>

#include "Window.hpp"
#include "Menu.hpp"
#include "Main.hpp"

int main()
{
	sw::Window window("Hexagone 2022", 720, 720, 0u, 0u);

	TextureManager::Init();

	TextureManager::LoadTextureFromFile("Character", "./sprites/character.png");

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