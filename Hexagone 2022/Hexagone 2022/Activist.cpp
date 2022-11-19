#include "Activist.hpp"
#include "Master.hpp"
#include "PseudoRandom.hpp"

#include "JosephRepublique.hpp"
#include "JeanneOskour.hpp"
#include "BenjaminVouallion.hpp"
#include "MerlinPimpain.hpp"

Action Activist::DecideAction()
{
	if ((float)_energyPoints / _maxEnergyPoints <= 0.2f)
		return BackToHome;
	return RandomMove;
}

int Activist::DecideMoveRange()
{
	return PseudoRandom::GetInt(_nMinMove, _nMaxMove);
}

void Activist::Meet(Character* character)
{
	if (character->GetParty() == _party)
		MessagesUnion(character);
	else if (character->GetParty() == _allyParty)
		ShareMessages(character);
	else
		Fight(character);
}

void Activist::MeetMaster()
{
	Character* master;

	switch (_party)
	{
		case LesRebelles:
			master = JosephRepublique::GetInstance();

			break;

		case EnRoute:
			master = MerlinPimpain::GetInstance();

			break;

		case AgglutinationPatriote:
			master = JeanneOskour::GetInstance();

			break;

		case Reprise:
			master = BenjaminVouallion::GetInstance();

			break;

		default:
			throw new std::invalid_argument("Tu es nul");
	}

	MessagesUnion(master);

	_energyPoints = _maxEnergyPoints;
}

void Activist::Fight(Character* character)
{
	bool b = PseudoRandom::GetInt(0, 1) == 0;
	Character* winner = b ? this : character;
	Character* loser = b ? character : this;

	int amountToTake = PseudoRandom::GetInt(0, std::min(3, (int)loser->GetMessages()->size()));
	const Messages* loserMessages = loser->GetMessages();
	const Messages* winnerMessages = winner->GetMessages();
	
	for (int i = 0; i < loserMessages->size(); ++i)
	{
		const std::string* message = (*loserMessages)[i];
		if (std::find(winnerMessages->begin(), winnerMessages->end(), message) == winnerMessages->end())//message not in winnerMessages
		{
			winner->AddMessage(message);
			loser->DeleteMessage(i--);
			if (--amountToTake < 1)
				break;
		}
	}
}

void Activist::ShareMessages(Character* character)
{
	//shares 1 message each
	ReceiveMessages(character->GetMessages(), 1);
	character->ReceiveMessages(&_messages, 1);
}

void Activist::MessagesUnion(Character* character)
{
	const Messages* otherMessages = character->GetMessages();
	for (const std::string* message : *otherMessages)
	{
		if (std::find(_messages.begin(), _messages.end(), message) == _messages.end())//message not in _messages
		{
			_messages.push_back(message);
		}
	}
	character->SetMessages(_messages);
}
