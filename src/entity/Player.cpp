#include "entity/Player.hpp"

#include "game/GameManager.hpp"


Player::Player(std::string name, std::string description, Location location)
    : Entity(EntityType::PLAYER, name, description, location) {
    inventory = std::make_unique<Inventory>();
}

void Player::setInventory(const Inventory& inventory) {
    this->inventory = std::make_unique<Inventory>(inventory);
}

void Player::setInventory(const Inventory&& inventory) {
    this->inventory = std::make_unique<Inventory>(std::move(inventory));
}

bool Player::interact(Entity& entity) {
    if (entity.getType() == EntityType::MOB) {
        auto mob = dynamic_cast<Mob*>(&entity);
        if (mob != nullptr) {
            int32_t damage = mob->getDamage();
            int32_t remain_health = this->hurt(damage);
            GameManager::getInstance().pushActionMessage(
                "You been hit for " + std::to_string(damage) + " damage by " + mob->getIcon() + " " + mob->getName());
        }
    }
    return true;
}