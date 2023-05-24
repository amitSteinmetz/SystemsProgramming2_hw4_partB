#include "Team.hpp"

class Team2 : public Team
{
    // Ctor
    public:
    Team2(Character* new_leader);

    // Overriding methods
    void print();
    void attack(Team* enemies);
    int stillAlive();
};