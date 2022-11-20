#include "Activist.hpp"
#include "Master.hpp"
#include "PseudoRandom.hpp"

#include "JosephRepublique.hpp"
#include "JeanneOskour.hpp"
#include "BenjaminVouallion.hpp"
#include "MerlinPimpain.hpp"

#include "Log.hpp"

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
	{
		MessagesUnion(character);

		Log::Print("Je fais la rencontre de mon allie " + character->GetName() + ", nous echangeons tous nos messages");
	}
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
			throw new std::invalid_argument("Invalid Party");
	}

	MessagesUnion(master);

	Log::Print("Je fais la rencontre de mon maitre " + master->GetName() + ", nous echangeons tous nos messages");

	_energyPoints = _maxEnergyPoints;
}

void Activist::Fight(Character* character)
{
	Log::Print("Je me bas contre " + character->GetName());

	bool lose = PseudoRandom::GetInt(0, 1) == 0;

	Character* winner = lose ? this : character;
	Character* loser = lose ? character : this;

	int amountToTake = PseudoRandom::GetInt(0, std::min(3, (int)loser->GetMessages().size()));
	const Messages loserMessages = loser->GetMessages();
	const Messages winnerMessages = winner->GetMessages();
	
	for (int i = 0; i < loserMessages.size(); ++i)
	{
		const std::string* message = loserMessages[i];
		if (std::find(winnerMessages.begin(), winnerMessages.end(), message) == winnerMessages.end())//message not in winnerMessages
		{
			winner->AddMessage(message);
			loser->DeleteMessage(i--);
			if (--amountToTake < 1)
				break;
		}
	}

	if (lose)
		Log::Print("J'ai perdu, je perds " + std::to_string(amountToTake) + " messages");
	else
		Log::Print("J'ai gagne, je lui prends " + std::to_string(amountToTake) + " messages");
}

void Activist::ShareMessages(Character* character)
{
	//shares 1 message each
	ReceiveMessages(character->GetMessages(), 1);
	character->ReceiveMessages(_messages, 1);

	Log::Print("Je fais la rencontre de " + character->GetName() + ", nous echangeons un message");
}

void Activist::MessagesUnion(Character* character)
{
	const Messages otherMessages = character->GetMessages();
	for (const std::string* message : otherMessages)
		_messages.push_back(message);

	std::sort(_messages.begin(), _messages.end());
	_messages.erase(std::unique(_messages.begin(), _messages.end()), _messages.end());//suppression des doublons éventuels
	character->SetMessages(_messages);
}
