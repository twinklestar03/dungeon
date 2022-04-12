#include "entity/Entity.hpp"


Entity::Entity(std::string name, std::string description) : Object(name, description) {

}

Entity::~Entity() {
    
}

Entity::EntityType Entity::getType() {
    return Entity::EntityType::NONE;
}

