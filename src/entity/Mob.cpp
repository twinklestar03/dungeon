#include "entity/Mob.hpp"
#include "entity/Player.hpp"
#include "game/GameManager.hpp"


Mob::Mob(std::wstring name, std::wstring description, Location location)
    : Entity(EntityType::MOB, name, description, location) {
    inventory = std::make_unique<Inventory>();
}

Mob::Mob(std::wstring icon, std::wstring name, std::wstring description, Location location)
    : Entity(EntityType::MOB, icon, name, description, location) {
    inventory = std::make_unique<Inventory>();
}

void Mob::setInventory(const Inventory& inventory) {
    this->inventory = std::make_unique<Inventory>(inventory);
}

Inventory& Mob::getInventory() {
    return *inventory;
}

void Mob::think(std::vector<std::shared_ptr<Entity>> entity_list) {
    // TODO: AI Logic.

    // TODO: Search for nearby player.
    // TODO: Attack player if capable.
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
        //std::cout << "You hit " << this->getName() << " for " << damage << " damage." << std::endl;
        GameManager::getInstance().pushActionMessage(
            L"You hit " + this->getIcon() + L" " + this->getName() + L" for " + std::to_wstring(damage) + L" damage.");

        if (remain_health <= 0) {
            GameManager::getInstance().pushActionMessage(L"😎😎😎🈹 You killed " + this->getName());
            this->brain = ThinkState::DEAD;
        } 
        else {
            GameManager::getInstance().pushActionMessage(this->getName() + L" has " + std::to_wstring(this->getHealth()) + L" ❤️ health left");
            this->brain = ThinkState::IDLE;
        }
        return true;
    }
    return false;
}