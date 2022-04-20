#include "inventory/Leggings.hpp"
#include "entity/Player.hpp"
#include "game/GameManager.hpp"


Leggings::Leggings(std::wstring name, std::wstring description, int32_t defense)
    : InventoryItem(ItemType::LEGGINGS, L"👖", name, description)
{
    this->setDefense(defense);
}

void Leggings::use(Entity& user) {
    if (user.getType() == Entity::EntityType::PLAYER) {
        Player* player = dynamic_cast<Player*>(&user);
        if (player == nullptr) {
            GameManager::getInstance().pushActionMessage(L"[ERROR] [Helmet::use]: Player Object cannot be referenced.");
        }

        std::shared_ptr<InventoryItem> old = player->getInventory().getLeggings();
        if (old != nullptr) {
            player->getInventory().addItem(old);
        }

        player->getInventory().setLeggings(player->getInventory().getItem(*this));
        player->getInventory().removeItem(*this);
        player->update();
        GameManager::getInstance().pushActionMessage(L"You equip the " + this->getName() + L".");
    }
}