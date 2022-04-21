#pragma once
#include "entity/Entity.hpp"
#include "inventory/Inventory.hpp"


class Flag : public Entity {
public:
    Flag(std::wstring name, std::wstring description, Location location);
    ~Flag() = default;

    bool interact(Entity& entity) override;

private:
};