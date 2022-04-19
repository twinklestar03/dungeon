#pragma once
#include <string>

#include "entity/Entity.hpp"


class Item : public Entity {
public:
    Item(std::wstring name, std::wstring descripton, Location location);
    ~Item();

    bool interact(Entity& entity) override; 
};