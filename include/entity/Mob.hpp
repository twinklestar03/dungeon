#pragma once
#include <string>
#include <iostream>

#include "entity/Entity.hpp"
#include "entity/Player.hpp"
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

    Mob(std::string name, std::string description, Location location);

    void setInventory(Inventory inventory);
    Inventory& getInventory() const;

    // Implement different thinking strategies for mobs.
    virtual void think(std::vector<std::shared_ptr<Object>> objects);

    bool interact(Entity& entity) override; 

private:
    std::unique_ptr<Inventory> inventory;

    // Once getting hit by a player, threat level increases.
    uint32_t threat_level = 0;
    // Thinking state.
    ThinkState brain = ThinkState::IDLE;
};