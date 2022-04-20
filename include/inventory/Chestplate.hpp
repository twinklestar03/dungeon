#pragma once

#include "inventory/InventoryItem.hpp"


class Chestplate : public InventoryItem {
public:
    Chestplate(std::wstring name, std::wstring description, int32_t defense);
    ~Chestplate() = default;
    
    void use(Entity& user) override;
    
private:
};