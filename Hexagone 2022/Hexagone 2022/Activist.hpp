#pragma once
#include "Character.hpp"

class Activist : Character
{
public:
	Activist(int maxEnergy)
	{
		_maxEnergyPoints = maxEnergy;
		_energyPoints = _maxEnergyPoints;
		_isDead = false;
		_lastDirection = sf::Vector3i();
	}
	virtual void Move() override;
private:
	int _energyPoints;
	int _maxEnergyPoints;
	bool _isDead;
	sf::Vector3i _lastDirection;
	int _nMinMove;
	int _nMaxMove;

	void Fight(Character*);
	void ShareMessages(Character*);
	void MessagesUnion(std::vector<std::string*>*);
};

