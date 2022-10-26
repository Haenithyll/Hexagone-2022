#include "PseudoRandom.hpp"


void PseudoRandom::ResetSeed() {
	std::srand((unsigned int) std::time(0));
	return;
}

int PseudoRandom::GetInt(int minInclusive, int maxInclusive)
{
	/*int random = std::rand();
	//minInclusive + random / ((RAND_MAX + 1u) / maxInclusive)
	std::cout << ((random) % (maxInclusive - minInclusive + 1)) + minInclusive << std::endl;
	random = random % (maxInclusive - minInclusive + (1)) + minInclusive;
	return random;*/

	return std::rand() % (maxInclusive - minInclusive + (1)) + minInclusive;
}

sf::Vector3i PseudoRandom::GetPosition(int radius)
{
	int x = GetInt(-radius, radius), y;

	//y = GetInt(x > 0 ? -radius : -radius - x, x > 0 ? radius - x : radius);
	//or
	//y = x > 0 ? GetInt(-radius, radius - x) : GetInt(-radius - x, radius);
	//or
	//x > 0 ? y = GetInt(-radius, radius - x) : y = GetInt(-radius - x, radius);
	//or
	if (x > 0)
		y = GetInt(-radius, radius - x);
	else
		y = GetInt(-radius - x, radius);

	return sf::Vector3i(x, y, -(x + y));
}

sf::Vector3i PseudoRandom::GetDirection()
{
	sf::Vector3i dir;
	do
	{
		dir = sf::Vector3i(GetPosition(1));
	} while ((abs(dir.x) + abs(dir.y) + abs(dir.z)) == 0);
	return dir;
}

int PseudoRandom::GetObstacleType(int type)
{
	return GetInt(0, type);
}

void PseudoRandom::GetOrder(int n, int* randomOrder)
{
	int tmp;
	bool unique = true;

	for (short i = 0; i < n; i++) 
	{
		do 
		{
			unique = true;
			tmp = GetInt(1, n);
			for (short j = 0; j < n - 1; j++) { // no need to check the last one
				if (tmp == randomOrder[j]) unique = false;
			}
		} while (!unique);

		if (unique) randomOrder[i] = tmp;
	}
	return;
}
