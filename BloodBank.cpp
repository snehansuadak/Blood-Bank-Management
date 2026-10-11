#include "BloodBank.h"
#include <algorithm>
#include <iostream>
#include <limits>
#include <stdexcept>

namespace {
int readInt(const std::string& prompt, int minimum = 0) {
    int value;
    while (true) {
        std::cout << prompt;
        if (std::cin >> value && value >= minimum) {
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            return value;
        }
        std::cout << "Invalid number. Try again.\n";
        std::cin.clear();
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    }
}
std::string readText(const std::string& prompt) {
    std::string value;
    std::cout << prompt;
    std::getline(std::cin, value);
    return value;
}
bool validContact(const std::string& s) { return !s.empty() && s.find('|') == std::string::npos; }
}
BloodBank::BloodBank() { loadAll(); }
BloodBank::~BloodBank() { saveAll(); }

bool BloodBank::validBloodGroup(const std::string& g) const {
    static const std::vector<std::string> groups = {"A+","A-","B+","B-","AB+","AB-","O+","O-"};
    return std::find(groups.begin(), groups.end(), g) != groups.end();
}
void BloodBank::updateNextIds() {
    for (const auto& x: donors) nextDonorId = std::max(nextDonorId, x.getId()+1);
    for (const auto& x: patients) nextPatientId = std::max(nextPatientId, x.getId()+1);
    for (const auto& x: bloodUnits) nextUnitId = std::max(nextUnitId, x.getId()+1);
    for (const auto& x: requests) nextRequestId = std::max(nextRequestId, x.getId()+1);
}
void BloodBank::addRecord() {
    std::cout << "\nAdd: 1.Donor  2.Patient  3.Blood stock\n";
    int type = readInt("Choose type: ", 1);
    if (type == 1 || type == 2) {
        std::string name = readText("Full name (do not use |): ");
        int age = readInt("Age: ", 1);
        std::string group = readText("Blood group (A+, A-, B+, B-, AB+, AB-, O+, O-): ");
        if (!validBloodGroup(group)) { std::cout << "Invalid blood group. Record not added.\n"; return; }
        std::string contact = readText("Contact (do not use |): ");
        if (!validContact(name) || !validContact(contact)) { std::cout << "Invalid | character.\n"; return; }
        if (type == 1) donors.emplace_back(nextDonorId++, name, age, group, contact);
        else patients.emplace_back(nextPatientId++, name, age, group, contact);
        saveAll();
        std::cout << "Record added successfully.\n";
    } else if (type == 3) {
        std::string group = readText("Blood group: ");
        if (!validBloodGroup(group)) { std::cout << "Invalid blood group.\n"; return; }
        int quantity = readInt("Number of available units: ", 0);
        std::string expiry = readText("Expiry date (YYYY-MM-DD): ");
        bloodUnits.emplace_back(nextUnitId++, group, quantity, expiry);
        saveAll();
        std::cout << "Blood stock added.\n";
    } else std::cout << "Unknown record type.\n";
}
void BloodBank::displayRecords() const {
    std::cout << "\n--- DONORS ---\n";
    if (donors.empty()) std::cout << "No donors.\n";
    for (const auto& d : donors) d.display();
    std::cout << "--- PATIENTS ---\n";
    if (patients.empty()) std::cout << "No patients.\n";
    for (const auto& p : patients) p.display();
    std::cout << "--- BLOOD STOCK ---\n";
    if (bloodUnits.empty()) std::cout << "No blood stock records.\n";
    for (const auto& b : bloodUnits) b.display();
    std::cout << "--- REQUESTS ---\n";
    if (requests.empty()) std::cout << "No requests.\n";
    for (const auto& r : requests) r.display();
}
void BloodBank::searchRecord() const {
    std::cout << "Search: 1.Donor 2.Patient 3.Blood unit 4.Request\n";
    int type = readInt("Choose type: ", 1);
    int id = readInt("Enter record ID: ", 1);
    bool found = false;
    if (type == 1) for (const auto& x: donors) if (x.getId()==id) { x.display(); found=true; }
    if (type == 2) for (const auto& x: patients) if (x.getId()==id) { x.display(); found=true; }
    if (type == 3) for (const auto& x: bloodUnits) if (x.getId()==id) { x.display(); found=true; }
    if (type == 4) for (const auto& x: requests) if (x.getId()==id) { x.display(); found=true; }
    if (!found) std::cout << "Record not found.\n";
}
void BloodBank::updateRecord() {
    std::cout << "Update: 1.Donor contact 2.Patient contact 3.Blood stock quantity\n";
    int type = readInt("Choose type: ", 1);
    int id = readInt("Enter ID: ", 1);
    if (type == 1) {
        for (auto& x: donors) if (x.getId()==id) {
            std::string contact = readText("New contact (do not use |): ");
            if (!validContact(contact)) { std::cout << "Invalid contact.\n"; return; }
            x.setContact(contact); saveAll(); std::cout << "Donor contact updated.\n"; return;
        }
    } else if (type == 2) {
        for (auto& x: patients) if (x.getId()==id) {
            std::string contact = readText("New contact (do not use |): ");
            if (!validContact(contact)) { std::cout << "Invalid contact.\n"; return; }
            x.setContact(contact); saveAll(); std::cout << "Patient contact updated.\n"; return;
        }
    } else if (type == 3) {
        for (auto& x: bloodUnits) if (x.getId()==id) {
            x.setQuantity(readInt("New quantity: ", 0)); saveAll();
            std::cout << "Stock updated.\n"; return;
        }
    }
    std::cout << "Record not found or invalid type.\n";
}
void BloodBank::deleteRecord() {
    std::cout << "Delete: 1.Donor 2.Patient 3.Blood unit 4.Request\n";
    int type = readInt("Choose type: ", 1);
    int id = readInt("Enter ID: ", 1);
    std::size_t before = 0, after = 0;
    if (type == 1) {
        before=donors.size(); donors.erase(std::remove_if(donors.begin(), donors.end(), [&](const Donor& x){return x.getId()==id;}), donors.end()); after=donors.size();
    } else if (type == 2) {
        before=patients.size(); patients.erase(std::remove_if(patients.begin(), patients.end(), [&](const Patient& x){return x.getId()==id;}), patients.end()); after=patients.size();
    } else if (type == 3) {
        before=bloodUnits.size(); bloodUnits.erase(std::remove_if(bloodUnits.begin(), bloodUnits.end(), [&](const BloodUnit& x){return x.getId()==id;}), bloodUnits.end()); after=bloodUnits.size();
    } else if (type == 4) {
        before=requests.size(); requests.erase(std::remove_if(requests.begin(), requests.end(), [&](const Request& x){return x.getId()==id;}), requests.end()); after=requests.size();
    } else { std::cout << "Invalid type.\n"; return; }
    if (before != after) { saveAll(); std::cout << "Record deleted.\n"; }
    else std::cout << "Record not found.\n";
}
void BloodBank::processTransaction() {
    if (patients.empty()) { std::cout << "Add a patient first.\n"; return; }
    std::cout << "Patients:\n";
    for (const auto& p : patients) p.display();
    int patientId = readInt("Patient ID: ", 1);
    auto patient = std::find_if(patients.begin(), patients.end(),
        [&](const Patient& p){ return p.getId()==patientId; });
    if (patient == patients.end()) { std::cout << "Patient not found.\n"; return; }
    int units = readInt("Units requested: ", 1);
    requests.emplace_back(nextRequestId++, patientId, patient->getBloodGroup(), units);
    Request& req = requests.back();

    // Simplified exact-group matching only; clinical compatibility must be confirmed by qualified staff.
    auto stock = std::find_if(bloodUnits.begin(), bloodUnits.end(), [&](const BloodUnit& b) {
        return b.getBloodGroup() == req.getBloodGroup() && b.getQuantity() >= units;
    });
    if (stock != bloodUnits.end()) {
        stock->takeUnits(units);
        req.setStatus("Fulfilled");
        std::cout << "Request fulfilled; stock reduced. Confirm all transfusion decisions with clinical staff.\n";
    } else {
        req.setStatus("Pending - insufficient matching stock");
        std::cout << "Insufficient matching stock. Request left pending.\n";
    }
    saveAll();
}
void BloodBank::generateReport() const {
    std::cout << "\n===== BLOOD BANK REPORT =====\n";
    std::cout << "Donors: " << donors.size() << "\nPatients: " << patients.size()
              << "\nRequests: " << requests.size() << "\n";
    std::vector<std::string> groups = {"A+","A-","B+","B-","AB+","AB-","O+","O-"};
    for (const auto& g : groups) {
        int total = 0;
        for (const auto& b : bloodUnits) if (b.getBloodGroup()==g) total += b.getQuantity();
        std::cout << g << ": " << total << " unit(s)\n";
    }
    int pending=0;
    for (const auto& r : requests) if (r.getStatus() != "Fulfilled") ++pending;
    std::cout << "Pending/unfulfilled requests: " << pending << '\n';
}
void BloodBank::saveAll() const {
    bool ok = fileManager.saveDonors(donors) && fileManager.savePatients(patients)
           && fileManager.saveBloodUnits(bloodUnits) && fileManager.saveRequests(requests);
    if (!ok) std::cerr << "Warning: one or more data files could not be saved.\n";
}
void BloodBank::loadAll() {
    if (!fileManager.loadDonors(donors) || !fileManager.loadPatients(patients)
        || !fileManager.loadBloodUnits(bloodUnits) || !fileManager.loadRequests(requests))
        std::cerr << "Warning: a data file could not be loaded.\n";
    updateNextIds();
}
void BloodBank::saveLoadMenu() {
    std::cout << "1.Save now  2.Reload from files\n";
    int choice = readInt("Choose: ", 1);
    if (choice == 1) { saveAll(); std::cout << "Save attempted.\n"; }
    else if (choice == 2) { loadAll(); std::cout << "Data loaded from files.\n"; }
    else std::cout << "Invalid choice.\n";
}
void BloodBank::dynamicMemoryDemo() const {
    int capacity = readInt("How many temporary Donor objects to allocate? ", 1);
    Donor* temporaryDonors = nullptr;
    try {
        temporaryDonors = new Donor[capacity];
        std::cout << "Allocated an array for " << capacity << " Donor object(s).\n";
        delete[] temporaryDonors;
        temporaryDonors = nullptr;
        std::cout << "Memory released using delete[].\n";
    } catch (const std::bad_alloc&) {
        delete[] temporaryDonors;
        std::cout << "Memory allocation failed.\n";
    }
}
