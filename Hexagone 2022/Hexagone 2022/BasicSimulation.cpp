#include "BasicSimulation.hpp"

#include "Log.hpp"

BasicSimulation::BasicSimulation(int radius, patternCenters(Tilemap::* pattern)()) : Simulation(radius, pattern)
{

}

void BasicSimulation::Reset()
{
	Simulation::Reset();

	mAllCharacters.clear();

	Log::Print("int");

	//for (int i = 0; i < 5; ++i)
	//	mAllCharacters.push_back(new Activist(Party::Reprise, Party::P3, sf::Vector3i(), 10, 2, 5));
}
