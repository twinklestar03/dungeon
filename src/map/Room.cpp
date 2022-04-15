#include "map/Room.hpp"


Room::Room(std::string name, std::string description, uint32_t max_x, uint32_t max_y) : Object(name, description), max_x(max_x), max_y(max_y) {
    room_objects = std::vector<std::vector<std::shared_ptr<RoomObject>>>(max_x, std::vector<std::shared_ptr<RoomObject>>(max_y));

    for (uint32_t i = 0; i < max_x; i++) {
        for (uint32_t j = 0; j < max_y; j++) {
            room_objects[i][j] = std::make_shared<RoomObject>(RoomObject::ObjectType::DIRT);
        }
    }

    // Mark room borders as walls.
    for (uint32_t i = 0; i < max_x; i++) {
        room_objects[i][0]->setType(RoomObject::ObjectType::WALL);
        room_objects[i][max_y - 1]->setType(RoomObject::ObjectType::WALL);
    }

    for (uint32_t i = 0; i < max_y; i++) {
        room_objects[0][i]->setType(RoomObject::ObjectType::WALL);
        room_objects[max_x - 1][i]->setType(RoomObject::ObjectType::WALL);
    }
}

std::shared_ptr<RoomObject> Room::getRoomObject(Location location) {
    if (location.getX() < 0 || location.getX() >= max_x || location.getY() < 0 || location.getY() >= max_y) {
        return nullptr;
    }
    return room_objects[location.getX()][location.getY()];
}

void Room::setMaxX(uint32_t max_x) {
    this->max_x = max_x;
}

void Room::setMaxY(uint32_t max_y) {
    this->max_y = max_y;
}

uint32_t Room::getMaxX() const {
    return max_x;
}

uint32_t Room::getMaxY() const {
    return max_y;
}

bool Room::operator== (Room &rhs) {
    if (this->getUniqueId() == rhs.getUniqueId()) {
        return true;
    }

    if (this->getName() == rhs.getName()) {
        return true;
    }

    return false;
}