#include <vector>

#include "Window.hpp"
#include "Menu.hpp"
#include "Simulation.hpp"
#include "Tilemap.hpp"

int main()
{
	//sw::Window window("Hexagone 2022", 1368, 768, 0u, 0u);

	//window.Create(false, 8u);

	//int index = 0;
	Tilemap::getInstance()->InitTilemap();

	//std::vector<Screen*> screens = {
	//	new Menu(),
	//	new Simulation()
	//};

	//while (index >= 0)
	//	index = screens[index]->Run(window);

	return 0;
}