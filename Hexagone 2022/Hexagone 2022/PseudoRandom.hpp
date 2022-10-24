#pragma once

#include "SFML/System/Vector3.hpp"

#include <cstdlib>
#include <iostream>
#include <ctime>
#include <vector>

class PseudoRandom
{
public:
	static void ResetSeed();
	static int GetInt(int minInclusive, int maxInclusive);
	static sf::Vector3i GetPosition(int radius);
	static sf::Vector3i GetDirection();
	static int GetObstacleType(int type);
	static void GetOrder(int n, int* randomOrder);
};