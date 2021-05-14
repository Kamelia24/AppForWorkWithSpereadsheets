#ifndef CELLH
#define CELLH
#include <string>

using namespace std;

enum CellValueType
{
    LONG_VALUE,  // Need to be different from the predefined LONG.
    DOUBLE_VALUE,
    STRING_VALUE,
    FORMULA,
    EMPTY_VALUE,
};

struct CellValueHolder
{
    long longValue;
    double doubleValue;
    string stringValue;
    string formula;
    CellValueHolder();
    ~CellValueHolder();
};

class CellValue
{
    public:
    CellValueType type;
    CellValueHolder value;
    bool hasFormula;
    string formulaAsString; // null - no formula
    CellValue();
    ~CellValue();
    // Instance of class CellValue might contain both value and formula. When saving only the formula is saved.
    // Values of the cells are calculated runtime.
};


class Cell
{
    private:
    CellValue value;
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
    template<typename T>
    T FormulaResult(string result);
};
#endif // CELLH
