#pragma once
#include <map>

#include "entity/Entity.hpp"
#include "inventory/Inventory.hpp"


class Player : public Entity {
public:
    Player(std::string name, std::string description, Location location);

    void setInventory(Inventory inventory);
    Inventory getInventory();

    bool interact(Entity& entity) override; 

private:
    Inventory inventory;
};
