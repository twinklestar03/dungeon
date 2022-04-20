#pragma once
#include <map>

#include "entity/Entity.hpp"
#include "inventory/InventoryItem.hpp"


class NPC : public Entity {
public:
    NPC(std::wstring name, std::wstring description, Location location);
    ~NPC();

    std::vector<InventoryItem> getInventoryItems() const;
    
    bool interact(Entity& entity) override; 

private:
    std::vector<InventoryItem> product;
    std::map<InventoryItem, uint32_t> purchase_table;
    /* map<ActionName, Result script> */
    std::map<std::wstring, std::wstring> script;
};