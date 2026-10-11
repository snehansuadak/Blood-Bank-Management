#pragma once
#include <string>

class BloodUnit {
private:
    int unitId{};
    std::string bloodGroup;
    int quantity{}; // Number of units currently available
    std::string expiryDate; // Format: YYYY-MM-DD
public:
    BloodUnit() = default;
    BloodUnit(int id, const std::string& group, int units,
              const std::string& expiry);

    int getId() const;
    std::string getBloodGroup() const;
    int getQuantity() const;
    std::string getExpiryDate() const;
    void setBloodGroup(const std::string& group);
    void setQuantity(int units);
    void setExpiryDate(const std::string& expiry);
    bool takeUnits(int units);
    void display() const;
};
