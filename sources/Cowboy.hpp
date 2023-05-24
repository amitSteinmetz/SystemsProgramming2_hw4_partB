#pragma once
#include "Character.hpp"

class Cowboy : public Character
{
    // Attributes:
    int bullets_amount;

    // Ctors:
    public:
    Cowboy(std::string new_name, Point new_location);
    
    // Methods:
    void shoot(Character* enemy);
    bool hasboolets() const;
    void reload();
    int getBulletsAmount() const;
    void attack_victim(Character* victim);
};