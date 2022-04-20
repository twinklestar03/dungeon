#include "entity/Chest.hpp"
#include "entity/Player.hpp"

#include "game/GameManager.hpp"


Chest::Chest(std::wstring name, std::wstring description, Location location) : Entity(EntityType::CHEST, name, description, location) {
    this->inventory = std::make_unique<Inventory>();
}

Chest::Chest(std::wstring name, std::wstring description, Location location, Inventory& inventory) : Entity(EntityType::CHEST, name, description, location) {
    this->inventory = std::make_unique<Inventory>(inventory);
}

Inventory& Chest::getInventory() {
    return *inventory;
}

bool Chest::interact(Entity& entity) {
    if (entity.getType() == EntityType::PLAYER) {
        auto player = dynamic_cast<Player*>(&entity);
        if (player == nullptr) {
            return false;
        }

        if (this->inventory->isEmpty()) {
            GameManager::getInstance().pushActionMessage(L"The chest is empty.");
        }
        else {
            GameManager::getInstance().pushActionMessage(L"You clear out the chest.");
            for (auto& item : this->inventory->getItems()) {
                player->getInventory().addItem(item);
                this->inventory->removeItem(*item);
            }
        }

        if (this->inventory->getItems().size() < 1) {
            this->setDeleted(true);
        }
    }

    return true;
}