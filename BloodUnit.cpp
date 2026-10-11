#include "BloodUnit.h"
#include <iostream>
#include <stdexcept>

BloodUnit::BloodUnit(int id, const std::string& group, int units,
                     const std::string& expiry)
    : unitId(id), bloodGroup(group), quantity(units), expiryDate(expiry) {
    if (units < 0) throw std::invalid_argument("Quantity cannot be negative.");
}
int BloodUnit::getId() const { return unitId; }
std::string BloodUnit::getBloodGroup() const { return bloodGroup; }
int BloodUnit::getQuantity() const { return quantity; }
std::string BloodUnit::getExpiryDate() const { return expiryDate; }
void BloodUnit::setBloodGroup(const std::string& group) { bloodGroup = group; }
void BloodUnit::setQuantity(int units) {
    if (units < 0) throw std::invalid_argument("Quantity cannot be negative.");
    quantity = units;
}
void BloodUnit::setExpiryDate(const std::string& expiry) { expiryDate = expiry; }
bool BloodUnit::takeUnits(int units) {
    if (units <= 0 || units > quantity) return false;
    quantity -= units;
    return true;
}
void BloodUnit::display() const {
    std::cout << "Unit ID: " << unitId << " | Group: " << bloodGroup
              << " | Quantity: " << quantity << " | Expiry: " << expiryDate << '\n';
}
