#pragma once

#include "entity/Entity.hpp"
#include "game/Object.hpp"


class InventoryItem : public Object {
public:
    enum class ItemType {
        NONE,
        KEY,
        POTION,
        WEAPON,
        HELMET,
        CHESTPLATE,
        LEGGINGS,
        BOOTS,
        ITEM,
    };

    InventoryItem();
    InventoryItem(ItemType type, std::wstring icon, std::wstring name, std::wstring description);
    ~InventoryItem() = default;

    void setItemType(ItemType item_type);
    ItemType getItemType();

    void setDefense(int32_t def);
    int32_t getDefense() const;

    std::wstring getIcon() const;

    virtual void use(Entity& target);

    bool operator< (const InventoryItem &rhs) const;

private:
    ItemType item_type;
    std::wstring icon;

    int32_t defense = 0;
};