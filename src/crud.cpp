#include "crud.h"
#include <iostream>
#include <iomanip>
#include <string>

void DBConnection::connect() {
	const char* db_host = std::getenv("DB_HOST");
    	const char* db_port = std::getenv("DB_PORT");
    	const char* db_user = std::getenv("DB_USER");
    	const char* db_pass = std::getenv("DB_PASS");
   	const char* db_name = std::getenv("DB_NAME");

    	if (!db_host || !db_port || !db_user || !db_pass || !db_name) {
        	throw std::runtime_error("Database environment variables are not set.");
    	}

	int port = std::stoi(db_port);

	sess = std::make_unique<mysqlx::Session>(db_host, port, db_user, db_pass);

	sess->sql("USE " + std::string(db_name)).execute();
}

void createRecord(DBConnection &db) {
	std::string name;
	int age;

	std::cout << "===== Create Record =====\n";
    	std::cout << "Name: ";
    	std::getline(std::cin, name);
    	std::cout << "Age: ";
    	std::cin >> age;
    	std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

   	try {
        	db.sess->sql("INSERT INTO users (name, age) VALUES (?, ?)")
               		.bind(name, age)
               		.execute();
        	std::cout << "Record created successfully!\n";
    	}
    	catch (const mysqlx::Error &err) {
        	std::cerr << "Error creating record: " << err.what() << std::endl;
    	}
}

void readAllRecords(DBConnection &db) {
    std::cout << "===== Read Records =====\n";
    try {
        mysqlx::RowResult res = db.sess->sql("SELECT * FROM users").execute();

        std::cout << std::left;
        std::cout << std::setw(5) << "ID" << std::setw(15) << "Name" << "Age\n";
        std::cout << "-----------------------------------\n";

        for (mysqlx::Row row : res) {
            std::cout << std::setw(5) << row[0].get<int>()
                      << std::setw(15) << row[1].get<std::string>()
                      << row[2].get<int>() << "\n";
        }
    }
    catch (const mysqlx::Error &err) {
        std::cerr << "Error reading records: " << err.what() << std::endl;
    }
}

void readRecordById(DBConnection &db) {
    std::cout << "=== Read Record by ID ===\n";

    int id;
    std::cout << "Enter the ID of the record: ";
    std::cin >> id;

    try {
        mysqlx::RowResult res = db.sess->sql("SELECT * FROM users WHERE id = ?")
                                .bind(id)
                                .execute();

        if (res.count() == 0) {
            std::cout << "No record found with ID: " << id << std::endl;
            return;
        }

        mysqlx::Row row = res.fetchOne();
        std::cout << std::left;
        std::cout << std::setw(5) << "ID" << std::setw(15) << "Name" << "Age\n";
        std::cout << "-----------------------------------\n";
        std::cout << std::setw(5) << row[0].get<int>()
                  << std::setw(15) << row[1].get<std::string>()
                  << row[2].get<int>() << "\n";
    }
    catch (const mysqlx::Error &err) {
        std::cerr << "Error reading record: " << err.what() << std::endl;
    }
}

void updateRecord(DBConnection &db) {
    int id;
    std::string new_name;
    int new_age;

    std::cout << "===== Update Record =====\n";
    std::cout << "ID of the record to update: ";
    std::cin >> id;
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    std::cout << "New Name: ";
    std::getline(std::cin, new_name);
    std::cout << "New Age: ";
    std::cin >> new_age;
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

    try {
        db.sess->sql("UPDATE users SET name = ?, age = ? WHERE id = ?")
               .bind(new_name, new_age, id)
               .execute();
        std::cout << "Record updated successfully!\n";
    }
    catch (const mysqlx::Error &err) {
        std::cerr << "Error updating record: " << err.what() << std::endl;
    }
}

void deleteRecord(DBConnection &db) {
    int id;

    std::cout << "===== Delete Record =====\n";
    std::cout << "ID of the record to delete: ";
    std::cin >> id;
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

    try {
        db.sess->sql("DELETE FROM users WHERE id = ?")
               .bind(id)
               .execute();
        std::cout << "Record deleted successfully!\n";
    }
    catch (const mysqlx::Error &err) {
        std::cerr << "Error deleting record: " << err.what() << std::endl;
    }
}
