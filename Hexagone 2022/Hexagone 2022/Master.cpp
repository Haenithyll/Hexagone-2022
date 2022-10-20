#include "Master.hpp"

void Master::DeliverMessages(Character* activist)
{
	std::vector<std::string*>* otherMessages = activist->GetMessages();
	for (int i = 0; i < _messages.size(); i++)
	{
		if (std::find(otherMessages->begin(), otherMessages->end(), _messages[i]) == otherMessages->end())//message not in vector
		{
			otherMessages->push_back(_messages[i]);
		}
	}
}

void Master::Move()
{
	return;
}
