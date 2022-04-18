#pragma once

#include "inventory/InventoryItem.hpp"


class Key : public InventoryItem {
public:
    Key(std::string name, std::string description);
    ~Key() = default;

    void use(std::shared_ptr<Entity> user) override;

private:
};