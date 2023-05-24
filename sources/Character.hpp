#pragma once
#include "Point.hpp"
#include <string>
#include <iostream>

class Character
{
    // Attributes:
    Point location;
    std::string name;
    int hit_points;
    std::string type;
    bool in_team = false;

    // Ctors:
    public:
    Character(std::string new_name, Point new_location, int new_hit_points, std::string new_type);

    // Methods:
    bool isAlive() const;
    double distance(Character* other) const;
    void hit(int sub_hit_points);
    std::string print() const;
    void virtual attack_victim(Character* victim);

    // Setters and Getters
    std::string getName() const;
    Point getLocation() const;
    void setLocation(Point new_location);
    int getHitPoints() const;
    std::string getType();
    void setType(char new_type);
    bool getTeam();
    void setTeam();
    
    friend std::ostream& operator<<(std::ostream& ost, std::string character_details);
};