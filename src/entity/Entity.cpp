#include "entity/Entity.hpp"

Entity::Entity(EntityType type, std::string name, std::string description, Location location) 
    : Object(name, description), type(type), location(location) {
}

Entity::~Entity() {
}

Entity::EntityType Entity::getType() const {
    return type;
}

void Entity::setLocation(Location location) {
    this->location = location;
}

void Entity::setMaxHealth(uint32_t maxHealth) {
    this->max_health = maxHealth;
}

void Entity::setHealth(uint32_t health) {
    this->health = health;
}

void Entity::setAttack(uint32_t attack) {
    this->attack = attack;
}

void Entity::setDefense(uint32_t defense) {
    this->defense = defense;
}

void Entity::setSpeed(uint32_t speed) {
    this->speed = speed;
}

void Entity::setLuck(float_t luck) {
    this->luck = luck;
}

Location Entity::getLocation() {
    return this->location;
}

uint32_t Entity::getMaxHealth() {
    return this->max_health;
}

uint32_t Entity::getHealth() {
    return this->health;
}

uint32_t Entity::getAttack() {
    return this->attack;
}

uint32_t Entity::getDefense() {
    return this->defense;
}

uint32_t Entity::getSpeed() {
    return this->speed;
}

float_t Entity::getLuck() {
    return this->luck;
}

bool Entity::interact(Entity& entity) {
    return true;
}