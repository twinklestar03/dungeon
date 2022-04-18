#include "inventory/Inventory.hpp"


Inventory::Inventory() {
    item_list = std::vector<InventoryItem>(10);

    weapon = InventoryItem(InventoryItem::ItemType::NONE, "❌", "No Item", "");
    helmet = InventoryItem(InventoryItem::ItemType::NONE, "❌", "No Item", "");
    chestplate = InventoryItem(InventoryItem::ItemType::NONE, "❌", "No Item", "");
    leggings = InventoryItem(InventoryItem::ItemType::NONE, "❌", "No Item", "");
    boots = InventoryItem(InventoryItem::ItemType::NONE, "❌", "No Item", "");
}

Inventory::~Inventory() {
    item_list.clear();
}

bool Inventory::hasItem(InventoryItem item) {
    for (auto& i : item_list) {
        if (i == item) {
            return true;
        }
    }
    return false;
}

bool Inventory::hasItem(std::string item_name) {
    for (auto& i : item_list) {
        if (i.getName() == item_name) {
            return true;
        }
    }
    return false;
}

bool Inventory::hasItem(uint32_t item_id) {
    for (auto& i : item_list) {
        if (i.getUniqueId() == item_id) {
            return true;
        }
    }
    return false;
}

void Inventory::addItem(InventoryItem item) {
    item_list.push_back(item);
}

void Inventory::removeItem(InventoryItem item) {
    if (item_list.size() > 0) {
        for (auto it = item_list.begin(); it != item_list.end(); it++) {
            if (*it == item) {
                item_list.erase(it);
                break;
            }
        }
    }
}

void Inventory::removeItem(std::string item_name) {
    for (auto it = item_list.begin(); it != item_list.end(); it++) {
        if (it->getName() == item_name) {
            item_list.erase(it);
            break;
        }
    }
}

void Inventory::removeItem(uint32_t item_id) {
    for(auto it = item_list.begin(); it != item_list.end(); it++) {
        if (it->getUniqueId() == item_id) {
            item_list.erase(it);
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

std::vector<InventoryItem> Inventory::getItemList() {
    return this->item_list;
}