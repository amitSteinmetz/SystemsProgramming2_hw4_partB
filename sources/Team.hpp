#pragma once

namespace ariel{}

#include "Character.hpp"
#include "Cowboy.hpp"
#include "Ninja.hpp"
#include "YoungNinja.hpp"
#include "TrainedNinja.hpp"
#include "OldNinja.hpp"
#include <vector>

class Team
{
    // Attributes
    Character* leader;
    std::vector<Character*> members;

    public:
    // Ctor
    Team(Character* new_leader);

    // Dtor
    ~Team();

    // Methods
    void add(Character* new_warrior);
    void virtual attack(Team* enemies);
    int virtual stillAlive();
    void virtual print();
    void sortCharacters();
    Character* closestWarrior(Team* team);
    std::vector<Character*> getMembers();
    Character* getLeader();
    void setLeader(Character* new_leader);
};
