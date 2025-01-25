// *********************************************************
// Course: CCP6114 Programming Fundamentals
// Lecture Class: TC8L
// Tutorial Class: T15L
// Trimester: 2430
// Member_1: 242UC2456L | NABIL NABIHAN BIN MAHDZAR SHARIL |NABIL.NABIHAN.MAHDZAR@student.mmu.edu.my |0106541102
// Member_2: 242UC244F2 | ZYADH KHALIFE BIN KAMSHUL |ZYADH.KHALIFE.KAMSHUL@student.mmu.edu.my |0173581604
// Member_3: 242UC2432Z | MOHAMMED AFIQ BIN MOHAMED SALIM |MOHAMED.AFIQ.MOHAMED@student.mmu.edu.my|0135666202
// *********************************************************
// Task Distribution
// Member_1: NABIL   (Program CREATE , CREATE TABLE , DATABASE)
// Member_2: KHALIFE (Program INSERT , TABLES, SELECT , SELECT COUNT)
// Member_3: AFIQ    (Program UPDATE , DELETE)

#include <iostream>
#include <iomanip>
#include <string>
#include <vector>
#include <fstream>
using namespace std;

// Global variable
int totalInserts = 0;

ifstream inputFile;

// Function declarations
vector<string> readInput();
string readOutput(string, ofstream&);
vector<vector<string>> CreateTable(string);
vector<vector<string>> TableInsert(string commands, vector<vector<string>>& table);
void displayTable(ofstream& OutputFile, string commands, vector<vector<string>>& table);
string tableName(string);
void databaseFile(int);
vector<vector<string>> TableUpdate(string, vector<vector<string>>);
vector<vector<string>> TableDelete(string, vector<vector<string>>);
void displayCommands(string, string, ofstream&);

int main()
{
    ofstream OutputFile;
    string nameOfTable;
    vector<string> query = readInput();
    int iterationCount = 1;
    vector<vector<string>> table;

    for (string commands : query) {
        // Handle CREATE TABLE command
        if (commands.find("CREATE TABLE") != string::npos) {
            displayCommands(commands, "CREATE TABLE", OutputFile);
            nameOfTable = tableName(commands);
            table = CreateTable(commands);
        }
        // Handle DATABASES command
        else if (commands.find("DATABASES") != string::npos) {
            displayCommands(commands, "DATABASES", OutputFile);
            databaseFile(iterationCount);
        }
        // Handle CREATE command
        else if (commands.find("CREATE") != string::npos) {
            displayCommands(commands, "CREATE", OutputFile);
            string Output = readOutput(commands, OutputFile);
            OutputFile.open(Output);
        }
        // Handle TABLES command
        else if (commands.find("TABLES") != string::npos) {
            displayCommands(commands, "TABLES", OutputFile);
            if (!nameOfTable.empty()) {
                cout << nameOfTable << endl;
            } else {
                cout << "No tables created yet." << endl;
            }
        }
        // Handle INSERT INTO command
        else if (commands.find("INSERT INTO") != string::npos) {
            displayCommands(commands, "INSERT INTO", OutputFile);
            table = TableInsert(commands, table);
        }
        // Handle SELECT COUNT command
        else if (commands.find("SELECT COUNT") != string::npos) {
            displayCommands(commands, "SELECT COUNT", OutputFile);
            cout << totalInserts << endl;
            OutputFile << totalInserts << endl;
        }
        // Handle SELECT command
        else if (commands.find("SELECT") != string::npos) {
            displayCommands(commands, "SELECT", OutputFile);
            displayTable(OutputFile, commands, table);
        }
        // Handle UPDATE command
        else if (commands.find("UPDATE") != string::npos) {
            displayCommands(commands, "UPDATE", OutputFile);
            table = TableUpdate(commands, table);
        }
        // Handle DELETE command
        else if (commands.find("DELETE") != string::npos) {
            displayCommands(commands, "DELETE", OutputFile);
            table = TableDelete(commands, table);
        }
        // Handle end of input commands (-1)
        else if (commands.find("-1") != string::npos) {
            OutputFile.close();
            iterationCount++;
            table.clear();
            totalInserts = 0;
        }
    }

    return 0;
}

// Reads input from multiple files and stores commands
vector<string> readInput()
{
    string fileName[3] = {"fileInput1.mdb", "fileInput2.mdb", "fileInput3.mdb"};
    string fileContents;
    string filePath = "C:\\mariadb\\";
    vector<string> output;

    for (int count = 0; count < 3; count++) {
        string fullFilePath = filePath + fileName[count];
        inputFile.open(fullFilePath);
        if (!inputFile) {
            cout << "File not found" << endl;
            continue;
        }

        // Read commands until ';' delimiter
        while (getline(inputFile, fileContents, ';')) {
            output.push_back(fileContents);
        }

        inputFile.close();
        output.push_back("-1");
    }

    return output;
}


string readOutput(string OutputFileName, ofstream& outputFile)
{
    OutputFileName.erase(0, 7);
    return OutputFileName;
}


