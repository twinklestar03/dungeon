#include "entity/Door.hpp"
#include "entity/Player.hpp"

#include "game/GameManager.hpp"


Door::Door(std::wstring name, std::wstring description, Location location, std::wstring key_name)
    : Entity(EntityType::DOOR, name, description, location) {
    this->key_name = key_name;
}

Door::~Door() {
    //GameManager::getInstance().pushActionMessage(L"DEBUG: Door (" + this->getName() + L") is being deleted.");
}

void Door::setKeyName(std::wstring key_name) {
    this->key_name = key_name;
}

std::wstring Door::getKeyName() {
    return key_name;
}

bool Door::interact(Entity& entity) {
    if (entity.getType() == EntityType::PLAYER) {
        Player& player = dynamic_cast<Player&>(entity);
        if (player.getInventory().hasItem(key_name)) {
            player.getInventory().removeItem(key_name);
            GameManager::getInstance().pushActionMessage(L"🔓 You have unlocked the door.");
            this->setDeleted(true);
            return true;
        } else {
            GameManager::getInstance().pushActionMessage(L"🔑 You need a key to open this door.");
            return false;
        }
    }
    
    return false;
}