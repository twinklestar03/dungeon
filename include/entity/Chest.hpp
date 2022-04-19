#pragma once
#include "entity/Entity.hpp"
#include "inventory/Inventory.hpp"


class Chest : public Entity {
public:
    Chest(std::wstring name, std::wstring description, Location location);
    Chest(std::wstring name, std::wstring description, Location location, Inventory& inventory);

    ~Chest() = default;

    void setInventory(const Inventory& inventory);

    Inventory& getInventory();

    bool interact(Entity& entity) override;

private:
    std::unique_ptr<Inventory> inventory = nullptr;
};