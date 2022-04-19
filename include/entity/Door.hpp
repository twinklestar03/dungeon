#pragma once

#include "entity/Door.hpp"
#include "game/Location.hpp"
#include "inventory/InventoryItem.hpp"


class Door : public Entity {
public:
    Door(std::wstring name, std::wstring description, Location location, std::wstring key_name);
    ~Door();

    void setKeyName(std::wstring key_name);

    std::wstring getKeyName();

    bool interact(Entity& entity) override;

private:
    std::wstring key_name;
};