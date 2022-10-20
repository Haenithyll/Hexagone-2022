#include "Activist.hpp"
#include "Master.hpp"

void Activist::Move()
{
	std::vector<sf::Vector3i> pathToTravel;
	int nTravelLength = PseudoRandom.GetInt(_nMinMove, _nMaxMove);
	if ((float)_energyPoints / _maxEnergyPoints <= 0.2)
	{
		pathToTravel = Tilemap.GetSafeZonePath(_position, _party);
	}
	else
	{
		for (int i = 0; i < nTravelLength; i++)
		{
			sf::Vector3i move = PseudoRandom.GetDirection();
			while (!Tilemap.ValidPosition(_position + move) || move == _lastDirection)
			{
				move = PseudoRandom.GetDirection();
			}

			pathToTravel.push_back(Tilemap.GetTile(_position + move));
			_lastDirection = move;
		}
	}

	for (int i = 0; i < pathToTravel.size(); i++)
	{
		if (_energyPoints-- <= 0)
		{
			_isDead = true;
			Tilemap.GetTile(_position)->Obstacle = true;
			//GraphicUpdate
		}
		Tile nextTile = pathToTravel[i];
		if (nextTile.Obstacle || nextTile.Safezone != _party)
			break;

		//we didn't encounter an obstacle so lastDirection is reset
		_lastDirection = sf::Vector3i(0, 0, 0);

		Character* character = nextTile->Character;
		if (character != nullptr)
		{
			if (character->GetParty() == _party)
				MessagesUnion(character->GetMessages());
			else if (character->GetParty() == _allyParty)
				ShareMessages(character);
			else
				Fight(character);
			break;
		}
		else 
		{
			*character = *this;
			Tilemap.GetTile(_position)->Character = nullptr;
			//GraphicUpdate
			if (nextTile.Safezone == _party)
			{
				Master master;
				master.ReceiveMessages(_messages*);
				_energyPoints = _maxEnergyPoints;
				master.DeliverMessages(this);
			}
		}
	}
}

void Activist::Fight(Character* character)
{
	Character* winner;
	Character* loser;
	//50/50
	if (PseudoRandom.GetInt(0, 1) == 0)
	{
		winner = this;
		loser = character;
	}
	else
	{
		winner = character;
		loser = this;
	}
	int nTaken = PseudoRandom.GetInt(1, std::min(3, (int)loser->GetMessages()->size()));
	int counter = 0;
	std::vector<std::string*>* loserMessages = loser->GetMessages();
	std::vector<std::string*>* winnerMessages = winner->GetMessages();
	for (int j = 0; j < loserMessages->size(); j++)
	{
		std::string* message = (*loserMessages)[j];
		if (std::find(winnerMessages->begin(), winnerMessages->end(), message) == winnerMessages->end())//message not in vector
		{
			winnerMessages->push_back(message);
			loserMessages->erase(loserMessages->begin() + j);
			if (++counter >= nTaken)
				break;
		}
	}
}

void Activist::ShareMessages(Character* character)
{
	//shares 1 message each
	std::vector<std::string*>* otherMessages = character->GetMessages();
	for (int i = 0; i < otherMessages->size(); i++)
	{
		if (std::find(_messages.begin(), _messages.end(), (*otherMessages)[i]) == _messages.end())//message not in vector
		{
			_messages.push_back((*otherMessages)[i]);
			break;
		}
	}
	for (int i = 0; i < otherMessages->size(); i++)
	{
		if (std::find(_messages.begin(), _messages.end(), (*otherMessages)[i]) == _messages.end())//message not in vector
		{
			_messages.push_back((*otherMessages)[i]);
			break;
		}
	}
}

void Activist::MessagesUnion(std::vector<std::string*>* newMessages)
{
	Character::ReceiveMessages(newMessages);
	*newMessages = _messages;
}
