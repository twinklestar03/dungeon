#include "entity/Item.hpp"
#include "entity/Player.hpp"

#include "game/GameManager.hpp"


Item::Item(std::wstring name, std::wstring description, Location location, InventoryItem& item) : Entity(EntityType::ITEM, name, description, location) {
    this->item = std::make_shared<InventoryItem>(item);
}

Item::~Item() {
}

bool Item::interact(Entity& entity) {
    if (entity.getType() == EntityType::PLAYER) {
        Player* player = dynamic_cast<Player*>(&entity);

        if (player == nullptr) {
            GameManager::getInstance().pushActionMessage(L"[ERROR] [Item::interact]: Player Object cannot be referenced.");
            return false;
        }

        GameManager::getInstance().pushActionMessage(L"You pick up the " + this->getName());
        player->getInventory().addItem(*item);
        this->setDeleted(true);

        return true;
    }
    return false;
}