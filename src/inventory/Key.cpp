#include "inventory/Key.hpp"

#include "game/GameManager.hpp"


Key::Key(std::string name, std::string description)
    : InventoryItem(ItemType::KEY, "🔑", name, description) {
}

void Key::use(std::shared_ptr<Entity> user) {
    GameManager::getInstance().pushActionMessage("❌ This item cannot be use directly.");
} 