#include <stdexcept>      // std::invalid_argument
#include <iostream>

#include "Cell.h"

using namespace std;

const char STRING_IDENTIFIER = '"';

CellValueHolder::CellValueHolder() {
}

CellValueHolder::~CellValueHolder() {
}

CellValue::CellValue() {
}

CellValue::~CellValue() {
}

Cell::Cell() {
}

Cell::~Cell() {
}

CellValueType Cell::getValueType() {
    return value.type;
}

string Cell::getLastError() {
    return lastError;
}

string Cell::getValueTypeAsString() {
    string result;
    switch (value.type) {
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

bool isLongValue(const string stringValue, long* outValue) {
    size_t startPos = 0;
    if (stringValue == "") {
        return false;
    }
    if (stringValue.at(0) == '-' || stringValue.at(0) == '+') {
        startPos = 1;
    }
    for (size_t pos=startPos; pos < stringValue.size(); pos++) {
        if (stringValue.at(pos) < '0' || stringValue.at(pos) > '9') {
            return false;
        }
    }
    try {
        *outValue = stol(stringValue);
        return true;
    }
    catch (const invalid_argument& ex) {
        return false;
    }
    catch (const out_of_range& ex) {
        return false;
    }
    catch (const std::runtime_error& ex) {
        return false;
    }
}

bool isDoubleValue(const string stringValue, double* outValue) {
    size_t startPos = 0;
    if (stringValue == "") {
        return false;
    }
    if (stringValue.at(0) == '-' || stringValue.at(0) == '+') {
        startPos = 1;
    }
    // Check case 12.4.44
    int dotOccurencies = 0;
    for (size_t pos=startPos; pos < stringValue.size(); pos++) {
        if (stringValue.at(pos) == '.') {
            dotOccurencies++;
        }
    }
    if (dotOccurencies > 1) {
        return false;
    }
    for (size_t pos=startPos; pos < stringValue.size(); pos++) {
        if (stringValue.at(pos) == '.') {
            continue;
        }
        else if (stringValue.at(pos) < '0' || stringValue.at(pos) > '9') {
            return false;
        }
    }
    try {
        *outValue = stod(stringValue);
        return true;
    }
    catch (const invalid_argument& ex) {
        return false;
    }
    catch (const out_of_range& ex) {
        return false;
    }
    catch (const std::runtime_error& ex) {
        return false;
    }
}

bool Cell::setValue(const string stringValue) { // Try to recognize the type of data contained in stringValue.
    long longValue;
    double doubleValue;

    if (stringValue.size() == 0) {
        value.type = CellValueType::EMPTY_VALUE;
        value.value.stringValue = stringValue;
        return true;
    }
    if (isLongValue(stringValue, &longValue)) {
        value.type = CellValueType::LONG_VALUE;
        value.value.longValue = longValue;
        return true;
    }
    if (isDoubleValue(stringValue, &doubleValue)) {
        value.type = CellValueType::DOUBLE_VALUE;
        value.value.doubleValue = doubleValue;
        return true;
    }
    if (stringValue.at(0) == STRING_IDENTIFIER
        && stringValue.at(stringValue.size()-1) == STRING_IDENTIFIER) {
        value.type = CellValueType::STRING_VALUE;
        // Remove the " at the beginning and at the end:
        string clearedStringValue = stringValue;
        clearedStringValue = clearedStringValue.erase (0, 1);
        clearedStringValue = clearedStringValue.erase (clearedStringValue.size()-1, 1);
        value.value.stringValue = clearedStringValue;
        //
        cout << stringValue << " " << clearedStringValue << endl;
        //
        return true;
    }
    if (stringValue.at(0) == '=') {
        value.type = CellValueType::FORMULA;
        value.value.formula = stringValue;
        //
        cout << stringValue << endl;
        //
        return true;
    }
    // Value is not recognized. Raise error:
    value.type = CellValueType::EMPTY_VALUE;
    lastError = "Value is not recognized: " + stringValue;
    return false;
}
