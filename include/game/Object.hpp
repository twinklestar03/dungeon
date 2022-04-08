#pragma once
#include <string>



class Object {
public:
    Object();
    Object(std::string name, std::string description);
    Object(uint32_t index, std::string name, std::string description);
    ~Object() = default;

    void setIndex(uint32_t index);
    void setName(std::string name);
    void setDescription(std::string description);

    uint32_t getIndex();
    std::string getName();
    std::string getDescription();

private:
    uint32_t index;
    std::string name;
    std::string description;
};