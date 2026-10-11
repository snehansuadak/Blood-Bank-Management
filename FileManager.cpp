#include "FileManager.h"
#include <filesystem>
#include <fstream>
#include <sstream>

namespace {
std::vector<std::string> split(const std::string& line) {
    std::vector<std::string> parts;
    std::stringstream stream(line);
    std::string part;
    while (std::getline(stream, part, '|')) parts.push_back(part);
    return parts;
}
template<typename T, typename Writer>
bool saveFile(const std::string& path, const std::vector<T>& items, Writer writer) {
    std::ofstream out(path);
    if (!out) return false;
    for (const auto& item : items) writer(out, item);
    return static_cast<bool>(out);
}
template<typename T, typename Reader>
bool loadFile(const std::string& path, std::vector<T>& items, Reader reader) {
    std::ifstream in(path);
    if (!in) return true; // First run: no file yet is normal.
    std::vector<T> loaded;
    std::string line;
    try {
        while (std::getline(in, line)) {
            if (line.empty()) continue;
            auto p = split(line);
            T item{};
            if (reader(p, item)) loaded.push_back(item);
        }
    } catch (...) {
        return false;
    }
    items = std::move(loaded);
    return true;
}
}
FileManager::FileManager(const std::string& directory) : dataDirectory(directory) {
    std::filesystem::create_directories(dataDirectory);
}
bool FileManager::saveDonors(const std::vector<Donor>& v) const {
    return saveFile(dataDirectory + "/donors.txt", v, [](std::ostream& o, const Donor& x) {
        o << x.getId() << '|' << x.getName() << '|' << x.getAge() << '|'
          << x.getBloodGroup() << '|' << x.getContact() << '\n';
    });
}
bool FileManager::loadDonors(std::vector<Donor>& v) const {
    return loadFile(dataDirectory + "/donors.txt", v, [](const auto& p, Donor& x) {
        if (p.size()!=5) return false;
        x = Donor(std::stoi(p[0]),p[1],std::stoi(p[2]),p[3],p[4]); return true;
    });
}
bool FileManager::savePatients(const std::vector<Patient>& v) const {
    return saveFile(dataDirectory + "/patients.txt", v, [](std::ostream& o, const Patient& x) {
        o << x.getId() << '|' << x.getName() << '|' << x.getAge() << '|'
          << x.getBloodGroup() << '|' << x.getContact() << '\n';
    });
}
bool FileManager::loadPatients(std::vector<Patient>& v) const {
    return loadFile(dataDirectory + "/patients.txt", v, [](const auto& p, Patient& x) {
        if (p.size()!=5) return false;
        x = Patient(std::stoi(p[0]),p[1],std::stoi(p[2]),p[3],p[4]); return true;
    });
}
bool FileManager::saveBloodUnits(const std::vector<BloodUnit>& v) const {
    return saveFile(dataDirectory + "/bloodunits.txt", v, [](std::ostream& o, const BloodUnit& x) {
        o << x.getId() << '|' << x.getBloodGroup() << '|' << x.getQuantity()
          << '|' << x.getExpiryDate() << '\n';
    });
}
bool FileManager::loadBloodUnits(std::vector<BloodUnit>& v) const {
    return loadFile(dataDirectory + "/bloodunits.txt", v, [](const auto& p, BloodUnit& x) {
        if (p.size()!=4) return false;
        x = BloodUnit(std::stoi(p[0]),p[1],std::stoi(p[2]),p[3]); return true;
    });
}
bool FileManager::saveRequests(const std::vector<Request>& v) const {
    return saveFile(dataDirectory + "/requests.txt", v, [](std::ostream& o, const Request& x) {
        o << x.getId() << '|' << x.getPatientId() << '|' << x.getBloodGroup()
          << '|' << x.getUnits() << '|' << x.getStatus() << '\n';
    });
}
bool FileManager::loadRequests(std::vector<Request>& v) const {
    return loadFile(dataDirectory + "/requests.txt", v, [](const auto& p, Request& x) {
        if (p.size()!=5) return false;
        x = Request(std::stoi(p[0]),std::stoi(p[1]),p[2],std::stoi(p[3]),p[4]); return true;
    });
}
