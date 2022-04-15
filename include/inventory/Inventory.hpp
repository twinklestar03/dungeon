#pragma once
#include <map>

#include "inventory/InventoryItem.hpp"


class Inventory {
public:
    Inventory();
    ~Inventory();

    void addItem(InventoryItem item);

    void removeItem(InventoryItem item);
    void removeItem(std::string item_name);
    void removeItem(uint32_t item_id);

    void setHelmet(InventoryItem helmet);
    void setChestplate(InventoryItem chestplate);
    void setLeggings(InventoryItem leggings);
    void setBoots(InventoryItem boots);
    void setWeapon(InventoryItem weapon);

    InventoryItem getHelmet();
    InventoryItem getChestplate();
    InventoryItem getLeggings();
    InventoryItem getBoots();
    InventoryItem getWeapon();

    std::map<InventoryItem, uint32_t> getItemsMap();

private:
    std::map<InventoryItem, uint32_t> items_map;

    InventoryItem weapon;

    InventoryItem helmet;
    InventoryItem chestplate;
    InventoryItem leggings;
    InventoryItem boots;
};