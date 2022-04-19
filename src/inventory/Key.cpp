#include "inventory/Key.hpp"

#include "game/GameManager.hpp"


Key::Key(std::wstring name, std::wstring description)
    : InventoryItem(ItemType::KEY, L"🔑", name, description) {
}

void Key::use(Entity& user) {
    if (user.getType() == Entity::EntityType::PLAYER) {
        Player* player = dynamic_cast<Player*>(&user);

        if (player == nullptr) {
            GameManager::getInstance().pushActionMessage(L"[ERROR] [Key::use]: Player Object cannot be referenced.");
        }

        GameManager::getInstance().pushActionMessage(L"❌ This item cannot be use directly.");
    }
    
} 