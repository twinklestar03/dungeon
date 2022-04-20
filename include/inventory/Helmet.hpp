#pragma once

#include "inventory/InventoryItem.hpp"


class Helmet : public InventoryItem {
public:
    Helmet(std::wstring name, std::wstring description, int32_t defense);
    ~Helmet() = default;
    
    void use(Entity& user) override;
    
private:
};