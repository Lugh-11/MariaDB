#include <iostream>
#include <iomanip>
#include <string>
#include <vector>
#include <fstream>
using namespace std;

ifstream inputFile;
vector <string> readInput ();
void parseAndGenerateOutput(const vector<string>& query);

int main()
{
    vector<string> query = readInput();
    for (string commands:query){
        cout << commands << endl;
    }
    parseAndGenerateOutput(query);
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


        while(getline(inputFile,fileContents)){
            output.push_back(fileContents);
        }

        inputFile.close();
        }

    return output;
}

void parseAndGenerateOutput( const vector <string> & query)
{
    for (const string& line : query)
    {
        if (line.find("CREATE") != string::npos)
        {
            cout << "> " << line << endl;
        }
        else if (line.find("DATABASES") != string::npos)
        {
            cout << "> " << line << endl;
        }
        else if (line.find("CREATE TABLE") != string::npos)
        {
            cout << "> " << line << endl;
        }
        else
        {
            cout << line << endl;
        }
    }
}
