#pragma once
#include <string>

#include "entity/Entity.hpp"
#include "inventory/InventoryItem.hpp"


class Item : public Entity {
public:
    Item(std::wstring name, std::wstring descripton, Location location, InventoryItem& item);
    ~Item();

    bool interact(Entity& entity) override; 

private:
    std::shared_ptr<InventoryItem> item;
};