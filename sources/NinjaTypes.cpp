#include "OldNinja.hpp"
#include "TrainedNinja.hpp"
#include "YoungNinja.hpp"

YoungNinja::YoungNinja(std::string new_name, Point new_location)
: Ninja(new_name, new_location, 100, 14)
{}

TrainedNinja::TrainedNinja(std::string new_name, Point new_location)
: Ninja(new_name, new_location, 120, 12)
{}

OldNinja::OldNinja(std::string new_name, Point new_location)
: Ninja(new_name, new_location, 150, 8)
{}



