#include "game/Object.hpp"


uint32_t Object::global_id_counter = 0;

Object::Object(std::wstring name, std::wstring description) : name(name), description(description) {
    this->unique_id = Object::global_id_counter++;
}

void Object::setName(std::wstring name) {
    this->name = name;
}

void Object::setDescription(std::wstring description) {
    this->description = description;
}

void Object::setDeleted(bool deleted) {
    this->is_deleted = deleted;
}

std::wstring Object::getName() const {
    return this->name;
}

std::wstring Object::getDescription() const {
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