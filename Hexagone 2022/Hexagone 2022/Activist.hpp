#pragma once
#include "Character.hpp"
#include "Tilemap.hpp"

class Activist : public Character
{
public:
	Activist(Party party, Party allyParty, sf::Vector3i position, int maxEnergy, int nMinMove, int nMaxMove):Character(party, allyParty, position)
	{
		_maxEnergyPoints = maxEnergy;
		_energyPoints = _maxEnergyPoints;
		_isDead = false;
		_lastDirection = sf::Vector3i();
		_nMinMove = nMinMove;
		_nMaxMove = nMaxMove;
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

