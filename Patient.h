#pragma once
#include "Person.h"

class Patient : public Person {
public:
    Patient() = default;
    Patient(int id, const std::string& name, int age,
            const std::string& bloodGroup, const std::string& contact);
    std::string role() const override;
    void display() const override;
};
