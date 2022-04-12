#pragma once
#include <string>
#include <stdint.h>
#include <math.h>


class Location {
public:
    Location() = default;
    ~Location() = default;
    Location(uint32_t x, uint32_t y);
    Location(uint32_t roomId, uint32_t x, uint32_t y);
    
    void setRoom(std::string id);
    void setX(uint32_t x);
    void setY(uint32_t y);
    std::string getRoomId() const;
    uint32_t getX() const;
    uint32_t getY() const;

    double_t distance(const Location& rsh);

    Location operator+(const Location& rhs) const;
    Location operator-(const Location& rhs) const;
    Location operator+=(const Location& rhs);
    Location operator-=(const Location& rhs);

private:
    std::string roomId;
    uint32_t x, y;
};