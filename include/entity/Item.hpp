#pragma once
#include <string>

#include "entity/Entity.hpp"


class Item : public Entity {
public:
    Item(std::string character, std::string name, std::string descripton);
    ~Item();

    EntityType getType() override;

    void setCharacter(std::string character);
    void setPrice(int price);
    void setWeight(int weight);

    std::string getCharacter();
    uint32_t getPrice();
    uint32_t getWeight();

private:
    std::string character;  // For icon.
    uint32_t weight;
    uint32_t price;
};