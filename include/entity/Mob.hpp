#pragma once
#include <map>

#include "entity/Entity.hpp"
#include "inventory/Inventory.hpp"


class Mob : public Entity {
public:
    Mob(std::string name, std::string description, Location location);

    void setInventory(Inventory inventory);
    Inventory getInventory();

    bool interact(Entity& entity) override; 

    // Could implement different thinking strategies for mobs.
    virtual void think();

private:
    Inventory inventory;

    // Once getting hit by a player, threat level increases.
    uint32_t threat_level = 0;
};