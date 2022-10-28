#include "BasicSimulation.hpp"

#include "PseudoRandom.hpp"

#include "Log.hpp"

BasicSimulation::BasicSimulation(int radius, patternCenters(Tilemap::* pattern)()) : Simulation(radius, pattern)
{

}

void BasicSimulation::Reset()
{
	Simulation::Reset();

	mAllCharacters.clear();

	for (int i = 0; i < 3; ++i)
	{
		sf::Vector3i position = PseudoRandom::GetPosition(Tilemap::Radius());

		std::vector<std::string> names = AssetManager::GetText("Names");

		std::string name = names[PseudoRandom::GetInt(0, names.size() - 1)];

		Character* character = new Activist(name, Party::Reprise, Party::P3, 10, 2, 5);
		character->MoveTo(Tilemap::CoordToPosition(position) * 75.f, 3.f);

		mAllCharacters[std::array<int, 3> { position.x, position.y, position.z }] = character;
	}
}
