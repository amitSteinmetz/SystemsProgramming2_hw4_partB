#include "Character.hpp"

using namespace std;

/* Ctor */ 

Character::Character(std::string new_name, Point new_location, int new_hit_points, std::string new_type)
: name(new_name), location(new_location), hit_points(new_hit_points), type(new_type)
{}

/* Methods */

bool Character::isAlive() const
{
    if (hit_points > 0) return true;

    return false;
}

double Character::distance(Character* other) const
{
    return location.distance(other->location);
}

void Character::hit(int sub_hit_points)
{
    if (sub_hit_points < 0) throw invalid_argument("Amount of points to subtract has to be non-negative!");
    
    if (hit_points - sub_hit_points < 0) hit_points = 0;

    else hit_points -= sub_hit_points;
}

std::string Character::getName() const
{
    return name;
}

Point Character::getLocation() const
{
    return location;
}

string Character::print() const
{
    string character_details = type + " ";

    if (!isAlive()) character_details += "(" + name + ")";
    else character_details += name;

    if (hit_points > 0) character_details += (", " + to_string(hit_points));

    character_details += (", " + location.print());

    return character_details;
}

std::ostream& operator<<(std::ostream& ost, std::string character_details)
{
    ost << character_details;
    return ost;
}

int Character::getHitPoints() const
{
    return hit_points;
}

void Character::setType(char new_type)
{
    type = new_type;
}

void Character::setLocation(Point new_location)
{
    location = new_location;
}

void Character::setTeam()
{
    in_team = true;
}

bool Character::getTeam()
{
    return in_team;
}

std::string Character::getType()
{
    return type;
}

void Character::attack_victim(Character* victim)
{
    return;
}