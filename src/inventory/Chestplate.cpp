#include "inventory/Chestplate.hpp"
#include "entity/Player.hpp"
#include "game/GameManager.hpp"


Chestplate::Chestplate(std::wstring name, std::wstring description, int32_t defense)
    : InventoryItem(ItemType::CHESTPLATE, L"🦺", name, description)
{
    this->setDefense(defense);
}

void Chestplate::use(Entity& user) {
    if (user.getType() == Entity::EntityType::PLAYER) {
        Player* player = dynamic_cast<Player*>(&user);
        if (player == nullptr) {
            GameManager::getInstance().pushActionMessage(L"[ERROR] [Chestplate::use]: Player Object cannot be referenced.");
        }

        std::shared_ptr<InventoryItem> old = player->getInventory().getChestplate();
        if (old != nullptr) {
            player->getInventory().addItem(old);
        }

        player->getInventory().setChestplate(player->getInventory().getItem(*this));
        player->getInventory().removeItem(*this);
        player->update();
        GameManager::getInstance().pushActionMessage(L"You equip the " + this->getName() + L".");
    }
}