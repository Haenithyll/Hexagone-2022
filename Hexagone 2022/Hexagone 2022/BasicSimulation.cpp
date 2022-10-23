#include "BasicSimulation.hpp"

#include "Log.hpp"

BasicSimulation::BasicSimulation(int radius) : Simulation(radius)
{

}

void BasicSimulation::Reset()
{
	Simulation::Reset();

	mCharacters.clear();

	Log::Print("int");

	for (int i = 0; i < 5; ++i)
		mCharacters.push_back(new Activist(Party::Reprise, Party::P3, sf::Vector3i(), 10, 2, 5));
}
