#pragma once

#include "SFML/System/Vector3.hpp"
#include "SFML/Graphics/RenderTarget.hpp"
#include "SFML/Graphics/Drawable.hpp"
#include "SFML/Graphics/CircleShape.hpp"
#include "Text.hpp"
#include "Rectangle.hpp"

#include "Animable.hpp"

#include <vector>
#include <string>
#include <vector>

typedef std::vector<const std::string*> Messages;
enum Action { RandomMove, BackToHome };
enum Party { None, LesRebelles, EnRoute, AgglutinationPatriote, Reprise };
class Character : public sf::Drawable, public Animable
{
public:
	Character(const std::string& name, Party party, Party allyParty, int maxEnergy) : Animable(16, 0)
	{
		_name = name;
		_party = party;
		_allyParty = allyParty;
		_maxEnergyPoints = maxEnergy;

		_energyPoints = _maxEnergyPoints;
	}
	const Party GetParty() const {	return _party;	}
	const virtual Messages& GetMessages() const {	return _messages;	}
	const std::string& GetName() const { return _name; }
	virtual void SetMessages(const Messages newMessages) {
		_messages = newMessages;
	}
	void ReceiveMessages(const Messages& newMessages, int amountToTake);
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

	void SetDrawState(bool idle);
	bool IsMaster() { return isMaster; };

protected:
	Messages _messages;
	Party _party;
	Party _allyParty;
	sf::Vector3i _lastDirection{ sf::Vector3i() };
	int _energyPoints;
	int _maxEnergyPoints;
	std::string _name;
	bool isMaster {false};

private:
	bool mIdle;

	void draw(sf::RenderTarget& target, sf::RenderStates states) const;
};

