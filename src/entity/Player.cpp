#include "entity/Player.hpp"


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

int32_t Player::getAttack() {
    std::default_random_engine generator( time(NULL) );
    std::uniform_real_distribution<float> unif(0.0, 1.0);
    float final_luck = unif(generator) * this->luck;

    if (final_luck > 0.5) {
        return attack * 2;
    }

    return attack;
}

bool Player::interact(Entity& entity) {
    if (entity.getType() == EntityType::MOB) {
        auto mob = dynamic_cast<Mob*>(&entity);
        if (mob != nullptr) {
            uint32_t damage = mob->getAttack();
        }
    }
    return true;
}