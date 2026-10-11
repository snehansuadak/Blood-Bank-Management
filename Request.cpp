#include "Request.h"
#include <iostream>
#include <stdexcept>

Request::Request(int requestIdValue, int patientIdValue,
                 const std::string& group, int unitCount, const std::string& statusValue)
    : requestId(requestIdValue), patientId(patientIdValue), bloodGroup(group),
      units(unitCount), status(statusValue) {
    if (unitCount <= 0) throw std::invalid_argument("Requested units must be greater than zero.");
}
int Request::getId() const { return requestId; }
int Request::getPatientId() const { return patientId; }
std::string Request::getBloodGroup() const { return bloodGroup; }
int Request::getUnits() const { return units; }
std::string Request::getStatus() const { return status; }
void Request::setStatus(const std::string& value) { status = value; }
void Request::display() const {
    std::cout << "Request ID: " << requestId << " | Patient ID: " << patientId
              << " | Group: " << bloodGroup << " | Units: " << units
              << " | Status: " << status << '\n';
}
