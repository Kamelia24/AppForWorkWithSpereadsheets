#include <stdexcept> // std::invalid_argument
#include <iostream>

#include "Cell.h"

using namespace std;

const char STRING_IDENTIFIER = '"';

Cell::Cell()
{
}

Cell::~Cell()
{
}

CellValueType Cell::getValueType()
{
    return value.type;
}

string Cell::getLastError()
{
    return lastError;
}

string Cell::getValueTypeAsString()
{
    string result;
    switch (value.type)
    {
    case LONG_VALUE:
        result = "Long value";
        break;
    case DOUBLE_VALUE:
        result = "Double value";
        break;
    case STRING_VALUE:
        result = "String value";
        break;
    case EMPTY_VALUE:
        result = "Empty value";
        break;
    case FORMULA:
        result = "Formula";
        break;
    default:
        result = "Unrecognized type!";
    }
    return result;
}

///function which returns the type of the value in a cell
CellValueType getValueType(const string stringValue)
{
    size_t startPos = 0;
    if (stringValue == "")
    {
        return CellValueType::EMPTY_VALUE;
    }
    if (stringValue.at(0) == '-' || stringValue.at(0) == '+')
    {
        startPos = 1;
    }
    for (size_t pos = startPos; pos < stringValue.size(); pos++)
    {
        if (stringValue.at(pos) < '0' || stringValue.at(pos) > '9')
        {
            return false;
        }
    }
    // Check case 12.4.44
    int dotOccurencies = 0;
    for (size_t pos = startPos; pos < stringValue.size(); pos++)
    {
        if (stringValue.at(pos) == '.')
        {
            dotOccurencies++;
        }
    }
    if (dotOccurencies > 1)
    {
        return CellValueType::EMPTY_VALUE;
    }

    for (size_t pos = startPos; pos < stringValue.size(); pos++)
    {
        if (stringValue.at(pos) == '.')
        {
            continue;
        }
        else if (stringValue.at(pos) < '0' || stringValue.at(pos) > '9')
        {
            return CellValueType::EMPTY_VALUE;
        }
    }
    if (dotOccurencies == 1)
    {
        return CellValueType::DOUBLE_VALUE;
    }
    else
    {
        return CellValueType::LONG_VALUE;
    }
}

bool Cell::setValue(const string stringValue)
{ // Try to recognize the type of data contained in stringValue.
    long longValue;
    double doubleValue;

    type=getValueType(const string stringValue);
    if (stringValue.at(0) == STRING_IDENTIFIER && stringValue.at(stringValue.size() - 1) == STRING_IDENTIFIER)
    {
        type = CellValueType::STRING_VALUE;
        // Remove the " at the beginning and at the end:
        string clearedStringValue = stringValue;
        clearedStringValue = clearedStringValue.erase(0, 1);
        clearedStringValue = clearedStringValue.erase(clearedStringValue.size() - 1, 1);
        value = clearedStringValue;
        //
        cout << stringValue << " " << clearedStringValue << endl;
        //
        return true;
    }
    if (stringValue.at(0) == '=')
    {
        type = CellValueType::FORMULA;
        value = stringValue;
        //
        cout << stringValue << endl;
        //
        return true;
    }
    // Value is not recognized. Raise error:
    type = CellValueType::EMPTY_VALUE;
    lastError = "Value is not recognized: " + stringValue;
    return false;
}
///function which converts the formula to a number
template <typename T>
T Cell::FormulaResult(string formula)
{ //returns the value of the formula (ako ne e s adresi)
    T firstAttribute;
    T secondAttribute;
    string action;
    //funkciq koqto razdelq formulata na chasti
    long longValue;
    double doubleValue;
    if (firstAttribute.at(0) == 'R')
    { //if its address get its value
        //izvikva funkciq koqto namira kletkata i vrushta stoinostta
    }
    if (secondAttribute.at(0) == 'R')
    { //if its address get its value
        //izvikva funkciq koqto namira kletkata i vrushta stoinostta
    }
    if (!isLongValue(firstAttribute, &longValue) && !isDoubleValue(firstAttribute, &doubleValue))
    {
        firstAttribute = 0;
    }
    if (!isLongValue(secondAttribute, &longValue) && !isDoubleValue(secondAttribute, &doubleValue))
    {
        secondAttribute = 0;
    }
    switch (action)
    {
    case '+':
        return firstAttribute + secondAttribute;
        break;
    case '-':
        return firstAttribute - secondAttribute;
        break;
    case '*':
        return firstAttribute * secondAttribute;
        break;
    case '/':
        return firstAttribute / secondAttribute;
        break;
    case '%':
        return firstAttribute % secondAttribute;
        break;
    default:
        lastError = 'Unrecognised action in formula';
        return lastError;
    }
}
