#include "entity/Portal.hpp"
#include "entity/Player.hpp"

#include "game/GameManager.hpp"


Portal::Portal(std::wstring name, std::wstring description, Location location) 
    : Entity(EntityType::PORTAL, name, description, location) {
}

Portal::Portal(std::wstring name, std::wstring description, Location location, Location destination) 
    : Entity(EntityType::PORTAL, name, description, location), destination(destination) {
}

void Portal::setDestination(Location destination) {
    this->destination = destination;
}

Location Portal::getDestination() {
    return destination;
}

bool Portal::interact(Entity& entity) {
    if (entity.getType() == EntityType::PLAYER) {
        auto player = dynamic_cast<Player*>(&entity);

        if (player == nullptr) {
            GameManager::getInstance().pushActionMessage(L"[ERROR] [Portal::interact]: Player Object cannot be referenced.");
            return false;
        }

        player->setLocation(destination);
        GameManager::getInstance().pushActionMessage(L"[DEBUG]: Assign player location to" + destination.getRoomName());
        GameManager::getInstance().pushActionMessage(L"You enter portal to " + destination.getRoomName());
        return true;
        
    }
    
    return false;
}