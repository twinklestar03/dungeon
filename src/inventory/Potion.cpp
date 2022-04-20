#include "inventory/Potion.hpp"

#include "entity/Player.hpp"
#include "game/GameManager.hpp"


Potion::Potion(PotionType type, std::wstring name, std::wstring description, uint32_t level, uint32_t amount) : InventoryItem(ItemType::POTION, L"🧪", name, description), potion_type(type), level(level), amount(amount) {
}

void Potion::setPotionType(PotionType potion_type) {
    this->potion_type = potion_type;
}

Potion::PotionType Potion::getPotionType() {
    return potion_type;
}

void Potion::use(Entity& target) {
    if (target.getType() == Entity::EntityType::PLAYER) {
        Player* player = dynamic_cast<Player*>(&target);

        if (player == nullptr) {
            GameManager::getInstance().pushActionMessage(L"[ERROR] [Potion::use]: Player Object cannot be referenced.");
            return;
        }

        int32_t remain;
        // TODO: Implement potion use.
        switch (potion_type) {
            case PotionType::HEAL: 
                remain = player->heal(amount * level);
                player->getInventory().removeItem(*this);
                GameManager::getInstance().pushActionMessage(L"You drink a potion of healing.");
                GameManager::getInstance().pushActionMessage(L"You now have ❤️ " + std::to_wstring(remain));
                break;
            case PotionType::NONE:
                break;
        }

    }
}