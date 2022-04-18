#pragma once

#include "entity/Door.hpp"
#include "game/Location.hpp"
#include "inventory/InventoryItem.hpp"


class Door : public Entity {
public:
    Door(std::string name, std::string description, Location location, std::string key_name);
    ~Door();

    void setKeyName(std::string key_name);

    std::string getKeyName();

    bool interact(Entity& entity) override;

private:
    std::string key_name;
};