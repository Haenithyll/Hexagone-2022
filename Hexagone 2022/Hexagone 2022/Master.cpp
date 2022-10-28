#include "Master.hpp"
#include "AssetManager.hpp"
#include "PseudoRandom.hpp"

std::map<Party, Master*> Master::_masters = std::map<Party, Master*>();

Master* Master::GetMaster(const Party party)
{
    std::vector<std::string> names = AssetManager::GetText("Names");

    if (_masters.find(party) == _masters.end()) {
        std::string name = names[PseudoRandom::GetInt(0, names.size() - 1)];

        _masters[party] = new Master(name, Party::EnRoute, Party::P3, 100);
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
