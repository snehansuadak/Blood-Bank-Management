#pragma once
#include <string>
#include <vector>
#include "Donor.h"
#include "Patient.h"
#include "BloodUnit.h"
#include "Request.h"

class FileManager {
private:
    std::string dataDirectory;
public:
    explicit FileManager(const std::string& directory = "Data");
    bool saveDonors(const std::vector<Donor>& items) const;
    bool loadDonors(std::vector<Donor>& items) const;
    bool savePatients(const std::vector<Patient>& items) const;
    bool loadPatients(std::vector<Patient>& items) const;
    bool saveBloodUnits(const std::vector<BloodUnit>& items) const;
    bool loadBloodUnits(std::vector<BloodUnit>& items) const;
    bool saveRequests(const std::vector<Request>& items) const;
    bool loadRequests(std::vector<Request>& items) const;
};
