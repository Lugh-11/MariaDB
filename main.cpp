#include <iostream>
#include <iomanip>
#include <string>
#include <vector>
#include <fstream>
using namespace std;

ifstream inputFile;
vector <string> readInput ();

int main()
{
    vector<string> query = readInput();
    for (string commands:query){
        cout << commands << endl;
        if (commands.find ("CREATE TABLE") != string::npos){
            cout << "CREATE TABLE" << endl;
        }
        else if (commands.find ("DATABASES") != string::npos){
            cout << "DATABSES" << endl;
        }
        else if (commands.find ("CREATE") != string::npos){
            cout << "CREATE" << endl;
        }
        else if (commands.find ("TABLES") != string::npos){
            cout << "TABLES" << endl;
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

    }

    return 0;
}

vector <string> readInput ()
{
    string fileName[3] = {"fileInput1.mdb" , "fileInput2.mdb" , "fileInput3.mdb"};
    string fileContents;
    vector<string> output;

    for (int count = 0 ; count < 3 ; count++) {
        inputFile.open(fileName[count]);
        if (!inputFile){
            cout << "File not found" << endl ;
            continue;
        }


        while(getline(inputFile,fileContents,';')){
            output.push_back(fileContents);
        }

        inputFile.close();
        }

    return output;
}
