#include "Character.hpp"
#include "Activist.hpp"
#include "Master.hpp"

class BenjaminVouallion : public Character, public Master
{
public:
	static void Init(int totalMessagesCount, Messages startMessages) 
	{
		if (_instance == nullptr)
			_instance = new BenjaminVouallion(totalMessagesCount, startMessages);
	}

	Action DecideAction() override {};
	int DecideMoveRange() override {};
	void Meet(Character*) override {};
	void MeetMaster() override {};
	const Messages* GetMessages() const override { return &_masterMessages; } 
	void SetMessages(const Messages newMessages) override { _masterMessages = newMessages; }

protected:
	static BenjaminVouallion* _instance;

	BenjaminVouallion(int totalMessagesCount, Messages startMessages) : Character("Ben Vouallion", Reprise, AgglutinationPatriote, 0), 
		Master(totalMessagesCount, startMessages) { };
};