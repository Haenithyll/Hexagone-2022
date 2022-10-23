#pragma once

#include "Simulation.hpp"

#include "Activist.hpp"

class BasicSimulation : public Simulation
{
	public:
		BasicSimulation(int radius);

		void Reset() override;
};
