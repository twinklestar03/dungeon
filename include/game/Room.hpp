#pragma once
#include <random>
#include <vector>
#include <map>

#include "entity/Entity.hpp"
#include "item/Item.hpp"
#include "game/Location.hpp"


class Portal;


class Room {
public:
    enum class MapObject {
        Wall,
        Floor,
        Door,
        StairsUp,
        StairsDown,
        Portal,
        None
    };

    Room(std::string room_name, uint32_t length, uint32_t width);
    ~Room();

    // Do the maze generation and placing objects.
    void generate();

    void addWall(const Location& loc);
    bool isWall(const Location& loc);
    bool isOutside(const Location& loc);

private:
    std::string room_name;
    uint32_t max_x, max_y;
    std::vector<std::vector<MapObject>> map;
};

class Portal {
public:
    Portal(Location target);
    ~Portal();

    void setTarget(Location target);
    Location getTarget();

private:
    std::string room_name;
    Location target;
};