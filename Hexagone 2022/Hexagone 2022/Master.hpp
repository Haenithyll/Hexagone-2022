#pragma once
#include "Character.hpp"
#include "Activist.hpp"

class Master : public Character
{
public:

    /**
     * Singletons should not be cloneable.
     */
    Master(Master& other) = delete;
    /**
     * Singletons should not be assignable.
     */
    void operator=(const Master&) = delete;

    static Master* GetMaster(const Party party);

    Action DecideAction() override;
    int DecideMoveRange() override;
    void Meet(Character* character) override;
    void MeetMaster() override;
protected:
    Master(const std::string& name, Party party, Party allyParty, int maxEnergy):Character(name, party, allyParty, maxEnergy)
    {
        
    }
    static std::map<Party, Master*> _masters;
};

