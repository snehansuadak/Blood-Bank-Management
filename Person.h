#pragma once
#include <string>

class Person {
protected:
    int id{};
    std::string name;
    int age{};
    std::string bloodGroup;
    std::string contact;
public:
    Person() = default;
    Person(int id, const std::string& name, int age,
           const std::string& bloodGroup, const std::string& contact);
    virtual ~Person() = default;

    int getId() const;
    std::string getName() const;
    int getAge() const;
    std::string getBloodGroup() const;
    std::string getContact() const;
    void setContact(const std::string& value);

    virtual std::string role() const = 0;
    virtual void display() const;
};
