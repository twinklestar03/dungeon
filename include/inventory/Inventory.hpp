#pragma once
#include <memory>
#include <vector>

#include "inventory/InventoryItem.hpp"

#define INVENTORY_SIZE 50

class Inventory {
public:
    Inventory();
    ~Inventory();

    bool isEmpty();

    bool hasItem(InventoryItem item);
    bool hasItem(std::wstring item_name);
    bool hasItem(uint32_t item_id);

    /* Return true if item was added. */
    bool addItem(InventoryItem item);
    bool addItem(std::shared_ptr<InventoryItem> item);

    void removeItem(InventoryItem item);
    void removeItem(std::wstring item_name);
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

    std::vector<std::shared_ptr<InventoryItem>> getItems();

    void clear();

private:
    std::vector<std::shared_ptr<InventoryItem>> item_list;

    InventoryItem weapon;

    InventoryItem helmet;
    InventoryItem chestplate;
    InventoryItem leggings;
    InventoryItem boots;
};