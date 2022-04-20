#pragma once

#include "inventory/InventoryItem.hpp"


class Leggings : public InventoryItem {
public:
    Leggings(std::wstring name, std::wstring description, int32_t defense);
    ~Leggings() = default;
    
    void use(Entity& user) override;
    
private:
};