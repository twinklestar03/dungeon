#include "inventory/Inventory.hpp"

#include "game/GameManager.hpp"

Inventory::Inventory() {
    item_list = std::vector<std::shared_ptr<InventoryItem>>();

    weapon = nullptr;
    helmet = nullptr;
    chestplate = nullptr;
    leggings = nullptr;
    boots = nullptr;
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

void Inventory::setHelmet(std::shared_ptr<InventoryItem> helmet) {
    if (helmet != nullptr) {
        this->helmet = helmet;
    }
}

void Inventory::setChestplate(std::shared_ptr<InventoryItem> chestplate) {
    if (chestplate != nullptr) {
        this->chestplate = chestplate;
    }
}

void Inventory::setLeggings(std::shared_ptr<InventoryItem> leggings) {
    if (leggings != nullptr) {
        this->leggings = leggings;
    }
}

void Inventory::setBoots(std::shared_ptr<InventoryItem> boots) {
    if (boots != nullptr) {
        this->boots = boots;
    }
}

void Inventory::setWeapon(std::shared_ptr<InventoryItem> weapon) {
    if (weapon != nullptr) {
        this->weapon = weapon;
    }
}

std::shared_ptr<InventoryItem> Inventory::getItem(InventoryItem item) {
    for (auto& i : item_list) {
        if (*i == item) {
            return i;
        }
    }
    return nullptr;
}

std::shared_ptr<InventoryItem> Inventory::getHelmet() {
    return this->helmet;
}

std::shared_ptr<InventoryItem> Inventory::getChestplate() {
    return this->chestplate;
}

std::shared_ptr<InventoryItem> Inventory::getLeggings() {
    return this->leggings;
}

std::shared_ptr<InventoryItem> Inventory::getBoots() {
    return this->boots;
}

std::shared_ptr<InventoryItem> Inventory::getWeapon() {
    return this->weapon;
}

std::vector<std::shared_ptr<InventoryItem>> Inventory::getItems() {
    return this->item_list;
}

void Inventory::clear() {
    this->item_list.clear();
}