#include "Master.hpp"

std::map<Party, Master*> Master::_masters = std::map<Party, Master*>();

Master* Master::GetMaster(const Party party)
{
    if (_masters.find(party) == _masters.end()) {
        _masters[party] = new Master(Party::EnRoute, Party::P3, 100);
    }
    return _masters[party];
}

Action Master::DecideAction()
{
    return Action::BackToHome;
}

int Master::DecideMoveRange()
{
    return 0;
}

void Master::Meet(Character* character)
{
}

void Master::MeetMaster()
{
}
