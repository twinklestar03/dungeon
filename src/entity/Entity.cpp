#include "entity/Chest.hpp"
#include "entity/Entity.hpp"
#include "game/GameManager.hpp"

#include <math.h>


Entity::Entity(EntityType type, std::wstring name, std::wstring description, Location location) 
    : Object(name, description), type(type), location(location) {
}

Entity::Entity(EntityType type, std::wstring icon, std::wstring name, std::wstring description, Location location) 
    : Object(name, description), type(type), location(location), icon(icon) {
}

Entity::~Entity() {
    GameManager::getInstance().pushActionMessage(L"DEBUG: Entity (" + this->getName() + L") is being deleted.");
}

Entity::EntityType Entity::getType() const {
    return type;
}

std::wstring Entity::getIcon() const {
    if (icon != L"") {
        return icon;
    }
    
    switch(type) {
        case EntityType::CHEST:
            return L"📦";
        case EntityType::DOOR:
            return L"🚪";
        case EntityType::ITEM:
            return L"㊠";
        case EntityType::MOB:
            return L"👿";
        case EntityType::NPC:
            return L"🥳";
        case EntityType::SIGN:
            return L"🪧";
        case EntityType::PLAYER:
            return L"😎";
        case EntityType::PORTAL:
            return L"✨";
        default:
            return L"❓";
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
    int32_t final_dmg = damage - this->defense;
    this->health -= final_dmg > 0 ? final_dmg : 0;

    // Trigger onDeath event.
    if (this->health <= 0) {
        // Dropping items if the entity is a mob.
        if (this->type == EntityType::MOB) {
            Mob* mob = dynamic_cast<Mob*>(this);
            GameManager::getInstance().addEntity(
                std::make_shared<Chest>(
                    L"Dropped loots",
                    L"Loots from " + this->getName(),
                    mob->getLocation(),
                    mob->getInventory()
                )
            );
        }

        if (this->type == EntityType::PLAYER) {
            GameManager::getInstance().pushActionMessage(L"🤣🤣🤣 You died. 🤔🤔🤔 ");
            GameManager::getInstance().gameOver();
        }
        
        this->setHealth(0);
        this->setDeleted(true);
    }

    return this->health;
}

int32_t Entity::heal(int32_t heal) {
    this->health += heal;

    if (this->health > this->max_health) {
        this->health = this->max_health;
    }

    return this->health;
}

int32_t Entity::getDamage() {
    std::default_random_engine generator( time(NULL) );
    std::uniform_real_distribution<double> unif(0.0, 1.0);
    std::uniform_int_distribution<int32_t> uni_atk(1.2, 2);
    double final_luck = unif(generator) * this->luck;
    
    if (final_luck > 0.8) {
        return attack * uni_atk(generator);
    }
    return attack;
}
