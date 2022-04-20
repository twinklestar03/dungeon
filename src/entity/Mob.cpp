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
    // Search for nearby player.
    Entity& target = GameManager::getInstance().getPlayer();

    Location normalized = (target.getLocation() - this->getLocation()).normailize();
    //GameManager::getInstance().pushActionMessage(L"[DEBUG] (Mob::think) Normalized: ");
    //GameManager::getInstance().pushActionMessage(L"[DEBUG] y: " + std::to_wstring(normalized.getY()) + L" x: " + std::to_wstring(normalized.getX()));
    // Unable to find a path to the player.
    if (!GameManager::getInstance().handleMovement(this, (target.getLocation() - this->getLocation()).normailize() )) {
        return;
    }
    
    // Attack player if capable.
    if (this->getLocation().distance(target.getLocation()) <= 1.5) {
        target.interact(*this);
    }
    
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