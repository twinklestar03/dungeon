#pragma once

#include "entity/Entity.hpp"
#include "game/Location.hpp"


class Portal : public Entity {
public:
    Portal(std::wstring name, std::wstring description, Location location);
    Portal(std::wstring name, std::wstring description, Location location, Location destination);

    void setDestination(Location destination);
    Location getDestination();

    bool interact(Entity& entity) override; 

private:
    Location destination;
};
