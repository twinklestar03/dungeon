#include "inventory/Inventory.hpp"


Inventory::Inventory() {
    items_map = std::map<InventoryItem, uint32_t>();

    weapon = InventoryItem(InventoryItem::ItemType::NONE, "X", "", "");
    helmet = InventoryItem(InventoryItem::ItemType::NONE, "X", "", "");
    chestplate = InventoryItem(InventoryItem::ItemType::NONE, "X", "", "");
    leggings = InventoryItem(InventoryItem::ItemType::NONE, "X", "", "");
    boots = InventoryItem(InventoryItem::ItemType::NONE, "X", "", "");
}

Inventory::~Inventory() {
    items_map.clear();
}

void Inventory::addItem(InventoryItem item) {
    if (items_map.find(item) == items_map.end()) {
        items_map[item] = 1;
    } else {
        items_map[item]++;
    }
}

void Inventory::removeItem(InventoryItem item) {
    if (items_map.find(item) != items_map.end()) {
        items_map[item]--;
        if (items_map[item] == 0) {
            items_map.erase(item);
        }
    }
}

void Inventory::removeItem(std::string item_name) {
    for (auto it = items_map.begin(); it != items_map.end(); it++) {
        if (((Object) it->first).getName() == item_name) {
            items_map[it->first]--;
            if (items_map[it->first] == 0) {
                items_map.erase(it);
            }
            break;
        }
    }
}

void Inventory::removeItem(uint32_t item_id) {
    for (auto it = items_map.begin(); it != items_map.end(); it++) {
        if (((Object)it->first).getUniqueId() == item_id) {
            items_map[it->first]--;
            if (items_map[it->first] == 0) {
                items_map.erase(it);
            }
            break;
        }
    }
}

void Inventory::setHelmet(InventoryItem helmet) {
    if (helmet.getItemType() == InventoryItem::ItemType::HELMET) {
        this->helmet = helmet;
    }
}

void Inventory::setChestplate(InventoryItem chestplate) {
    if (chestplate.getItemType() == InventoryItem::ItemType::CHESTPLATE) {
        this->chestplate = chestplate;
    }
}

void Inventory::setLeggings(InventoryItem leggings) {
    if (leggings.getItemType() == InventoryItem::ItemType::LEGGINGS) {
        this->leggings = leggings;
    }
}

void Inventory::setBoots(InventoryItem boots) {
    if (boots.getItemType() == InventoryItem::ItemType::BOOTS) {
        this->boots = boots;
    }
}

void Inventory::setWeapon(InventoryItem weapon) {
    if (weapon.getItemType() == InventoryItem::ItemType::WEAPON) {
        this->weapon = weapon;
    }
}

InventoryItem Inventory::getHelmet() {
    return this->helmet;
}

InventoryItem Inventory::getChestplate() {
    return this->chestplate;
}

InventoryItem Inventory::getLeggings() {
    return this->leggings;
}

InventoryItem Inventory::getBoots() {
    return this->boots;
}

InventoryItem Inventory::getWeapon() {
    return this->weapon;
}  

std::map<InventoryItem, uint32_t> Inventory::getItemsMap() {
    return this->items_map;
}