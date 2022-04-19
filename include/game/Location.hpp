#pragma once
#include <string>
#include <stdint.h>
#include <math.h>


class Location {
public:
    Location() = default;
    ~Location() = default;
    /* Offset mode */
    Location(int32_t y, int32_t x);
    /* Specific location mode  */
    Location(std::wstring room_name, int32_t y, int32_t x);
    
    void setRoomName(std::wstring room_name);
    void setX(int32_t x);
    void setY(int32_t y);
    std::wstring getRoomName() const;
    int32_t getX() const;
    int32_t getY() const;

    Location normailize();
    double distance(const Location& rsh);

    Location operator+(const Location& rhs) const;
    Location operator-(const Location& rhs) const;
    Location operator+=(const Location& rhs);
    Location operator-=(const Location& rhs);

    bool operator==(const Location& rhs) const;

private:
    std::wstring room_name;
    int32_t x, y;
};