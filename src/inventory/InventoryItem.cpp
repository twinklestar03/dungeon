#include "inventory/InventoryItem.hpp"

#include "entity/Player.hpp"
#include "game/GameManager.hpp"


InventoryItem::InventoryItem() {
    item_type = ItemType::NONE;
    icon = L"❌";
    setName(L"No Item");
    setDescription(L"");
}

InventoryItem::InventoryItem(ItemType type, std::wstring icon, std::wstring name, std::wstring description)
    : Object(name, description), item_type(type), icon(icon) {
}

void InventoryItem::setItemType(ItemType type) {
    item_type = type;
}

InventoryItem::ItemType InventoryItem::getItemType() {
    return item_type;
}

void InventoryItem::setDefense(int32_t def) {
    defense = def;
}

int32_t InventoryItem::getDefense() const {
    return defense;
}

std::wstring InventoryItem::getIcon() const {
    return icon;
}

void InventoryItem::use(Entity& user) {
    if (user.getType() == Entity::EntityType::PLAYER) {
        Player* player = dynamic_cast<Player*>(&user);

        if (player == nullptr) {
            GameManager::getInstance().pushActionMessage(L"[ERROR] [InventoryItem::use]: Player Object cannot be referenced.");
        }

        GameManager::getInstance().pushActionMessage(L"❌ This item cannot be use directly.");
    }
}

bool InventoryItem::operator< (const InventoryItem &rhs) const {
    return this->getUniqueId() < rhs.getUniqueId();
}