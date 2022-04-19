#pragma once
#include <string>
#include <iostream>

#include "entity/Entity.hpp"
#include "inventory/Inventory.hpp"


class Mob : public Entity {
public:
    enum class ThinkState {
        IDLE,
        MOVE,
        ATTACK,
        FLEEING,
        DEAD,
    };

    Mob(std::wstring name, std::wstring description, Location location);
    Mob(std::wstring icon, std::wstring name, std::wstring description, Location location);

    void setInventory(const Inventory& inventory);
    Inventory& getInventory();

    // Implement different thinking strategies for mobs.
    virtual void think(std::vector<std::shared_ptr<Entity>> entity_list);

    virtual bool interact(Entity& entity) override; 

private:
    std::unique_ptr<Inventory> inventory;

    // Once getting hit by a player, threat level increases.
    uint32_t threat_level = 0;
    // Thinking state.
    ThinkState brain = ThinkState::IDLE;
};