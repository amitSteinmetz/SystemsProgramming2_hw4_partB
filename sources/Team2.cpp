#include "Team2.hpp"

using namespace std;

/* Ctor */
Team2::Team2(Character* new_leader) : Team(new_leader)
{}

/* Methods */

void Team2::print()
{
    if (getMembers().empty()) throw runtime_error("Team has no members!");

    for (Character* warrior: getMembers())
    {
        cout << warrior->print() << endl;
    }
}

void Team2::attack(Team* enemies)
{
     /* Error handle */
    if (getMembers().empty()) throw runtime_error("Team has no members!");
    if (!enemies) throw invalid_argument("nullptr");
    if (enemies->stillAlive() == 0) throw runtime_error("Can't attack dead team!");

    // Check if attacking leader is alive, and if not, the closest warrior will be the new leader
    if (!getLeader()->isAlive()) setLeader(closestWarrior(this));

    // Group choose a victim - the closest to the attacking leader
    Character* victim = closestWarrior(enemies);

    /* Attacking the victim */
    for (Character* warrior: getMembers())
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
int Team2::stillAlive()
{
    if (getMembers().empty()) throw runtime_error("Team has no members!");

    int result = 0;

    for (Character* warrior: getMembers())
    {
        if (warrior->isAlive()) result++;
    }

    return result;
}