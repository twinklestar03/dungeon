#pragma once

#include <vector>
#include <string>

#include "game/Object.hpp"
#include "game/Location.hpp"


class Entity : public Object {
public:
    enum class EntityType {
        ITEM,
        PLAYER,
        MOB,
        NPC,
        NONE
    };

    Entity(std::string name, std::string descripton);

    void damage(uint32_t damage);
    void heal(uint32_t heal);

    virtual EntityType getType();

    // Setter and Getter
    void setDelete(bool delete_);
    void setLocation(Location location);
    void setMaxHealth(uint32_t maxHealth);
    void setHealth(uint32_t health);
    void setAttack(uint32_t attack);
    void setDefense(uint32_t defense);
    void setSpeed(uint32_t speed);
    void setLuck(uint32_t luck);

    bool isDeleted();
    Location getLocation();
    uint32_t getMaxHealth();
    uint32_t getHealth();
    uint32_t getAttack();
    uint32_t getDefense();
    uint32_t getSpeed();
    uint32_t getLuck();

private:
    // When this flag is true, the entity will be deleted after the next update.
    bool is_deleted = false;
    Location loc;

    uint32_t max_health;
    uint32_t health;
    uint32_t defense;
    uint32_t attack;
    uint32_t speed;
    uint32_t luck;
};