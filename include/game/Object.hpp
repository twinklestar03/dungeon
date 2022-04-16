#pragma once
#include <string>



class Object {
public:
    Object() = default;
    Object(std::string name, std::string description);
    ~Object() = default;

    void setName(std::string name);
    void setDescription(std::string description);

    /* If current object need to be purge out from global object list */
    /* Set this flag */
    void setDeleted(bool deleted);

    std::string getName() const;
    std::string getDescription() const;
    uint32_t getUniqueId() const;
    bool isDeleted() const;

    bool operator== (Object &rhs) const;
    bool operator< (Object &rhs) const;

private:
    static uint32_t global_id_counter;

    /* For global object removal */
    bool is_deleted = false;

    std::string name;
    std::string description;

    /* Use to identify object equality, generate at object construction */
    uint32_t unique_id;
};