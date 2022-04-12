#pragma once

#include "entity/Entity.hpp"


class Portal : public Entity {
public:
    Portal(std::string name, std::string description, Location target);

    EntityType getType();

    Location getTarget();

    void setTarget(Location target);

    // Teleport the entity on the same location
    void doTeleport(Entity& entity);

private:
    Location target;
};