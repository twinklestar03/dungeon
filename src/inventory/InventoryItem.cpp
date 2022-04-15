#include "inventory/InventoryItem.hpp"


InventoryItem::InventoryItem(ItemType type, std::string icon, std::string name, std::string description)
    : item_type(type), icon(icon), Object(name, description) {
}

void InventoryItem::setItemType(ItemType type) {
    item_type = type;
}

InventoryItem::ItemType InventoryItem::getItemType() {
    return item_type;
}

void InventoryItem::use(std::shared_ptr<Entity> target) {
}

bool InventoryItem::operator< (const InventoryItem &rhs) const {
    return this->getUniqueId() < rhs.getUniqueId();
}