#include "entity/Entity.hpp"

#include "game/GameManager.hpp"


Entity::Entity(EntityType type, std::string name, std::string description, Location location) 
    : Object(name, description), type(type), location(location) {
}

Entity::Entity(EntityType type, std::string icon, std::string name, std::string description, Location location) 
    : Object(name, description), type(type), location(location), icon(icon) {
}

Entity::~Entity() {
    GameManager::getInstance().pushActionMessage("DEBUG: Entity (" + this->getName() + ") is being deleted.");
}

Entity::EntityType Entity::getType() const {
    return type;
}

std::string Entity::getIcon() const {
    if (icon != "") {
        return icon;
    }
    
    switch(type) {
        case EntityType::DOOR:
            return "🚪";
        case EntityType::ITEM:
            return "㊠";
        case EntityType::MOB:
            return "👿";
        case EntityType::NPC:
            return "🥳";
        case EntityType::SIGN:
            return "🪧";
        case EntityType::PLAYER:
            return "😎";
        case EntityType::PORTAL:
            return "✨";
        default:
            return "❓";
    }
}

void Entity::setLocation(Location location) {
    this->location = location;
}

void Entity::setMaxHealth(int32_t maxHealth) {
    this->max_health = maxHealth;
}

void Entity::setHealth(int32_t health) {
    this->health = health;
}

void Entity::setAttack(int32_t attack) {
    this->attack = attack;
}

void Entity::setDefense(int32_t defense) {
    this->defense = defense;
}

void Entity::setSpeed(int32_t speed) {
    this->speed = speed;
}

void Entity::setLuck(float_t luck) {
    this->luck = luck;
}

Location Entity::getLocation() {
    return this->location;
}

int32_t Entity::getMaxHealth() {
    return this->max_health;
}

int32_t Entity::getHealth() {
    return this->health;
}

int32_t Entity::getAttack() {
    return this->attack;
}

int32_t Entity::getDefense() {
    return this->defense;
}

int32_t Entity::getSpeed() {
    return this->speed;
}

float_t Entity::getLuck() {
    return this->luck;
}

bool Entity::interact(Entity& entity) {
    return true;
}

int32_t Entity::hurt(int32_t damage) {
    this->health -= damage;
    return this->health;
}

int32_t Entity::getDamage() {
    std::default_random_engine generator( time(NULL) );
    std::uniform_real_distribution<float> unif(0.0, 1.0);
    float final_luck = unif(generator) * this->luck;

    if (final_luck > 0.5) {
        return attack * 2;
    }

    return attack;
}