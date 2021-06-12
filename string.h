#pragma once
#include <iostream>
#include <cstring>
#include <algorithm>

class String {
private:
    char* str;
public:
    //default constructor
    String() {
        str = nullptr;
    }

    // constructor
    String(const char* _str);

    //copy constructor
    String(const String& other);

    //destructor
    ~String();

    String& operator=(const String& other);

    bool operator==(const String& other);
    String operator+(const String& other);
    String& operator+=(const String& other);
    const char& operator[](unsigned int index) const;
    const char* c_str() const {
        return str;
    }

    int size() const {
        return strlen(str);
    }

    void set_str(const char* _str);
};
