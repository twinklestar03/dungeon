#include "inventory/Inventory.hpp"


Inventory::Inventory() {
    item_list = std::vector<std::shared_ptr<InventoryItem>>();

    weapon = InventoryItem();
    helmet = InventoryItem();
    chestplate = InventoryItem();
    leggings = InventoryItem();
    boots = InventoryItem();
}

Inventory::~Inventory() {
    item_list.clear();
}

bool Inventory::isEmpty() {
    return item_list.empty();
}

bool Inventory::hasItem(InventoryItem item) {
    for (auto& i : item_list) {
        if (*i == item) {
            return true;
        }
    }
    return false;
}

bool Inventory::hasItem(std::wstring item_name) {
    for (auto& i : item_list) {
        if (i->getName() == item_name) {
            return true;
        }
    }
    return false;
}

bool Inventory::hasItem(uint32_t item_id) {
    for (auto& i : item_list) {
        if (i->getUniqueId() == item_id) {
            return true;
        }
    }
    return false;
}

bool Inventory::addItem(InventoryItem item) {
    if (item_list.size() < INVENTORY_SIZE) {
        item_list.push_back(std::make_shared<InventoryItem>(item));
        return true;
    }
    return false;
}

bool Inventory::addItem(std::shared_ptr<InventoryItem> item) {
    if (item_list.size() < INVENTORY_SIZE) {
        item_list.push_back(item);
        return true;
    }
    return false;
}

void Inventory::removeItem(InventoryItem item) {
    for (auto it = item_list.begin(); it != item_list.end(); it++) {
        if (**it == item) {
            item_list.erase(it);
            break;
        }
    }
}

void Inventory::removeItem(std::wstring item_name) {
    for (auto it = item_list.begin(); it != item_list.end(); it++) {
        if ((*it)->getName() == item_name) {
            item_list.erase(it);
            break;
        }
    }
}

void Inventory::removeItem(uint32_t item_id) {
    for(auto it = item_list.begin(); it != item_list.end(); it++) {
        if ((*it)->getUniqueId() == item_id) {
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

std::vector<std::shared_ptr<InventoryItem>> Inventory::getItems() {
    return this->item_list;
}

void Inventory::clear() {
    this->item_list.clear();
}