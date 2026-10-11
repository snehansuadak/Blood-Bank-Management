#pragma once
#include "Person.h"

class Donor : public Person {
public:
    Donor() = default;
    Donor(int id, const std::string& name, int age,
          const std::string& bloodGroup, const std::string& contact);
    std::string role() const override;
    void display() const override;
};
