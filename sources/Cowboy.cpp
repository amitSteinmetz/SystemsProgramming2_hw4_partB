#include "Cowboy.hpp"

using namespace std;

/* Ctors */

Cowboy::Cowboy(std::string new_name, Point new_location)
  : Character(new_name, new_location, 110, "C") ,bullets_amount(6)
{}

/* Methods: */

void Cowboy::shoot(Character* enemy)
{
    /* Error handle */ 
    if (!enemy->isAlive()) throw runtime_error("Enemy is already dead!");
    if (!isAlive()) throw runtime_error("Dead character can't attack!");
    if (this == enemy) throw runtime_error("No self harm");
    
    if (hasboolets())
    {
        enemy->hit(10);
        bullets_amount -= 1; // Lose one bullet
    }
}
bool Cowboy::hasboolets() const
{
    if (bullets_amount > 0) return true;

    return false;
}
void Cowboy::reload()
{
    if (!isAlive()) throw runtime_error("Dead cowboy can't reload!");
    
    bullets_amount = 6;
}
int Cowboy::getBulletsAmount() const
{
    return bullets_amount;
}
void Cowboy::attack_victim(Character* victim)
{
    if (!hasboolets()) reload(); // If there's no bullets left, reload
    else shoot(victim);
}