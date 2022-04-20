#pragma once
#include <memory>
#include <vector>

#include "inventory/InventoryItem.hpp"
#include "inventory/Helmet.hpp"


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

    void setHelmet(std::shared_ptr<InventoryItem> helmet);
    void setChestplate(std::shared_ptr<InventoryItem> chestplate);
    void setLeggings(std::shared_ptr<InventoryItem> leggings);
    void setBoots(std::shared_ptr<InventoryItem> boots);
    void setWeapon(std::shared_ptr<InventoryItem> weapon);

    std::shared_ptr<InventoryItem> getItem(InventoryItem item);

    std::shared_ptr<InventoryItem> getHelmet();
    std::shared_ptr<InventoryItem> getChestplate();
    std::shared_ptr<InventoryItem> getLeggings();
    std::shared_ptr<InventoryItem> getBoots();
    std::shared_ptr<InventoryItem> getWeapon();

    std::vector<std::shared_ptr<InventoryItem>> getItems();

    void clear();

private:
    std::vector<std::shared_ptr<InventoryItem>> item_list;

    std::shared_ptr<InventoryItem> weapon = nullptr;

    std::shared_ptr<InventoryItem> helmet = nullptr;
    std::shared_ptr<InventoryItem> chestplate = nullptr;
    std::shared_ptr<InventoryItem> leggings = nullptr;
    std::shared_ptr<InventoryItem> boots = nullptr;
};