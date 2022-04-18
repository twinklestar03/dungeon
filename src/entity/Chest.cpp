#include "entity/Chest.hpp"
#include "entity/Player.hpp"

#include "game/GameManager.hpp"


Chest::Chest(std::string name, std::string description, Location location) : Entity(EntityType::CHEST, name, description, location) {
    this->inventory = std::make_unique<Inventory>();
}

Chest::Chest(std::string name, std::string description, Location location, const Inventory& inventory) : Entity(EntityType::CHEST, name, description, location) {
    this->inventory = std::make_unique<Inventory>(inventory);
}

Chest::Chest(std::string name, std::string description, Location location, const Inventory&& inventory) : Entity(EntityType::CHEST, name, description, location) {
    this->inventory = std::make_unique<Inventory>(std::move(inventory));
}

bool Chest::interact(Entity& entity) {
    if (entity.getType() == EntityType::PLAYER) {
        auto player = dynamic_cast<Player*>(&entity);
        if (player == nullptr) {
            return false;
        }

        if (this->inventory->isEmpty()) {
            GameManager::getInstance().pushActionMessage("The chest is empty.");
        }
        else {
            GameManager::getInstance().pushActionMessage("You zero out the chest.");
            for (auto& item : this->inventory->getItems()) {
                player->getInventory().addItem(item);
                this->inventory->removeItem(item);
            }
        }

        if (this->inventory->getItems().size() < 1) {
            this->setDeleted(true);
        }
    }

    return true;
}