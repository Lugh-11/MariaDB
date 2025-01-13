#include <iostream>
#include <map>
#include <vector>
#include <sstream>
#include <string>

using namespace std;

// Database: Map of table names to rows of data
map<string, vector<vector<string>>> database;

// Function prototypes
void handleTables();
void handleInsert(string command);
void handleSelect(string command);

int main() {
    string command;

    cout << "Welcome to MariaDB Simulator!\n";
    cout << "Enter your SQL commands (or type EXIT to quit):\n";

    while (true) {
        cout << "> ";
        getline(cin, command);

        if (command == "EXIT") {
            break;
        } else if (command == "TABLES") {
            handleTables();
        } else if (command.rfind("INSERT INTO", 0) == 0) {  // Check if command starts with "INSERT INTO"
            handleInsert(command);
        } else if (command.rfind("SELECT * FROM", 0) == 0) {  // Check if command starts with "SELECT * FROM"
            handleSelect(command);
        } else {
            cout << "Unknown command. Please try again.\n";
        }
    }

    cout << "Goodbye!\n";
    return 0;
}

// List all tables in the database
void handleTables() {
    if (database.empty()) {
        cout << "No tables available.\n";
    } else {
        cout << "Tables:\n";
        for (const auto& table : database) {
            cout << "- " << table.first << endl;
        }
    }
}

// Insert data into a table
void handleInsert(string command) {
    size_t tableStart = command.find("INSERT INTO") + 12;
    size_t valuesStart = command.find("VALUES (");

    if (valuesStart == string::npos) {
        cout << "Invalid INSERT command.\n";
        return;
    }

    string tableName = command.substr(tableStart, valuesStart - tableStart - 1);
    string values = command.substr(valuesStart + 8, command.length() - valuesStart - 9);

    stringstream ss(values);
    string value;
    vector<string> row;

    while (getline(ss, value, ',')) {
        row.push_back(value);
    }

    database[tableName].push_back(row);
    cout << "Inserted row into table '" << tableName << "'.\n";
}

// Select all rows from a table
void handleSelect(string command) {
    size_t tableStart = command.find("FROM") + 5;
    string tableName = command.substr(tableStart);

    // Trim trailing semicolon
    if (tableName.back() == ';') {
        tableName.pop_back();
    }

    if (database.find(tableName) == database.end()) {
        cout << "Table '" << tableName << "' does not exist.\n";
        return;
    }

    cout << "Rows in table '" << tableName << "':\n";
    for (const auto& row : database[tableName]) {
        for (const auto& col : row) {
            cout << col << " ";
        }
        cout << endl;
    }
}
