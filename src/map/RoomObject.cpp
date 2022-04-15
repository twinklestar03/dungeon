#include "map/RoomObject.hpp"


RoomObject::RoomObject(ObjectType type) : type(type) {
}

void RoomObject::setType(ObjectType type) {
    this->type = type;
}

RoomObject::ObjectType RoomObject::getType() {
    return type;
}

std::string RoomObject::getIcon() {
    switch (type) {
        case ObjectType::NONE:
            return "❓";
        case ObjectType::WALL:
            return "\033[38;2;142;142;142m牆\033[0m";
        case ObjectType::DIRT:
            return "\033[38;2;155;118;83m🐾\033[0m";
        case ObjectType::GRASS:
            return "\033[38;2;126;200;80m🌱\033[0m";
        default:
            return "❓";
    }
}

bool RoomObject::canWalk() {
    switch (type) {
        case ObjectType::NONE:
            return false;
        case ObjectType::WALL:
            return false;
        case ObjectType::DIRT:
            return true;
        case ObjectType::GRASS:
            return true;
    }
    return true;
}