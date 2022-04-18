#pragma once
#include "entity/Entity.hpp"
#include "inventory/Inventory.hpp"


class Chest : public Entity {
public:
    Chest(std::string name, std::string description, Location location);
    Chest(std::string name, std::string description, Location location, const Inventory& inventory);
    Chest(std::string name, std::string description, Location location, const Inventory&& inventory);
    ~Chest() = default;

    void setInventory(const Inventory& inventory);

    Inventory& getInventory();

    bool interact(Entity& entity) override;

private:
    std::unique_ptr<Inventory> inventory = nullptr;
};