#include "entity/Mob.hpp"

#include "game/GameManager.hpp"


Mob::Mob(std::string name, std::string description, Location location)
    : Entity(EntityType::MOB, name, description, location) {
    std::cerr << "DEBUG: Mob (" << this->getName() << ") is being created." << std::endl;
    inventory = std::make_unique<Inventory>();
}

Mob::Mob(std::string icon, std::string name, std::string description, Location location)
    : Entity(EntityType::MOB, icon, name, description, location) {
    std::cerr << "DEBUG: Mob (" << this->getName() << ") is being created." << std::endl;
    inventory = std::make_unique<Inventory>();
}

Inventory& Mob::getInventory() const {
    return *inventory;
}

void Mob::think(std::vector<std::shared_ptr<Object>> objects) {
    // TODO: AI Logic.
}

bool Mob::interact(Entity& entity) {
    // Getting damaged by player.
    if (entity.getType() == EntityType::PLAYER) {
        auto player = dynamic_cast<Player*>(&entity);
        if (player == nullptr) {
            return false;
        }

        int32_t damage = player->getDamage();
        int32_t remain_health = this->hurt(damage);
        std::cout << "You hit " << this->getName() << " for " << damage << " damage." << std::endl;

        if (remain_health <= 0) {
            GameManager::getInstance().pushActionMessage("😎😎😎🈹 You killed " + this->getName());
            this->setHealth(0);
            this->brain = ThinkState::DEAD;

            this->setDeleted(true);
        } 
        else {
            GameManager::getInstance().pushActionMessage(this->getName() + " has " + std::to_string(this->getHealth()) + " ❤️ health left");
            this->brain = ThinkState::IDLE;
        }

        return true;

    }
    return false;
}