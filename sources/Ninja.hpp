#pragma once
#include "Character.hpp"

class Ninja : public Character
{
    // Attributes:
    int speed;

    // Ctors:
    public:
    Ninja(std::string new_name, Point new_location, int hit_points, int speed);

    // Methods:
    void move(const Character* enemy);
    void slash(Character* enemy);
    int getSpeed() const;
    void attack_victim(Character* victim);
};