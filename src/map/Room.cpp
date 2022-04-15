#include "map/Room.hpp"


Room::Room(std::string name, std::string description, uint32_t max_x, uint32_t max_y) : Object(name, description), max_x(max_x), max_y(max_y) {
    room_objects = std::vector<std::vector<std::shared_ptr<RoomObject>>>(max_x, std::vector<std::shared_ptr<RoomObject>>(max_y));
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