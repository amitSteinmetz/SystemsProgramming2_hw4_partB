#include "SmartTeam.hpp"
#include <cfloat>

using namespace std;

// Ctor 
SmartTeam::SmartTeam(Character* new_leader) : Team(new_leader)
{}

void SmartTeam::attack(Team* enemies)
{
    // Check if there are cowboys in our team, and how nuch.
    int amount_of_cowboys = amount_of_cowboys_or_ninjas(this, "C");

    /* If there are, check how much cowboys there are in enemies team: 
    
    1. less than us - cowboys will kill cowboys enemeis, and ninja's will
    move towards defending cowboys in order to protect them from attacking ninja's.

    2. same amount - depends on ninja's enemeis strength and amount:
    if enemeis stronger or bigger - send a decoy (HP bigger ninja, to stole time) close to ninja
    of enemy, and all other of our ninja's will get less close to ninja of enemy (but still less than meter), and they
    hit the ninja.
    if we are stronger or bigger - our ninja's kill their ninja's. 

    3. more than us - our ninja's will kill their cowboys.
    */

    if (amount_of_cowboys > 0)
    {
        /* Check enemy amount of cowboys */
        int enemies_amount_of_cowboys = amount_of_cowboys_or_ninjas(enemies, "C");

        // Less
        if (enemies_amount_of_cowboys < amount_of_cowboys)
        {
            for (Character* warrior: getMembers()) 
            {
                if (warrior->isAlive())
                {
                    // Cowboys attack cowboys (or ninja's if no cowboys left)
                    if (warrior->getType() == "C")
                    {
                        Character* victim = chooseCowboy(enemies);
                        if (!victim) victim = chooseEnemyNinja(enemies);
                        warrior->attack_victim(victim);
                    }

                    // Ninja's defending
                    if (warrior->getType() == "N")
                    {
                        Character* cowboy_teamate = chooseCowboy(this);
                        bool attack_ninja = false;

                        // Check if there is enemy ninja less than meter
                        for (Character* enemy: enemies->getMembers())
                        {
                            if (enemy->getType() == "N" && enemy->isAlive() && warrior->distance(enemy) <= 1) warrior->attack_victim(enemy);
                            attack_ninja = true;
                        }

                        // In case that there's no ninja less than meter but there's no teamate cowboy
                        if (!attack_ninja && !cowboy_teamate)
                        {
                            Character* new_victim = closestWarrior(enemies, warrior, "N");
                            if (!new_victim) new_victim = closestWarrior(enemies, warrior, "C");

                            warrior->attack_victim(new_victim);
                        }

                        // In case that there's no ninja less than meter but there is teamate cowboy
                        if (cowboy_teamate && !attack_ninja) moveToCharacter(warrior, cowboy_teamate);
                    }
                }
            }
        }

        // Same amount
        else if (enemies_amount_of_cowboys == amount_of_cowboys)
        {
            /* Cowboys kills enemies cowboys */ 
            for (Character* character: getMembers())
            {
                if (character->isAlive() && character->getType() == "C")
                {
                    // If there is enemy cowboy
                    if (amount_of_cowboys_or_ninjas(enemies, "C") > 0)
                    {
                        Character* cowboy_victim = chooseCowboy(enemies);
                        character->attack_victim(cowboy_victim);
                    }
                    else // Attack ninja
                    {
                        Character* ninja_victim = chooseEnemyNinja(enemies);
                        character->attack_victim(ninja_victim);
                    }
                }
            }

            /* Ninjas kill enemies ninjas */ 

            // Check amount of ninjas
            int amount_of_ninjas = amount_of_cowboys_or_ninjas(this, "N");
            int enemies_amount_of_ninjas = amount_of_cowboys_or_ninjas(enemies, "N");

            // If there are no enemies ninjas, attack cowboys
            if (enemies_amount_of_ninjas == 0)
            {
                // every ninja warrior attack victim
                 // victim = closest_warrior() to each warrior
                for (Character* character2: getMembers())
                {
                    if (character2->isAlive() && character2->getType() == "N")
                    {
                        Character* enemy_victim = closestWarrior(enemies, character2, "C");
                        character2->attack_victim(enemy_victim);
                    }
                }
            }

            // If enemies ninjas are stronger
            else if (amount_of_ninjas < enemies_amount_of_ninjas)
            {
                // Send a decoy
                Character* strongest_ninja = findStrongestNinja(this);
                Character* enemy = chooseEnemyNinja(enemies);
                moveToCharacter(strongest_ninja, enemy);
                
                // Rest of ninjas get close to enemy ninja, but less close than decoy
                moveRest(this, strongest_ninja, enemy);
            }

            // If enemies less stronger
            else
            {
                // Ninjas kill enemies ninja
                for (Character* fighter: getMembers())
                {
                    if (fighter->isAlive() && fighter->getType() == "N")
                    {
                        Character* closest_ninja_victim = closestWarrior(this, fighter, "N");
                        fighter->attack_victim(closest_ninja_victim);
                    }
                }
            }
        }

        // Bigger amount
        else
        {
            /* Cowboys kill enemy cowboys */
            for (Character* character1: getMembers())
            {
                if (character1->isAlive() && character1->getType() == "C")
                {
                    // If there is enemy cowboy
                    if (amount_of_cowboys_or_ninjas(enemies, "C") > 0)
                    {
                        Character* cowboy_victim = chooseCowboy(enemies);
                        character1->attack_victim(cowboy_victim);
                    }
                    else // If not, attack a ninja
                    {
                        Character* ninja_victim = chooseEnemyNinja(enemies);
                        character1->attack_victim(ninja_victim);
                    }
                }
            }

            /* Ninja's kill enemy cowboys */ 
              for (Character* character2: getMembers())
            {
                if (character2->isAlive() && character2->getType() == "N")
                {
                    // If there is enemy cowboy
                    if (amount_of_cowboys_or_ninjas(enemies, "C") > 0)
                    {
                        Character* cowboy_victim = chooseCowboy(enemies);
                        character2->attack_victim(cowboy_victim);
                    }
                    else // If not, attack a ninja
                    {
                        Character* ninja_victim = chooseEnemyNinja(enemies);
                        character2->attack_victim(ninja_victim);
                    }
                }
            }
        }
    }

    /* If there are'nt cowboys in our team, the ninja's will kill first enemy cowboys, and after that ninja's. */
    else
    {
        for (Character* character: getMembers())
        {
            if (character->isAlive())
            {
                // If there is enemy cowboy
                if (amount_of_cowboys_or_ninjas(enemies, "C") > 0)
                {
                    Character* cowboy_victim = chooseCowboy(enemies);
                    character->attack_victim(cowboy_victim);
                }
                else // If not, attack a ninja
                {
                    Character* ninja_victim = chooseEnemyNinja(enemies);
                    character->attack_victim(ninja_victim);
                }
            }
        }
    } 
}

