#pragma once
#include <map>

#include "inventory/InventoryItem.hpp"


class Inventory {
public:
    Inventory();
    ~Inventory();

    bool hasItem(InventoryItem item);
    bool hasItem(std::string item_name);
    bool hasItem(uint32_t item_id);

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

    std::vector<InventoryItem> getItemList();

private:
    std::vector<InventoryItem> item_list;

    InventoryItem weapon;

    InventoryItem helmet;
    InventoryItem chestplate;
    InventoryItem leggings;
    InventoryItem boots;
};