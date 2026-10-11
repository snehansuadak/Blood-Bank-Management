#pragma once
#include <vector>
#include "Donor.h"
#include "Patient.h"
#include "BloodUnit.h"
#include "Request.h"
#include "FileManager.h"

class BloodBank {
private:
    std::vector<Donor> donors;
    std::vector<Patient> patients;
    std::vector<BloodUnit> bloodUnits;
    std::vector<Request> requests;
    FileManager fileManager;
    int nextDonorId{1}, nextPatientId{1}, nextUnitId{1}, nextRequestId{1};

    bool validBloodGroup(const std::string& group) const;
    void updateNextIds();
public:
    BloodBank();
    ~BloodBank();

    void addRecord();
    void displayRecords() const;
    void searchRecord() const;
    void updateRecord();
    void deleteRecord();
    void processTransaction();
    void generateReport() const;
    void saveLoadMenu();
    void saveAll() const;
    void loadAll();
    void dynamicMemoryDemo() const;
};
