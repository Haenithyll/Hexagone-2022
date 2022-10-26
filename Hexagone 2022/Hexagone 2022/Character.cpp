#include "Character.hpp"

void Character::ReceiveMessages(const std::vector<const std::string*>* newMessages, int amountToTake)
{
	for (const std::string* message : *newMessages)
	{
		if (std::find(_messages.begin(), _messages.end(), message) == _messages.end())//message not in _messages
		{
			_messages.push_back(message);
			if (--amountToTake < 1)
				break;
		}
	}
}

void Character::AddMessage(const std::string* message)
{
	_messages.push_back(message);
}

void Character::DeleteMessage(int index)
{
	_messages.erase(_messages.begin() + index);
}

bool Character::LoseEnergy()
{
	return _energyPoints-- <= 0;
}