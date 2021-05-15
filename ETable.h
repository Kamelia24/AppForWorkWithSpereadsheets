#ifndef ETABLEH
#define ETABLEH

#include <string>

using namespace std;
class ETable
{
private:
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