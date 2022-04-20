#include "entity/NPC.hpp"
#include "game/GameManager.hpp"


NPC::NPC(std::wstring name, std::wstring description, Location location)
    : Entity(EntityType::NPC, name, description, location) {
}

NPC::~NPC() {
    GameManager::getInstance().pushActionMessage(L"DEBUG: NPC (" + this->getName() + L") is being deleted.");
}

bool NPC::interact(Entity& entity) {
    if (entity.getType() == EntityType::PLAYER) {
        auto player = dynamic_cast<Player*>(&entity);
        if (player == nullptr) {
            GameManager::getInstance().pushActionMessage(L"[ERROR] (NPC::interact): Player object cannot be referenced.");
            return false;
        }

        

    }
    return true;
}