#pragma once

#include "entity/Entity.hpp"
#include "game/Object.hpp"


class InventoryItem : public Object {
public:
    enum class ItemType {
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
    InventoryItem(ItemType type, std::string icon, std::string name, std::string description);
    ~InventoryItem() = default;

    void setItemType(ItemType item_type);
    ItemType getItemType();

    virtual void use(std::shared_ptr<Entity> target);

    bool operator< (const InventoryItem &rmhs) const;

private:
    ItemType item_type;
    std::string icon;
};