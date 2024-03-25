#ifndef CLASSSTRING_H
#define CLASSSTRING_H

#include <iostream>

using namespace std;

class String
{
private:
    char *p;
    int len;
public:
    String();
    String(const char *str);
    String(const String &str);
    ~String();

    String& operator=(const String &str);
    //String& operator=(const char *str);

    String operator+(const String &str);
    String& operator+=(const String &str);

    char& operator[](int index);
    bool operator==(const String &str);
    bool operator!=(const String &str);

    //funciones amigas
    friend ostream& operator<< (ostream &os,const String &str);
};

#endif // CLASSSTRING_H
