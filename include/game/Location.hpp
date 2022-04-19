#pragma once
#include <string>
#include <stdint.h>
#include <math.h>


class Location {
public:
    Location() = default;
    ~Location() = default;
    /* Offset mode */
    Location(uint32_t y, uint32_t x);
    /* Specific location mode  */
    Location(std::wstring room_name, uint32_t y, uint32_t x);
    
    void setRoomName(std::wstring room_name);
    void setX(uint32_t x);
    void setY(uint32_t y);
    std::wstring getRoomName() const;
    uint32_t getX() const;
    uint32_t getY() const;

    double distance(const Location& rsh);

    Location operator+(const Location& rhs) const;
    Location operator-(const Location& rhs) const;
    Location operator+=(const Location& rhs);
    Location operator-=(const Location& rhs);

    bool operator==(const Location& rhs) const;

private:
    std::wstring room_name;
    uint32_t x, y;
};