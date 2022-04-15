#pragma once
#include <string>



class Object {
public:
    Object() = default;
    Object(std::string name, std::string description);
    ~Object() = default;

    void setName(std::string name);
    void setDescription(std::string description);

    std::string getName();
    std::string getDescription();

    uint32_t getUniqueId() const;

    bool operator== (Object &rhs) const;

    bool operator< (Object &rhs) const;

private:
    static uint32_t global_id_counter;

    std::string name;
    std::string description;

    /* Use to identify object equality, generate at object construction */
    uint32_t unique_id;
};