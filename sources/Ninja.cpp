#include "Ninja.hpp"

using namespace std;

Ninja::Ninja(std::string new_name, Point new_location, int hit_points, int new_speed) 
: Character(new_name, new_location, hit_points, "N"), speed(new_speed)
{}

void Ninja::move(const Character* enemy)
{
    // Optional new location - add speed to current location
    Point new_location = getLocation().moveTowards(getLocation(), enemy->getLocation(), speed);

    // If enemy location is closer than the new location, character will move to the same location of enemy
    if (this->getLocation().distance(new_location) > this->getLocation().distance(enemy->getLocation()))
    {
        this->setLocation(enemy->getLocation());
    }

    else this->setLocation(new_location);
}

void Ninja::slash(Character* enemy)
{
    /* Handle errors */
    if (!enemy->isAlive()) throw runtime_error("Enemy is already dead!");
    if (!isAlive()) throw runtime_error("Dead character can't attack!");
    if (this == enemy) throw runtime_error("No self harm");
    
    // If character is Alive and enemy location less than 1 (meter), subtract 40 hit_points from enemy
    if (this->getLocation().distance(enemy->getLocation()) <= 1) enemy->hit(40);
}
int Ninja::getSpeed() const
{
    return speed;
}

void Ninja::attack_victim(Character* victim)
{
    if (this->distance(victim) > 1) move(victim); // If ninja is far from metter from victim, he move towards him
    else slash(victim);
}
