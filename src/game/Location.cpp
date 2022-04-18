#include "game/Location.hpp"


Location::Location(std::string name, uint32_t x, uint32_t y) {
    this->room_name = name;
    this->x = x;
    this->y = y;
}

Location::Location(uint32_t x, uint32_t y) {
    this->x = x;
    this->y = y;
}

void Location::setRoomName(std::string name) {
    this->room_name = name;
}

void Location::setX(uint32_t x) {
    this->x = x;
}

void Location::setY(uint32_t y) {
    this->y = y;
}

std::string Location::getRoomName() const {
    return this->room_name;
}

uint32_t Location::getX() const {
    return this->x;
}

uint32_t Location::getY() const {
    return this->y;
}

double Location::distance(const Location& rsh) {
    uint32_t dx = this->x - rsh.getX();
    uint32_t dy = this->y - rsh.getY();
    return sqrt(dx * dx + dy * dy);
    //return max;
}

Location Location::operator+ (const Location &loc) const {
    return Location(this->room_name, this->x + loc.x, this->y + loc.y);
}

Location Location::operator- (const Location &loc) const {
    return Location(this->room_name, this->x - loc.x, this->y - loc.y);
}

Location Location::operator+= (const Location& rhs) {
    this->x += rhs.x;
    this->y += rhs.y;
    return *this;
}

Location Location::operator-= (const Location& rhs) {
    this->x -= rhs.x;
    this->y -= rhs.y;
    return *this;
}

bool Location::operator== (const Location& rhs) const {
    return this->room_name == rhs.room_name && this->x == rhs.x && this->y == rhs.y;
}