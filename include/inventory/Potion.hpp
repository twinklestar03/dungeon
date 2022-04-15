#pragma once

#include "inventory/InventoryItem.hpp"


class Potion : public InventoryItem {
public:
    enum class PotionType {
        HEAL,
        DAMAGE,
        INVISIBLE,
        UNBREAKABLE,
        NONE,
    };

    Potion(std::string name, std::string description, uint32_t level, uint32_t amount);
    ~Potion() = default;

    void setPotionType(PotionType potion_type);
    PotionType getPotionType();

    void use(std::shared_ptr<Entity> target);

private:
    uint32_t level;
    uint32_t amount;
};