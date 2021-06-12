#include "string.h"

String::String(const char* _str) {
    str = new char[strlen(_str) + 1];
    strcpy(str, _str);
}

String::~String() {
    delete[] str;
}

void String::set_str(const char* _str) {
    if(str != nullptr) {
        delete[] str;
    }
    str = new char[strlen(_str) + 1];
    strcpy(str, _str);
}

String::String(const String& other) {
    str = new char[other.size() + 1];
    strcpy(str, other.c_str());
}

String& String::operator=(const String& other) {
    if(this != &other) {
        if(str != nullptr) {
            delete[] str;
        }
        str = new char[strlen(other.str) + 1];
        strcpy(str, other.str);
    }
    return *this;
}

bool String::operator==(const String& other) {
    return strcmp(str, other.str) == 0 ? true : false;
}

String String::operator+(const String& other) {
    char* result = new char[strlen(str) + strlen(other.str) + 1];
    strcpy(result, str);
    strcat(result, other.str);
    String res(result);
    delete[] result;
    return res;
}

String& String::operator+=(const String& other) {
    *this = *this + other;
    return *this;
}

const char& String::operator[](unsigned int index) const {
    if(index < strlen(str)) return str[index];
}
