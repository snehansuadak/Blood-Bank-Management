#include "BloodBank.h"
#include <iostream>
#include <limits>

int main() {
    try {
        BloodBank system;
        int choice = 0;
        do {
            std::cout << "\n====================================\n"
                      << "       BLOOD BANK MANAGEMENT\n"
                      << "====================================\n"
                      << "1. Add Record\n"
                      << "2. Display Records\n"
                      << "3. Search Record\n"
                      << "4. Update Record\n"
                      << "5. Delete Record\n"
                      << "6. Main Transaction/Process\n"
                      << "7. Report\n"
                      << "8. Save/Load\n"
                      << "9. Dynamic Memory Demo\n"
                      << "0. Exit\n";
            std::cout << "Enter choice: ";
            if (!(std::cin >> choice)) {
                std::cout << "Please enter a number.\n";
                std::cin.clear();
                std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
                continue;
            }
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            try {
                switch (choice) {
                    case 1: system.addRecord(); break;
                    case 2: system.displayRecords(); break;
                    case 3: system.searchRecord(); break;
                    case 4: system.updateRecord(); break;
                    case 5: system.deleteRecord(); break;
                    case 6: system.processTransaction(); break;
                    case 7: system.generateReport(); break;
                    case 8: system.saveLoadMenu(); break;
                    case 9: system.dynamicMemoryDemo(); break;
                    case 0: system.saveAll(); std::cout << "Data saved. Goodbye!\n"; break;
                    default: std::cout << "Choose a listed menu option.\n";
                }
            } catch (const std::exception& ex) {
                std::cout << "Operation failed: " << ex.what() << '\n';
            }
        } while (choice != 0);
    } catch (const std::exception& ex) {
        std::cerr << "Application could not start: " << ex.what() << '\n';
        return 1;
    }
    return 0;
}
