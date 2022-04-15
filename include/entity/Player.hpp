#pragma once
#include <random>

#include "entity/Entity.hpp"
#include "entity/Mob.hpp"
#include "inventory/Inventory.hpp"


class Player : public Entity {
public:
    Player(std::string name, std::string description, Location location);

    void setInventory(const Inventory& inventory);
    void setInventory(const Inventory&& inventory);
    Inventory getInventory();

    int32_t getAttack() override;

    bool interact(Entity& entity) override; 

private:
    std::unique_ptr<Inventory> inventory = nullptr;
};
