#ifndef CELLH
#define CELLH

#include "string.h"

using namespace std;
///contains data types
enum CellValueType
{
    LONG_VALUE,
    DOUBLE_VALUE,
    STRING_VALUE,
    FORMULA,
    EMPTY_VALUE,
};

template<typename T>
///class which contains info of the cell.
class Cell
{
private:
    CellValueType type;
    T value;
    string formulaAsString;
    string lastError = "";

public:
    Cell();
    ~Cell();
    CellValueType getValueType();
    string getValueTypeAsString();
    long getValueL();
    double getValueD();
    string getValueS();
    // Convert string value:
    bool setValue(const string stringValue);
    string getLastError();
    template <typename T>
    T FormulaResult(string result);
};
#endif // CELLH