vector<vector<string>> CreateTable(string cmd)
{
    vector<vector<string>> table;
    string columns = cmd;
    string tempStr;
    string newString;
    vector<string> tempVector;


    columns.erase(0, columns.find("(") + 1);
    columns.erase(columns.find(")"), 1);


    for (int count = 0; count < columns.size(); count++) {
        if (columns.find("\n") != string::npos) {
            columns.erase(columns.find("\n"), 1);
        } else if (columns.find("INT") != string::npos) {
            columns.erase(columns.find("INT"), 3);
        } else if (columns.find("TEXT") != string::npos) {
            columns.erase(columns.find("TEXT"), 4);
        }
    }

    columns += ",";


    for (int count = 0; count < columns.size(); count++) {
        if (columns[count] != ' ') {
            newString += columns[count];
        }
    }

    for (int count = 0; count < newString.size(); count++) {
        if (newString[count] != ',') {
            tempStr += newString[count];
        } else {
            tempVector.push_back(tempStr);
            tempStr = "";
        }
    }

    table.push_back(tempVector);
    return table;
}


string tableName(string commands)
{
    size_t start = commands.find("TABLE") + 6;
    size_t end = commands.find("(", start);
    string lastCreatedTable = commands.substr(start, end - start);
    return lastCreatedTable;
}


void databaseFile(int count)
{
    string fullFilePath = "C:\\mariadb\\";
    string fileName[3] = {"fileInput1.mdb", "fileInput2.mdb", "fileInput3.mdb"};
    if (count == 1) {
        fullFilePath += fileName[count - 1];
    } else if (count == 2) {
        fullFilePath += fileName[count - 1];
    } else if (count == 3) {
        fullFilePath += fileName[count - 1];
    }
    cout << fullFilePath << endl;
}

// Handles INSERT INTO command and updates the table
vector<vector<string>> TableInsert(string commands, vector<vector<string>>& table)
{
    // 1. Extract table name and values
    size_t start = commands.find("INTO ") + 5;
    size_t end = commands.find("(", start);
    string tableName = commands.substr(start, end - start);

    start = commands.find("VALUES (") + 8; // Adjust to find "VALUES ("
    end = commands.find(")", start);
    string valuesString = commands.substr(start, end - start);

    // 2. Split valuesString into individual values
    vector<string> values;
    size_t pos = 0;
    string delimiter = ",";
    while ((pos = valuesString.find(delimiter)) != string::npos) {
        values.push_back(valuesString.substr(0, pos));
        valuesString.erase(0, pos + delimiter.length());
    }
    values.push_back(valuesString);

    // 3. Add new row to the table
    table.push_back(values);
    totalInserts += 1; // Increment total inserts
    return table;
}

// Displays the table content on console and output file
void displayTable(ofstream& OutputFile, string commands, vector<vector<string>>& table)
{
    for (int rows = 0; rows < table.size(); rows++) {
        if (rows > 0) {
            cout << endl;
            OutputFile << endl;
        }
        for (int columns = 0; columns < table[rows].size(); columns++) {
            if (columns != table[rows].size() - 1) {
                cout << table[rows][columns] << ",";
                OutputFile << table[rows][columns] << ",";
            } else {
                cout << table[rows][columns];
                OutputFile << table[rows][columns];
            }
        }
    }
    cout << endl;
    OutputFile << endl;
}

// Updates a specific cell in the table
vector<vector<string>> TableUpdate(string cmd, vector<vector<string>> table)
{
    string itemToReplace = cmd;
    string row = cmd;
    string columnName = cmd;
    int colNum;
    int rowNum;

    // item to replace
    itemToReplace.erase(0, itemToReplace.find("=") + 1);
    itemToReplace.erase(itemToReplace.find("' ") + 1, -1);

    //  row number
    row.erase(0, row.find("=") + 1);
    row.erase(0, row.find("=") + 1);
    rowNum = stoi(row);

    //  column name
    columnName.erase(0, columnName.find("SET") + 4);
    columnName.erase(columnName.find("="), -1);

    // Find column index
    for (int vectorRow = 0; vectorRow < table.size(); vectorRow++) {
        for (int col = 0; col < table[vectorRow].size(); col++) {
            if (table[vectorRow][col] == columnName) {
                colNum = col;
                break;
            }
        }
    }
    table[rowNum][colNum] = itemToReplace; // Update the value
    return table;
}

// Deletes a specific row from the table
vector<vector<string>> TableDelete(string query, vector<vector<string>> table)
{
    string rowToBeDeleted = query;
    int row;

    // row number to delete
    rowToBeDeleted.erase(0, rowToBeDeleted.find("=") + 1);
    row = stoi(rowToBeDeleted);
    table[row].clear(); // Clear the row content
    totalInserts -= 1; // Decrement total inserts

    return table;
}

// Logs the commands to console and output file
void displayCommands(string cmd, string beginningWord, ofstream& OutputFile)
{
    cmd.erase(0, cmd.find(beginningWord));
    cout << ">" << cmd << ";" << endl;
    OutputFile << ">" << cmd << ";" << endl;
}
