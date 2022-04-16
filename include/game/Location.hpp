#pragma once
#include <string>
#include <stdint.h>
#include <math.h>


class Location {
public:
    Location() = default;
    ~Location() = default;
    /* Offset mode */
    Location(uint32_t x, uint32_t y);
    /* Specific location mode  */
    Location(std::string room_name, uint32_t x, uint32_t y);
    
    void setRoomName(std::string room_name);
    void setX(uint32_t x);
    void setY(uint32_t y);
    std::string getRoomName() const;
    uint32_t getX() const;
    uint32_t getY() const;

    double distance(const Location& rsh);

    Location operator+(const Location& rhs) const;
    Location operator-(const Location& rhs) const;
    Location operator+=(const Location& rhs);
    Location operator-=(const Location& rhs);

private:
    std::string room_name;
    uint32_t x, y;
};