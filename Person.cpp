#include "Person.h"
#include <iostream>

Person::Person(int idValue, const std::string& nameValue, int ageValue,
               const std::string& groupValue, const std::string& contactValue)
    : id(idValue), name(nameValue), age(ageValue),
      bloodGroup(groupValue), contact(contactValue) {}

int Person::getId() const { return id; }
std::string Person::getName() const { return name; }
int Person::getAge() const { return age; }
std::string Person::getBloodGroup() const { return bloodGroup; }
std::string Person::getContact() const { return contact; }
void Person::setContact(const std::string& value) { contact = value; }

void Person::display() const {
    std::cout << "ID: " << id << " | Name: " << name
              << " | Age: " << age << " | Blood group: " << bloodGroup
              << " | Contact: " << contact;
}
