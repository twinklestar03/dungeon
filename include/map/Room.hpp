#pragma once

#include <memory>
#include <string>
#include <vector>
#include <unistd.h>

#include "game/Location.hpp"
#include "game/Object.hpp"
#include "map/RoomObject.hpp"


class Room : public Object {
public:
    Room(std::wstring name, std::wstring description, uint32_t max_h, uint32_t max_w);
    ~Room() = default;

    void setRoomObject(Location location, RoomObject& room_object);
    void setRoomObject(Location location, std::shared_ptr<RoomObject> room_object);
    std::shared_ptr<RoomObject> getRoomObject(Location location);

    void setMaxHeight(uint32_t max_h);
    void setMaxWidth(uint32_t max_w);

    uint32_t getMaxHeight() const;
    uint32_t getMaxWidth() const;

    bool operator== (Room &rhs);

private:
    uint32_t max_h, max_w;
    std::vector<std::vector<std::shared_ptr<RoomObject>>> room_objects;
};