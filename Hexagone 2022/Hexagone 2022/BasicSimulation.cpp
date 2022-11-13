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
	mCharacterPositions.clear();

	sf::Vector3i position = PseudoRandom::GetPosition(Tilemap::Radius());
	std::vector<std::string> names = AssetManager::GetText("Names");

	for (int i = 0; i < 2; ++i)
	{
		std::string name = names[PseudoRandom::GetInt(0, names.size() - 1)];

		Character* character = new Activist(name, (Party)i + 1, Party::P3, 10, 2, 5);

		sf::Vector3i position = sf::Vector3i(1, -1, 0);

		mCharacterPositions.push_back(position);
		mAllCharacters[std::array<int, 3> { position.x, position.y, position.z }] = character;

		character->MoveTo(Tilemap::CoordToPosition(position) * 75.f, 0.f);
	}
}
