#pragma once
#include <map>

#include "entity/Entity.hpp"
#include "inventory/Inventory.hpp"


class Player : public Entity {
public:
    Player(std::string name, std::string description);

    EntityType getType() override;

    void setInventory(Inventory inventory);
    Inventory getInventory();

private:
    Inventory inventory;
};
