#include "game/Location.hpp"


Location::Location(std::wstring name, int32_t y, int32_t x) {
    this->room_name = name;
    this->x = x;
    this->y = y;
}

Location::Location(int32_t y, int32_t x) {
    this->x = x;
    this->y = y;
}

void Location::setRoomName(std::wstring name) {
    this->room_name = name;
}

void Location::setX(int32_t x) {
    this->x = x;
}

void Location::setY(int32_t y) {
    this->y = y;
}

std::wstring Location::getRoomName() const {
    return this->room_name;
}

int32_t Location::getX() const {
    return this->x;
}

int32_t Location::getY() const {
    return this->y;
}

Location Location::normailize() {
    int f_x = (this->x > 0) ? 1 : -1;
    int f_y = (this->y > 0) ? 1 : -1;

    return Location(f_y, f_x);
}

double Location::distance(const Location& rsh) {
    int32_t dx = this->x - rsh.getX();
    int32_t dy = this->y - rsh.getY();
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