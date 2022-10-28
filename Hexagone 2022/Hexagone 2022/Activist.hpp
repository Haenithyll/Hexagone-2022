#pragma once
#include "Character.hpp"
#include "Tilemap.hpp"

class Activist : public Character
{
public:
	Activist(const std::string& name,  Party party, Party allyParty, int maxEnergy,
		int nMinMove, int nMaxMove)
		:Character(name, party, allyParty, maxEnergy)
	{
		_nMinMove = nMinMove;
		_nMaxMove = nMaxMove;
	}
	virtual Action DecideAction() override;
	virtual int DecideMoveRange() override;
	virtual void Meet(Character* character) override;
	virtual void MeetMaster() override;
private:
	int _nMinMove;
	int _nMaxMove;

	void Fight(Character* character);
	void ShareMessages(Character* character);
	void MessagesUnion(Character* character);
};