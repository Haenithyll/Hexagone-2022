#pragma once
#include <vector>
#include <string>
#include <SFML/System/Vector3.hpp>

enum Action { RandomMove, BackToHome };
enum Party { None, LesRebelles, EnRoute, P3, Reprise };
class Character
{
public:
	Character(Party party, Party allyParty, int maxEnergy)
	{
		_party = party;
		_allyParty = allyParty;
		_maxEnergyPoints = maxEnergy;

		_energyPoints = _maxEnergyPoints;
	}
	const Party GetParty() const {	return _party;	}
	const std::vector<const std::string*>* GetMessages() const {	return &_messages;	}
	void SetMessages(const std::vector<const std::string*> newMessages) {	
		_messages = newMessages;
	}
	void ReceiveMessages(const std::vector<const std::string*>* newMessages, int amountToTake);
	void AddMessage(const std::string* message);
	void DeleteMessage(int index);
	virtual Action DecideAction() = 0;
	virtual int DecideMoveRange() = 0;
	virtual void Meet(Character* character) = 0;
	virtual void MeetMaster() = 0;
	sf::Vector3i GetLastDirection() {
		return _lastDirection;
	}
	void SetLastDirection(sf::Vector3i value) {
		_lastDirection = value;
	}
	bool LoseEnergy();
protected:
	std::vector<const std::string*> _messages;
	Party _party;
	Party _allyParty;
	sf::Vector3i _lastDirection{ sf::Vector3i() };
	int _energyPoints;
	int _maxEnergyPoints;
};

