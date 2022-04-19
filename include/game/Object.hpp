#pragma once
#include <string>



class Object {
public:
    Object() = default;
    Object(std::wstring name, std::wstring description);
    ~Object() = default;

    void setName(std::wstring name);
    void setDescription(std::wstring description);

    /* If current object need to be purge out from global object list */
    /* Set this flag */
    void setDeleted(bool deleted);

    std::wstring getName() const;
    std::wstring getDescription() const;
    uint32_t getUniqueId() const;
    bool isDeleted() const;

    bool operator== (Object &rhs) const;
    bool operator< (Object &rhs) const;

private:
    static uint32_t global_id_counter;

    /* For global object removal */
    bool is_deleted = false;

    std::wstring name;
    std::wstring description;

    /* Use to identify object equality, generate at object construction */
    uint32_t unique_id;
};