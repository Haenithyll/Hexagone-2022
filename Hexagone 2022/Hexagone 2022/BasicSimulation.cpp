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

		Character* character = new Activist(Party::Reprise, Party::P3, 10, 2, 5);
		character->MoveTo(Tilemap::CoordToPosition(position) * 75.f, 3.f);

		mAllCharacters[std::array<int, 3> { position.x, position.y, position.z }] = character;
	}
}
