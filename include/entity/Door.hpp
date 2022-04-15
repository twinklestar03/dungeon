#pragma once

#include "entity/Door.hpp"
#include "inventory/InventoryItem.hpp"


class Door : public Entity {
public:
    Door(std::string name, std::string description, std::string key_name);
    ~Door();

    bool interact(Entity& entity) override;

private:
    std::string key_name;
};