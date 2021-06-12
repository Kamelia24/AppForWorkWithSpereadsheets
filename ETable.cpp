#include <iostream>

#include "ETable.h"
//#include "Cell.cpp"

using namespace std;

const int LINE_LENGTH = 1024;
const string FIELD_SEPARATOR = ",";

void createDataDir(string pathName)
{ //create folder for the files
    string cmd = "mkdir ";
    cmd.append(pathName);
    cmd.append(" 1>nul 2>nul"); // Eat the message in console.
    system(cmd.c_str());
}

ETable::ETable(string fileName)
{ //Create empty file
    createDataDir(folderForFiles);
    activeFilePath = folderForFiles;
    activeFilePath.append("/");
    activeFilePath.append(fileName);
    ofstream activeFile;
    activeFile.open(activeFilePath, fstream::out);
    activeFile.close();
    cout << "file " << fileName << " was created \n";
}

ETable::~ETable()
{
}
///functions which returns the last recieved error when working with the table.
string ETable::getLastError()
{ 
    return lastError;
}
///functions which reads line from the table by given address.
bool ETable::readRow(string address)
{
    ifstream activeFile;
    char line[LINE_LENGTH];

    activeFile.open(activeFilePath, fstream::in);
    activeFile.getline(line, LINE_LENGTH - 1, '\n');
    activeFile.close();
    return true;
}

bool ETable::readRow(int rowNumber)
{
    return true;
}
///function which checks if certain file exists by given filename.
bool doesFileExist(string filePathName)
{ //check if there already exists such file
    ifstream f(filePathName);
    return f.good();
}

void ETable::createTestData()
{ // insert test data into file
    ofstream activeFile;
    char line[] = "10, 20, 30\n";
    char line1[] = "10.9, \"22\", \"3s\"\n";
    char line2[] = "    , =10+5, =R1C1+R2C2\n";

    activeFile.open(activeFilePath, fstream::out);
    activeFile.write(line, strlen(line));
    activeFile.write(line1, strlen(line1));
    activeFile.write(line2, strlen(line2));
    activeFile.close();
}

bool ETable::saveRow(string address)//function which writes row into the file by given address.
{ //write new row into the file  --it replaces the whole table with the row
    ofstream activeFile;
    char line[] = "10, 20, 30\n";

    activeFile.open(activeFilePath, fstream::out);
    activeFile.write(line, strlen(line));
    activeFile.close();
    return true;
}

bool ETable::saveRow(int rowNumber)
{ //as the above but the address is a number
    return true;
}

// trim from start (in place)
static inline void ltrim(std::string &s)
{
    s.erase(s.begin(), std::find_if(s.begin(), s.end(),
                                    std::not1(std::ptr_fun<int, int>(std::isspace))));
}

// trim from end (in place)
static inline void rtrim(std::string &s)
{
    s.erase(std::find_if(s.rbegin(), s.rend(),
                         std::not1(std::ptr_fun<int, int>(std::isspace)))
                .base(),
            s.end());
}

// inLine - one row from the file.
// outFields - parsed data as strings.
// returns the number of fields.
int parseLine(char *inLine, string *outFields)
{ //returns the number of cells in a row
    string line = inLine;
    if (line.size() == 0)
        return 0;

    size_t newPos;
    size_t oldPos = 0;
    int itemNumber = 0;
    while ((newPos = line.find(FIELD_SEPARATOR, oldPos)) != string::npos)
    {
        string field = line.substr(oldPos, newPos - oldPos);
        ltrim(field);
        rtrim(field);
        outFields[itemNumber++] = field;
        oldPos = newPos + 1;
    }
    // Output the last field from the line:
    string field = line.substr(oldPos);
    ltrim(field);
    rtrim(field);
    outFields[itemNumber++] = field;
    return itemNumber;
}

void formatLine(char *inLine)
{ //otuputs row in the console
    string line = inLine;
    size_t newPos;
    size_t oldPos = 0;
    while ((newPos = line.find(FIELD_SEPARATOR, oldPos)) != string::npos)
    {
        string field = line.substr(oldPos, newPos - oldPos);
        ltrim(field);
        rtrim(field);
        cout<<setw(10) << field << " |";
        oldPos = newPos + 1;
    }
    // Output the last field from the line:
    string field = line.substr(oldPos);
    ltrim(field);
    rtrim(field);
    cout<<setw(10) << field << endl;
}

void ETable::print()
{ //outputs table
    ifstream activeFile;
    char line[LINE_LENGTH];

    activeFile.open(activeFilePath, fstream::in);
    while (!activeFile.eof())
    {
        line[0] = 0;
        activeFile.getline(line, LINE_LENGTH - 1, '\n');
        formatLine(line);
    }
    activeFile.close();
}
///function which shows the user the data and her type for rvery cell in the table.
void ETable::recognizeTestData()
{
    ifstream activeFile;
    char *line = new char[LINE_LENGTH];
    string fields[32];

    activeFile.open(activeFilePath, fstream::in);
    while (!activeFile.eof())
    {
        line[0] = 0;
        activeFile.getline(line, LINE_LENGTH - 1, '\n');
        int number = parseLine(line, fields);
        for (int counter = 0; counter < number; counter++)
        {
            Cell *cell = new Cell();
            bool result = cell->setValue(fields[counter]);
            if (result)
            {
                cout << fields[counter] << " - " << cell->getValueTypeAsString() << endl;
            }
            else
            {
                cout << cell->getLastError() << endl;
            }
            delete cell;
        }
    }
    activeFile.close();
    delete line;
    //delete fields;
}
