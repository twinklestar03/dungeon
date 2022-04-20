#include "inventory/Boots.hpp"
#include "entity/Player.hpp"
#include "game/GameManager.hpp"


Boots::Boots(std::wstring name, std::wstring description, int32_t defense)
    : InventoryItem(ItemType::BOOTS, L"🥾", name, description)
{
    this->setDefense(defense);
}

void Boots::use(Entity& user) {
    if (user.getType() == Entity::EntityType::PLAYER) {
        Player* player = dynamic_cast<Player*>(&user);
        if (player == nullptr) {
            GameManager::getInstance().pushActionMessage(L"[ERROR] [Boots::use]: Player Object cannot be referenced.");
        }

        std::shared_ptr<InventoryItem> old = player->getInventory().getBoots();
        if (old != nullptr) {
            player->getInventory().addItem(old);
        }

        player->getInventory().setBoots(player->getInventory().getItem(*this));
        player->getInventory().removeItem(*this);
        player->update();
        GameManager::getInstance().pushActionMessage(L"You equip the " + this->getName() + L".");
    }
}