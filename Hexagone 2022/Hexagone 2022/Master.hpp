#pragma once
#include "Character.hpp"
#include "Activist.hpp"

class Master 
{
public:
	int GetTotalMessagesCount() { return _totalMessagesCount; }

protected:
	Master(int totalMessagesCount, Messages _startMessages) 
	{
		_totalMessagesCount = totalMessagesCount;
		_masterMessages.insert(std::end(_masterMessages), std::begin(_startMessages), std::end(_startMessages));
	}
	int _totalMessagesCount;
	Messages _masterMessages;
};

