#include "entity/Flag.hpp"

#include "entity/Player.hpp"
#include "game/GameManager.hpp"


Flag::Flag(std::wstring name, std::wstring description, Location location)
    : Entity(EntityType::FLAG, L"🚩", name, description, location) {
}

bool Flag::interact(Entity& entity) {
    if (entity.getType() == EntityType::PLAYER) {
        Player* player = dynamic_cast<Player*>(&entity);
        if (player == nullptr) {
            return false;
        }

        GameManager::getInstance().gameWin();

    }
    
    return false;
}