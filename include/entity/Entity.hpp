#pragma once
#include <memory>
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
        SIGN,
        PLAYER,
        PORTAL,
        NONE
    };

    Entity(EntityType type, std::string name, std::string descripton, Location location);
    virtual ~Entity();

    EntityType getType() const;
    std::string getIcon() const;

    /* Handle interaction from other entity */
    virtual bool interact(Entity& entity);
    
    /* Deal amount of damage to this entity */
    int32_t hurt(int32_t damage);

    /* Calculate current strike damege. */
    int32_t getDamage();

    /* Setter and Getter */

    void setLocation(Location location);
    void setMaxHealth(int32_t maxHealth);
    void setHealth(int32_t health);
    void setAttack(int32_t attack);
    void setDefense(int32_t defense);
    void setSpeed(int32_t speed);
    void setLuck(float_t luck);

    /* Base attribute getters. */

    Location getLocation();
    int32_t getMaxHealth();
    int32_t getHealth();
    int32_t getAttack();
    int32_t getDefense();
    int32_t getSpeed();
    float_t getLuck();

protected:
    // When this flag is true, the entity will be deleted after the next update.
    EntityType type = EntityType::NONE;

    Location location;

    int32_t max_health = 20;
    int32_t health = 20;
    int32_t defense = 0;
    int32_t attack = 1;
    int32_t speed = 1;
    float_t luck = 1;
};