#include "Donor.h"
#include <iostream>

Donor::Donor(int id, const std::string& name, int age,
             const std::string& bloodGroup, const std::string& contact)
    : Person(id, name, age, bloodGroup, contact) {}

std::string Donor::role() const { return "Donor"; }

void Donor::display() const {
    Person::display();
    std::cout << " | Role: Donor\n";
}
