#pragma once
#include <string>

#include "entity/Entity.hpp"


class Item : public Entity {
public:
    Item(std::string name, std::string descripton, Location location);
    ~Item();

    bool interact(Entity& entity) override; 
};