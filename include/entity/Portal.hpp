#pragma once

#include "entity/Entity.hpp"
#include "game/Location.hpp"


class Portal : public Entity {
public:
    Portal(std::string name, std::string description, Location location);
    Portal(std::string name, std::string description, Location location, Location destination);

    void setDestination(Location destination);
    Location getDestination();

    bool interact(Entity& entity) override; 

private:
    Location destination;
};
