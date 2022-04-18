#include "map/Room.hpp"


Room::Room(std::string name, std::string description, uint32_t max_h, uint32_t max_w) : Object(name, description), max_h(max_h), max_w(max_w) {
    room_objects = std::vector<std::vector<std::shared_ptr<RoomObject>>>(max_h, std::vector<std::shared_ptr<RoomObject>>(max_w));

    for (uint32_t i = 0; i < max_h; i++) {
        for (uint32_t j = 0; j < max_w; j++) {
            room_objects[i][j] = std::make_shared<RoomObject>(RoomObject::ObjectType::DIRT);
        }
    }

    // Mark room borders as walls.
    for (uint32_t i = 0; i < max_h; i++) {
        room_objects[i][0]->setType(RoomObject::ObjectType::WALL);
        room_objects[i][max_w - 1]->setType(RoomObject::ObjectType::WALL);
    }

    for (uint32_t i = 0; i < max_w; i++) {
        room_objects[0][i]->setType(RoomObject::ObjectType::WALL);
        room_objects[max_h - 1][i]->setType(RoomObject::ObjectType::WALL);
    }
}

std::shared_ptr<RoomObject> Room::getRoomObject(Location location) {
    if (location.getX() < 0 || location.getX() >= max_h || location.getY() < 0 || location.getY() >= max_w) {
        return nullptr;
    }
    return room_objects[location.getX()][location.getY()];
}

void Room::setMaxHeight(uint32_t max_h) {
    this->max_h = max_h;
}

void Room::setMaxWidth(uint32_t max_w) {
    this->max_w = max_w;
}

uint32_t Room::getMaxHeight() const {
    return max_h;
}

uint32_t Room::getMaxWidth() const {
    return max_w;
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