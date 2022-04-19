#pragma once
#include <random>

#include "entity/Entity.hpp"
#include "entity/Mob.hpp"
#include "inventory/Inventory.hpp"


class Player : public Entity {
public:
    Player(std::wstring name, std::wstring description, Location location);

    void setInventory(const Inventory& inventory);
    void setInventory(const Inventory&& inventory);
    Inventory& getInventory();

    bool interact(Entity& entity) override; 

private:
    std::unique_ptr<Inventory> inventory = nullptr;
};
