#pragma once

#include "inventory/InventoryItem.hpp"


class Boots : public InventoryItem {
public:
    Boots(std::wstring name, std::wstring description, int32_t defense);
    ~Boots() = default;
    
    void use(Entity& user) override;
    
private:
};