#include "inventory/Helmet.hpp"
#include "entity/Player.hpp"
#include "game/GameManager.hpp"


Helmet::Helmet(std::wstring name, std::wstring description, int32_t defense)
    : InventoryItem(ItemType::HELMET, L"🪖", name, description)
{
    this->setDefense(defense);
}

void Helmet::use(Entity& user) {
    if (user.getType() == Entity::EntityType::PLAYER) {
        Player* player = dynamic_cast<Player*>(&user);
        if (player == nullptr) {
            GameManager::getInstance().pushActionMessage(L"[ERROR] [Helmet::use]: Player Object cannot be referenced.");
        }

        std::shared_ptr<InventoryItem> old = player->getInventory().getHelmet();
        if (old != nullptr) {
            player->getInventory().addItem(old);
        }

        player->getInventory().setHelmet(player->getInventory().getItem(*this));
        player->getInventory().removeItem(*this);
        player->update();
        GameManager::getInstance().pushActionMessage(L"You equip the " + this->getName() + L".");
    }
}