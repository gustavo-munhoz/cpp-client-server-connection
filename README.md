# **CRUD Application with C++ and MySQL**

This project is a simple command-line CRUD (Create, Read, Update, Delete) application developed in C++ that connects to a docker container with a MySQL database using MySQL Connector/C++. The project demonstrates basic operations such as adding, reading, updating, and deleting records in a database table.

## **Table of Contents**

- [Features](#features)
- [Prerequisites](#prerequisites)
- [Installation](#installation)
- [Usage](#usage)
- [Project Structure](#project-structure)
- [Database Schema](#database-schema)
- [Contributing](#contributing)
- [License](#license)

---

## **Features**

- Create new records in the database.
- Read all records or a specific record by ID.
- Update existing records.
- Delete records by ID.
- Command-line interface for interacting with the database.

## **Prerequisites**

Before running this project, ensure you have the following installed on your system:

- **C++ compiler** (with C++14 or higher support)
- **CMake** (for building the project)
- **MySQL** (local instance or Docker container)
- **MySQL Connector/C++** (for database connection)
- **Docker** (for database populating and hosting)

## **Installation**

### **1. Clone the repository:**

```bash
git clone https://github.com/your-username/cpp-client-server-connection.git
cd cpp-client-server-connection
```

### **2. Install dependencies:**

Make sure you have installed MySQL Connector/C++. If you're using Homebrew on macOS, you can install it using:

```bash
brew install mysql-connector-c++
```

### **3. Run docker compose**

Run the following script to start the docker containter:

```bash
docker compose up -d
```

Or in earlier versions:
```bash
docker-compose up -d
```

### **4. Set environment variables:**

Run the script in `set_env.sh` to set database environment variables:

```bash
source set_env.sh
```

### **5. Build the project**

Configure and build the project using CMake:

```bash
mkdir build
cd build
cmake ..
make
```

## Usage

After building the project, run the executable:

```bash
./crud_app
```
