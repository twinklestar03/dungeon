#include "game/Location.hpp"


Location::Location(std::wstring name, uint32_t y, uint32_t x) {
    this->room_name = name;
    this->x = x;
    this->y = y;
}

Location::Location(uint32_t y, uint32_t x) {
    this->x = x;
    this->y = y;
}

void Location::setRoomName(std::wstring name) {
    this->room_name = name;
}

void Location::setX(uint32_t x) {
    this->x = x;
}

void Location::setY(uint32_t y) {
    this->y = y;
}

std::wstring Location::getRoomName() const {
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
    return Location(this->room_name, this->y + loc.y,  this->x + loc.x);
}

Location Location::operator- (const Location &loc) const {
    return Location(this->room_name, this->y - loc.y, this->x - loc.x);
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