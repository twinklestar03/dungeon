#pragma once
#include <string>

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

    void setType(ObjectType type);
    ObjectType getType();
    
    std::wstring getIcon();

    bool canWalk();

private:
    ObjectType type;
};