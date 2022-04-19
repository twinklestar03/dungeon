#pragma once
#include <memory>
#include <vector>
#include <string>

#include "game/Object.hpp"
#include "game/Location.hpp"


class Entity : public Object {
public:
    enum class EntityType {
        CHEST,
        DOOR,
        ITEM,
        MOB,
        NPC,
        SIGN,
        PLAYER,
        PORTAL,
        NONE
    };

    Entity(EntityType type, std::wstring name, std::wstring descripton, Location location);
    Entity(EntityType type, std::wstring icon, std::wstring name, std::wstring descripton, Location location);
    virtual ~Entity();

    EntityType getType() const;
    std::wstring getIcon() const;

    void setLocation(Location location);
    void setMaxHealth(int32_t maxHealth);
    void setHealth(int32_t health);
    void setAttack(int32_t attack);
    void setDefense(int32_t defense);
    void setSpeed(int32_t speed);
    void setLuck(float_t luck);

    Location getLocation();
    int32_t getMaxHealth();
    int32_t getHealth();
    int32_t getAttack();
    int32_t getDefense();
    int32_t getSpeed();
    float_t getLuck();

    /* Deal amount of damage to this entity */
    int32_t hurt(int32_t damage);
    int32_t heal(int32_t heal);

    /* Calculate current strike damege. */
    int32_t getDamage();

    /* Handle interaction from other entity */
    virtual bool interact(Entity& entity);

protected:
    // When this flag is true, the entity will be deleted after the next update.
    EntityType type = EntityType::NONE;

    Location location;

    std::wstring icon = L"";

    int32_t max_health = 20;
    int32_t health = 20;
    int32_t defense = 0;
    int32_t attack = 1;
    int32_t speed = 1;
    float_t luck = 1;
};