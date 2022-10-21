#pragma once
#include <vector>
#include <string>
#include <SFML/System/Vector3.hpp>

class Character
{
public:
	Character(Party party, Party allyParty, sf::Vector3i position)
	{
		_party = party;
		_allyParty = allyParty;
		_position = position;
	}
	Party GetParty(){	return _party;	}
	std::vector<std::string*>* GetMessages(){	return &_messages;	}
	void ReceiveMessages(std::vector<std::string*>*);
	virtual void Move() = 0;
protected:
	std::vector<std::string*> _messages;
	Party _party;
	Party _allyParty;
	sf::Vector3<int> _position;
};
enum Party {None, LesRebelles, EnRoute, P3, Reprise};

