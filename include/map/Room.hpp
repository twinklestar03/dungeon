#pragma once

#include <string>
#include <vector>
#include <unistd.h>

#include "game/Location.hpp"
#include "game/Object.hpp"
#include "map/RoomObject.hpp"


class Room : public Object {
public:
    Room(std::string name, std::string description, uint32_t max_x, uint32_t max_y);
    ~Room() = default;

    void setMaxX(uint32_t max_x);
    void setMaxY(uint32_t max_y);

    uint32_t getMaxX() const;
    uint32_t getMaxY() const;

    bool operator== (Room &rhs);

private:
    uint32_t max_x, max_y;
    std::vector<std::vector<std::shared_ptr<RoomObject>>> room_objects;
};