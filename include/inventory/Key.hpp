#pragma once

#include "inventory/InventoryItem.hpp"


class Key : public InventoryItem {
public:
    Key(std::wstring name, std::wstring description);
    ~Key() = default;

    void use(Entity& user) override;

private:
};