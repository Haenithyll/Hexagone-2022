#include "Character.hpp"

void Character::ReceiveMessages(std::vector<std::string*>* otherMessages)
{
	for (int i = 0; i < otherMessages->size(); i++)
	{
		if (std::find(_messages.begin(), _messages.end(), (*otherMessages)[i]) == _messages.end())//message not in vector
		{
			_messages.push_back((*otherMessages)[i]);
		}
	}
}
