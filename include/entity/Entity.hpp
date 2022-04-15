#pragma once

#include <vector>
#include <string>

#include "game/Object.hpp"
#include "game/Location.hpp"


class Entity : public Object {
public:
    enum class EntityType {
        DOOR,
        ITEM,
        MOB,
        NPC,
        PLAYER,
        NONE
    };

    Entity(EntityType type, std::string name, std::string descripton, Location location);
    virtual ~Entity();

    EntityType getType() const;

    /* Handle interaction from other entity */
    virtual bool interact(Entity& entity);

    /* Setter and Getter */

    void setLocation(Location location);
    void setMaxHealth(uint32_t maxHealth);
    void setHealth(uint32_t health);
    void setAttack(uint32_t attack);
    void setDefense(uint32_t defense);
    void setSpeed(uint32_t speed);
    void setLuck(float_t luck);

    Location getLocation();
    uint32_t getMaxHealth();
    uint32_t getHealth();
    uint32_t getAttack();
    uint32_t getDefense();
    uint32_t getSpeed();
    float_t getLuck();

private:
    // When this flag is true, the entity will be deleted after the next update.
    EntityType type = EntityType::NONE;

    Location location;

    uint32_t max_health = 20;
    uint32_t health = 20;
    uint32_t defense = 0;
    uint32_t attack = 1;
    uint32_t speed = 1;
    float_t luck = 1;
};