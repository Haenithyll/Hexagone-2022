#include "PseudoRandom.hpp"


void PseudoRandom::ResetSeed() {
	std::srand(std::time(NULL));
	return;
}

int PseudoRandom::GetInt(int minInclusive, int maxInclusive)
{
	return std::rand() % (maxInclusive - minInclusive + (1)) + minInclusive;
}

sf::Vector3i PseudoRandom::GetPosition(int radius)
{
	int x = GetInt(-radius, radius);

	int y = x > 0 ? GetInt(-radius, radius - x) : GetInt(-radius - x, radius);

	return sf::Vector3i(x, y, -(x + y));
}

sf::Vector3i PseudoRandom::GetDirection()
{
	sf::Vector3i dirs[] = {
		sf::Vector3i(0, 1, -1),
		sf::Vector3i(1, 0, -1),
		sf::Vector3i(1, -1, 0),
		sf::Vector3i(0, -1, 1),
		sf::Vector3i(-1, 0, 1),
		sf::Vector3i(-1, 1, 0),
	};
	
	return dirs[GetInt(0,  5)];
}

int PseudoRandom::GetObstacleType(int type)
{
	return GetInt(0, type);
}
