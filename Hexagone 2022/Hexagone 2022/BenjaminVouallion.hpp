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

	static BenjaminVouallion* GetInstance() {
		return _instance;
	}

	Action DecideAction() override { return Action::BackToHome; };
	int DecideMoveRange() override { return 0; };
	void Meet(Character*) override {};
	void MeetMaster() override {};
	const Messages* GetMessages() const override { return &_masterMessages; } 
	void SetMessages(const Messages newMessages) override { _masterMessages = newMessages; }

protected:
	static BenjaminVouallion* _instance;

	BenjaminVouallion(int totalMessagesCount, Messages startMessages) : Character("Ben Vouallion", Reprise, AgglutinationPatriote, 0), 
		Master(totalMessagesCount, startMessages) { 
		isMaster = true;
	};
};