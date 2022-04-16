#include "inventory/InventoryItem.hpp"


InventoryItem::InventoryItem() {
    item_type = ItemType::NONE;
    icon = "❌";
    setName("No Item");
    setDescription("");
}

InventoryItem::InventoryItem(ItemType type, std::string icon, std::string name, std::string description)
    : Object(name, description), item_type(type), icon(icon) {
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