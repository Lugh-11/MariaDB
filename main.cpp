#include <iostream>
#include <iomanip>
#include <string>
#include <vector>
#include <fstream>
using namespace std;

ifstream inputFile;
vector <string> readInput ();
string readOutput (string);
vector<vector<string>> CreateTable ();
string tableName (string);
void databaseFile(int);

int main()
{
    ofstream OutputFile;
    string nameOfTable;
    vector<string> query = readInput();
    int iterationCount = 1;

    for (string commands:query){
        cout << commands << endl;
        if (commands.find ("CREATE TABLE") != string::npos){
            cout << "CREATE TABLE" << endl;
            nameOfTable = tableName(commands);
            CreateTable();
        }
        else if (commands.find ("DATABASES") != string::npos){
            databaseFile(iterationCount);
        }
        else if (commands.find ("CREATE") != string::npos){
            cout << "CREATE" << endl;
            string Output = readOutput(commands);
            OutputFile.open(Output);
        }
        else if (commands.find ("TABLES") != string::npos){
            if (!nameOfTable.empty()) {
              cout << nameOfTable << endl;
            }
            else {
              cout << "No tables created yet." << endl;
            }
        }
        else if (commands.find ("INSERT INTO") != string::npos){
            cout << "INSERT INTO" << endl;
        }
        else if (commands.find ("SELECT COUNT") != string::npos){
            cout << "SELECT COUNT" << endl;
        }
        else if (commands.find ("SELECT") != string::npos){
            cout << "SELECT" << endl;
        }
        else if (commands.find ("UPDATE") != string::npos){
            cout << "UPDATE" << endl;
        }
        else if (commands.find ("DELETE") != string::npos){
            cout << "DELETE" << endl;
        }
        else if (commands.find("-1") != string::npos){
            OutputFile.close();
            iterationCount ++;
        }

    }

    return 0;
}

vector <string> readInput ()
{
    string fileName[3] = {"fileInput1.mdb" , "fileInput2.mdb" , "fileInput3.mdb"};
    string fileContents;
    string filePath = "C:\\mariadb\\";
    vector<string> output;

    for (int count = 0 ; count < 3 ; count++) {
        string fullFilePath = filePath + fileName[count];
        inputFile.open(fullFilePath);
        if (!inputFile){
            cout << "File not found" << endl ;
            continue;
        }


        while(getline(inputFile,fileContents,';')){
            output.push_back(fileContents);
        }

        inputFile.close();
        output.push_back("-1");
        fullFilePath = filePath;
        }

    return output;
}
string readOutput (string OutputFileName)
{
    OutputFileName.erase(0,7);
    cout << OutputFileName << endl;
    return OutputFileName;

}
vector<vector<string>> CreateTable ()
{
    vector<vector<string>> table;
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
    string fileName[3] = {"fileInput1.mdb" , "fileInput2.mdb" , "fileInput3.mdb"};
    if (count == 1)
    {
        fullFilePath += fileName[count -1];
    }
    else if (count == 2)
    {
        fullFilePath += fileName[count -1];
    }
    else if (count == 3)
    {
        fullFilePath += fileName[count -1];
    }
    cout << fullFilePath << endl;
}

