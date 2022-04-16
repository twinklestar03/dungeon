#include "game/Object.hpp"


uint32_t Object::global_id_counter = 0;

Object::Object(std::string name, std::string description) : name(name), description(description) {
    this->unique_id = Object::global_id_counter++;
}

void Object::setName(std::string name) {
    this->name = name;
}

void Object::setDescription(std::string description) {
    this->description = description;
}

void Object::setDeleted(bool deleted) {
    this->is_deleted = deleted;
}

std::string Object::getName() const {
    return this->name;
}

std::string Object::getDescription() const {
    return this->description;
}

uint32_t Object::getUniqueId() const {
    return this->unique_id;
}

bool Object::isDeleted() const {
    return this->is_deleted;
}

bool Object::operator< (Object &rhs) const {
    return this->unique_id < rhs.unique_id;
}

bool Object::operator== (Object &rhs) const {
    if (this->unique_id == rhs.unique_id) {
        return true;
    }

    if (this->name == rhs.name) {
        return true;
    }
    
    return false;
}