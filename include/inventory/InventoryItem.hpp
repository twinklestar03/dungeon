#pragma once

#include "entity/Entity.hpp"
#include "game/Object.hpp"


class InventoryItem : public Object {
public:
    enum class ItemType {
        KEY,
        POTION,
        WEAPON,
        HELMET,
        CHESTPLATE,
        LEGGINGS,
        BOOTS,
        ITEM,
        NONE,
    };

    InventoryItem();
    InventoryItem(ItemType type, std::wstring icon, std::wstring name, std::wstring description);
    ~InventoryItem() = default;

    void setItemType(ItemType item_type);
    ItemType getItemType();

    virtual void use(Entity& target);

    bool operator< (const InventoryItem &rhs) const;

private:
    ItemType item_type;
    std::wstring icon;
};