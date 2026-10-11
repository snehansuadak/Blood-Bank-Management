#pragma once
#include <string>

class Request {
private:
    int requestId{};
    int patientId{};
    std::string bloodGroup;
    int units{};
    std::string status{"Pending"};
public:
    Request() = default;
    Request(int requestId, int patientId, const std::string& group,
            int units, const std::string& status = "Pending");

    int getId() const;
    int getPatientId() const;
    std::string getBloodGroup() const;
    int getUnits() const;
    std::string getStatus() const;
    void setStatus(const std::string& value);
    void display() const;
};
