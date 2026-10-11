#include "Patient.h"
#include <iostream>

Patient::Patient(int id, const std::string& name, int age,
                 const std::string& bloodGroup, const std::string& contact)
    : Person(id, name, age, bloodGroup, contact) {}

std::string Patient::role() const { return "Patient"; }

void Patient::display() const {
    Person::display();
    std::cout << " | Role: Patient\n";
}
