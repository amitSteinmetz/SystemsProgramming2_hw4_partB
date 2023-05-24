#include "Team.hpp"

class SmartTeam : public Team
{
    public:
    // Ctor
    SmartTeam(Character* new_leader);

    // Overriding methods
    void attack(Team* enemies);
    
    int amount_of_cowboys_or_ninjas(Team *team, std::string type);
    Character* chooseCowboy(Team* enemies);
    void moveToCharacter(Character* warrior, Character* cowboy_teamate);
    Character* closestWarrior(Team* team, Character* warrior, std::string type);
    Character* findStrongestNinja(Team* team);
    Character* chooseEnemyNinja(Team* enemies);
    void moveRest(Team* team, Character* strongestNinja, Character* enemy);
};