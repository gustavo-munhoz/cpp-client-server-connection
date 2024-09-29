#include <iostream>
#include <string>
#include <cstdlib>
#include "crud.h"

void printMenu() {
    std::cout << "\n=== CRUD Application ===\n";
    std::cout << "1. Create Record\n";
    std::cout << "2. Read All Records\n";
    std::cout << "3. Read Record By ID\n";
    std::cout << "4. Update Record\n";
    std::cout << "5. Delete Record\n";
    std::cout << "6. Exit\n";
    std::cout << "Choose an option: ";
}

int main() {
    try {
        DBConnection db;
        db.connect();

        int choice;
        while (true) {
            printMenu();
            std::cin >> choice;

            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

            switch (choice) {
                case 1:
                    createRecord(db);
                    break;
                case 2:
                    readAllRecords(db);
                    break;
		case 3:
		    readRecordById(db);
		    break;
                case 4:
                    updateRecord(db);
                    break;
                case 5:
                    deleteRecord(db);
                    break;
                case 6:
                    std::cout << "Exiting the application. Goodbye!\n";
                    return 0;
                default:
                    std::cout << "Invalid option. Please try again.\n";
            }
        }
    }
    catch (const std::exception &ex) {
        std::cerr << "Error: " << ex.what() << std::endl;
        return 1;
    }
    return 0;
}

