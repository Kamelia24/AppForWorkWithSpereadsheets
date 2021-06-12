#ifndef ETABLEH
#define ETABLEH

#include <fstream>
#include <cstring>
#include <algorithm> //.find
#include <cctype> // .isspace
#include <locale> // for the above include
#include <iomanip>

#include "string.h"
#include "Cell.h"

using namespace std;
///class which contains info of the table.
class ETable
{
private:
Cell cells[50][50];
    string lastError = "";
    string folderForFiles = ".\\Data"; // Here the data files will be created.
    string activeFilePath = "";        // The file from which data is read or saved.
public:
    ETable(string fileName);
    ~ETable();
    bool readRow(string address);
    bool readRow(int rowNumber);
    bool saveRow(string address);
    bool saveRow(int rowNumber);
    string getLastError();
    void print();
    void createTestData();
    void recognizeTestData();
};

#endif // ETABLEH