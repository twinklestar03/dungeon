#include "game/Object.hpp"

Object::Object(std::string name, std::string description) : name(name), description(description) {

}

Object::Object(uint32_t index, std::string name, std::string description) : index(index), name(name), description(description) {

}

void Object::setIndex(uint32_t index) {
    this->index = index;
}

void Object::setName(std::string name) {
    this->name = name;
}

void Object::setDescription(std::string description) {
    this->description = description;
}

uint32_t Object::getIndex() {
    return this->index;
}

std::string Object::getName() {
    return this->name;
}

std::string Object::getDescription() {
    return this->description;
}