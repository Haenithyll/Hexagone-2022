#pragma once
#include <cstdlib>
#include <iostream>
#include <ctime>
#include <vector>

class PseudoRandom
{
public:
	PseudoRandom(int NumberOfDiffObstacles = 0)
	{
		std::srand(std::time(0));
		mNumberOfDiffObstacles = NumberOfDiffObstacles;
	}

	std::vector<sf::Vector3<int>> GetPosition(int n, int radius);
	int GetObstacleType();
	sf::Vector3<int> GetDirection();
	int[] GetOrder(int n);
	int GetInt(int minInclusive, int maxInclusive);

private:
	short mNumberOfDiffObstacles = 0;
};