#include <iostream>
#include <iomanip>
#include <string>
#include <vector>
#include <fstream>
using namespace std;

ifstream inputFile;
vector <string> readInput ();
string readOutput (string);

int main()
{
    ofstream OutputFile;
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
            string Output = readOutput(commands);
            OutputFile.open(Output);
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
        else if (commands.find("-1") != string::npos){
            OutputFile.close();
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
        output.push_back("-1");
        }

    return output;
}
string readOutput (string OutputFileName)
{
    OutputFileName.erase(0,7);
    cout << OutputFileName << endl;
    return OutputFileName;

}
