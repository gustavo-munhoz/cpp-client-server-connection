#ifndef CRUD_H
#define CRUD_H

#include <mysqlx/xdevapi.h>
#include <memory>

class DBConnection {
public:
	std::unique_ptr<mysqlx::Session> sess;

	DBConnection() : sess(nullptr) {}
	void connect();
	~DBConnection() {
		sess->close();
	}
};

void createRecord(DBConnection &db);
void readAllRecords(DBConnection &db);
void readRecordById(DBConnection &db);
void updateRecord(DBConnection &db);
void deleteRecord(DBConnection &db);

#endif
