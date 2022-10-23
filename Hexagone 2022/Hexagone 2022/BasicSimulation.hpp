#pragma once

#include "Simulation.hpp"

#include "Activist.hpp"

class BasicSimulation : public Simulation
{
	public:
		BasicSimulation();

		void Reset() override;
};
