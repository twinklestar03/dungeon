#pragma once


class RoomObject {
public:
    enum class ObjectType {
        NONE,
        WALL,
        DIRT,
        GRASS,
    };
    RoomObject(ObjectType type);
    ~RoomObject() = default;

    ObjectType getType();
    
    bool canWalk();

private:
    ObjectType type;
};