#pragma once

#include "Simulation.hpp"

#include "Activist.hpp"

class BasicSimulation : public Simulation
{
public:
	BasicSimulation(int radius, patternCenters(Tilemap::* pattern)());

	void Reset() override;

private:
	void InitMasters();
	void InitActivists(int countPerParty);
};
