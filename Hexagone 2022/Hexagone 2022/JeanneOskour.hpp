#include "Character.hpp"
#include "Activist.hpp"
#include "Master.hpp"

class JeanneOskour : public Character, public Master
{
public:
	static void Init(int totalMessagesCount, Messages startMessages)
	{
		_instance = new JeanneOskour(totalMessagesCount, startMessages);
	}

	static JeanneOskour* GetInstance() {
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
	static JeanneOskour* _instance;

	JeanneOskour(int totalMessagesCount, Messages startMessages) : Character("Jeanne Oskour", AgglutinationPatriote, Reprise, 0),
		Master(totalMessagesCount, startMessages) {
		isMaster = true;
	};
};