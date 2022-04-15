#include "game/Location.hpp"


Location::Location(uint32_t name, uint32_t x, uint32_t y) {
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

double_t Location::distance(const Location& rsh) {
    return abs( sqrt( (rsh.x - this->x) * (rsh.x - this->x)
            - (rsh.y - this->y) * (rsh.y - this->y) ) );
}

Location Location::operator+ (const Location &loc) const {
    return Location(this->x + loc.x, this->y + loc.y);
}

Location Location::operator- (const Location &loc) const {
    return Location(this->x - loc.x, this->y - loc.y);
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