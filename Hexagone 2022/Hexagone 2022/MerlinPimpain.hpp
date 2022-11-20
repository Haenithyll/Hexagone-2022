#include "Character.hpp"
#include "Activist.hpp"
#include "Master.hpp"

class MerlinPimpain : public Character, public Master
{
public:
	static void Init(int totalMessagesCount, Messages startMessages)
	{
		_instance = new MerlinPimpain(totalMessagesCount, startMessages);
	}

	static MerlinPimpain* GetInstance() {
		return _instance;
	}

	Action DecideAction() override { return Action::BackToHome; };
	int DecideMoveRange() override { return 0; };
	void Meet(Character*) override {};
	void MeetMaster() override {};
	const Messages& GetMessages() const override { return _masterMessages; }
	void SetMessages(const Messages newMessages) override
	{
		_masterMessages = newMessages;
	}

private:
	static MerlinPimpain* _instance;

	MerlinPimpain(int totalMessagesCount, Messages startMessages) : Character("Merlin Pimpain", EnRoute, LesRebelles, 0),
		Master(totalMessagesCount, startMessages) {
		isMaster = true;
	};
};