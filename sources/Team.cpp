#include "Team.hpp"
#include <cfloat>
#include <algorithm>
#include <vector>

using namespace std;

/* Ctor */ 

Team::Team(Character* new_leader) : members()
{
    // If the leader is already in other team - throw exception
    if (new_leader->getTeam()) throw runtime_error("Leader already has a team!");

    leader = new_leader;
    members.push_back(leader);
    leader->setTeam();
}

/* Dtor */ 

Team::~Team()
{
    for (Character* warrior: members) delete warrior;
}; 

/* Methods */

// Help Func - sort the member vector
void Team::sortCharacters()
{
    std::sort(members.begin(), members.end(), [](Character* a, Character* b) {
        // Check if both characters are cowboys
        if (a->getType() == "C" && b->getType() == "C") {
            return a < b; // Sort by memory address (order of addition)
        }
        // Check if both characters are ninjas
        else if (a->getType() == "N" && b->getType() == "N") {
            return a < b; // Sort by memory address (order of addition)
        }
        // Cowboy should come before ninja
        else if (a->getType() == "C") {
            return true;
        }
        // Ninja should come after cowboy
        else if (b->getType() == "C") {
            return false;
        }
        return false; // Default case (to suppress compiler warning)
    });
}

void Team::add(Character* new_warrior)
{
    /* Error handle */
    if (members.size() == 10) throw runtime_error("Group has 10 members!");
    if (new_warrior->getTeam()) throw runtime_error("Warrior already in a team!");

    // Add the new_warrior to the group
    members.push_back(new_warrior);
    new_warrior->setTeam();
}

int Team::stillAlive()
{
    if (members.empty()) throw runtime_error("Team has no members!");

    int result = 0;

    // sort the vector before
    sortCharacters();
   
    for (Character* warrior: members)
    {
        if (warrior->isAlive()) result++;
    }

    return result;
}

Character* Team::closestWarrior(Team* team)
{
    if (team->members.empty()) throw runtime_error("Team has no members!");

    sortCharacters();
    
    /* Check who is the closest warrior to the leader */ 
    double min_distance = DBL_MAX;
    Character* closest_warrior = NULL;

    for (Character* warrior: team->getMembers())
    {
        // Check the distance from warrior to attacking leader, and update closest warrior if needed
        if (warrior->isAlive() && (leader->distance(warrior) < min_distance))
        {
            min_distance = leader->distance(warrior);
            closest_warrior = warrior;
        }
    }

    return closest_warrior;
}

void Team::attack(Team* enemies)
{
    /* Error handle */
    if (members.empty()) throw runtime_error("Team has no members!");
    if (!enemies) throw invalid_argument("nullptr");
    if (enemies->stillAlive() == 0) throw runtime_error("Can't attack dead team!");

    // Check if attacking leader is alive, and if not, the closest warrior will be the new leader
    if (!leader->isAlive()) leader = closestWarrior(this);

    // Group choose a victim - the closest to the attacking leader
    Character* victim = closestWarrior(enemies);

    sortCharacters();

    /* Attacking the victim */
    for (Character* warrior: members)
    {
        if (victim->isAlive())
        {
            if (warrior->isAlive()) warrior->attack_victim(victim);
        }
        else if (enemies->stillAlive())  // If victim died in the middle of the attack, we should choose another victim
        {
            victim = closestWarrior(enemies);
            if (warrior->isAlive()) warrior->attack_victim(victim);
        }
        else break; // If victim died and there are no more enemies alive - stop the attack
    }
}

void Team::print()
{ 
    if (members.empty()) throw runtime_error("Team has no members!");
    
    sortCharacters();

    for (Character* warrior: members)
    {
        cout << warrior->print() << endl;
    }
}

Character* Team::getLeader()
{
    return leader;
}

void Team::setLeader(Character* new_leader)
{
    leader = new_leader;
}

std::vector<Character*> Team::getMembers()
{
    return members;
}