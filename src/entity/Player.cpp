#include "entity/Player.hpp"

#include "game/GameManager.hpp"


Player::Player(std::wstring name, std::wstring description, Location location)
    : Entity(EntityType::PLAYER, name, description, location) {
    inventory = std::make_unique<Inventory>();
}

void Player::setInventory(const Inventory& inventory) {
    this->inventory = std::make_unique<Inventory>(inventory);
}

void Player::setInventory(const Inventory&& inventory) {
    this->inventory = std::make_unique<Inventory>(std::move(inventory));
}

Inventory& Player::getInventory() {
    return *inventory;
}

bool Player::interact(Entity& entity) {
    if (entity.getType() == EntityType::MOB) {
        auto mob = dynamic_cast<Mob*>(&entity);
        if (mob != nullptr) {
            int32_t damage = mob->getDamage();
            int32_t remain_health = this->hurt(damage);
            GameManager::getInstance().pushActionMessage(
                L"You been hit for " + std::to_wstring(damage) + L" damage by " + mob->getIcon() + L" " + mob->getName());
            GameManager::getInstance().pushActionMessage(
                L"Your remain ❤️ " + std::to_wstring(remain_health));
        }
    }
    return true;
}