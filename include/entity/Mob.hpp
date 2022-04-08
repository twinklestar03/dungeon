#pragma once
#include <map>

#include "entity/Entity.hpp"
#include "inventory/Inventory.hpp"


class Mob : public Entity {
public:
    Mob(std::string name, std::string description);

    EntityType getType() override;

    void setInventory(Inventory inventory);
    Inventory getInventory();

    void think();

private:
    Inventory inventory;
};