/* Help funcs */

int SmartTeam::amount_of_cowboys_or_ninjas(Team *team, string type)
{
    int amount_of_cowboys = 0, amount_of_ninjas = 0;

    if (type == "C")
    {
        for (Character* warrior: team->getMembers())
        {
            if (warrior->getType() == "C" && warrior->isAlive()) amount_of_cowboys++;
        }

        return amount_of_cowboys;
    }

    else
    {
        for (Character* warrior: team->getMembers())
        {
            if (warrior->getType() == "N" && warrior->isAlive()) amount_of_ninjas++;
        }

        return amount_of_ninjas;
    }   
}

Character* SmartTeam::chooseCowboy(Team* enemies)
{
    for (Character* warrior: enemies->getMembers())
    {
        if (warrior->getType() == "C" && warrior->isAlive()) return warrior;
    }

    return NULL;
}

void SmartTeam::moveToCharacter(Character* warrior, Character* character)
{
    // Optional new location - add minimal speed to current location
    Point new_location = warrior->getLocation().moveTowards(warrior->getLocation(), character->getLocation(), 8);

    // If enemy location is closer than the new location, character will move to the same location of enemy
    if (warrior->getLocation().distance(new_location) > warrior->getLocation().distance(character->getLocation()))
    {
        warrior->setLocation(character->getLocation());
    }

    else warrior->setLocation(new_location);
}

Character* SmartTeam::closestWarrior(Team* team, Character* warrior, string type)
{
    if (team->getMembers().empty()) throw runtime_error("Team has no members!");

    /* Check who is the closest warrior  */ 
    double min_distance = DBL_MAX;
    Character* closest_character = NULL;

    if (type == "N")
    {
         for (Character* character: team->getMembers())
        {
            // Check the distance from warrior to attacking leader, and update closest warrior if needed
            if (character->isAlive() && (warrior->distance(character) < min_distance) && character->getType() == "N")
            {
                min_distance = warrior->distance(character);
                closest_character = character;
            }
        }
    }
    else
    {
         for (Character* character: team->getMembers())
        {
            // Check the distance from warrior to attacking leader, and update closest warrior if needed
            if (character->isAlive() && (warrior->distance(character) < min_distance))
            {
                min_distance = warrior->distance(character);
                closest_character = character;
            }
        }
    }
    return closest_character;
}

Character* SmartTeam::findStrongestNinja(Team* team)
{
    Character* strongest = NULL;
    int most_hitPoints = 0;

    for (Character* warrior: team->getMembers())
    {
        if (warrior->isAlive() && warrior->getType() == "N")
        {
            if (warrior->getHitPoints() > most_hitPoints) 
            {
                strongest = warrior;
                most_hitPoints = warrior->getHitPoints();
            }
        }
    }

    return strongest;
}

Character* SmartTeam::chooseEnemyNinja(Team* enemies)
{
    for (Character* warrior: enemies->getMembers())
    {
        if (warrior->getType() == "N" && warrior->isAlive()) return warrior;
    }

    return NULL;
}

void SmartTeam::moveRest(Team* team, Character* strongestNinja, Character* enemy)
{
    for (Character* warrior: team->getMembers())
    {
        if (warrior != strongestNinja)
        {
            if (warrior->distance(enemy) <= 1) warrior->attack_victim(enemy);
            else
            {
                moveToCharacter(warrior, enemy);
                if (warrior->distance(enemy) == 0)
                {
                    warrior->setLocation(Point((warrior->getLocation().getX() - 0.1), (warrior->getLocation().getY() - 0.1)));
                }
            }
        }
    }
}