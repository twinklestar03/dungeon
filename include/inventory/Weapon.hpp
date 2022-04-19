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

    Weapon(std::wstring name, std::wstring description, uint32_t level, uint32_t base);
    ~Weapon() = default;

    void setWeaponType(WeaponType weapon_type);
    WeaponType getWeaponType();
    uint32_t getDamage();

    void use(Entity& target);

private:
    WeaponType type;
    uint32_t level;
    uint32_t base;
};