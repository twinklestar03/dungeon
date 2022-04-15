#pragma once

#include "inventory/InventoryItem.hpp"


class Weapon : public InventoryItem {
public:
    enum class WeaponType {
        SWORD,
        AXE,
        BOW,
        NONE,
    };

    Weapon(std::string name, std::string description, uint32_t level, uint32_t base);
    ~Weapon() = default;

    void setWeaponType(WeaponType weapon_type);
    WeaponType getWeaponType();
    uint32_t getDamage();

private:
    WeaponType type;
    uint32_t level;
    uint32_t base;
};