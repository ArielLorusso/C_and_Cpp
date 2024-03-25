#include "ClassString.h"
#include <cstring>

String::String()   //constructor x default
{
    len=0;
    p=NULL;

}
//------------------------------------------------------------------------------
String::String(const char *str) //constructor parametrizado.
{
    len = strlen(str);
    p = new char [len+1];
    strcpy(p, str);
}
//------------------------------------------------------------------------------
String::String(const String& str) //constructor de copia
{
    len = str.len;
    p = new char [len+1];
    strcpy (p, str.p);
}
//------------------------------------------------------------------------------
String::~String()
{
    delete[] p;
}
//------------------------------------------------------------------------------
// operador de asignaci�n: asigna objetos iguales
String& String::operator=(const String& str)
{
    delete[] p;           //libero y pido memoria de nuevo
    len = str.len;
    p = new char [len+1];
    strcpy (p, str.p);
    return *this;  //devuelvo el propio objeto para permitir asignaciones m�ltiples
}

//------------------------------------------------------------------------------
// operador de asignaci�n: Un objeto igual a una cadena. No es realmente necesario
// porque utiliza String& String::operator=(const String& str) junto con el constructor
// parametrizado
/*String& String::operator=(const char *str)
{
    delete [] p;             //libero y pido memoria de nuevo
    len = strlen(str);
    p = new char [len+1];

    strcpy (p, str);
    return *this;    //devuelvo el propio objeto para permitir asignaciones m�ltiples
}*/

String String::operator+(const String &str)
{
    char *s = new char(len+str.len+1);
    strcpy(s, p);
    strcat(s, str.p);
    String aux(s);
    delete[] s;	
    return aux;
}

String& String::operator+=(const String &str)
{
    char *s = new char(len+str.len+1);
    strcpy(s, p);
    strcat(s, str.p);
    delete[] p;
    len = len+str.len;
    p = s;
    return *this;
}

char& String::operator[](int index)
{
    return p[index];
}

bool String::operator==(const String &str)
{
    return !strcmp(p,str.p);
}

bool String::operator!=(const String &str)
{
    return strcmp(p, str.p);
}

//------------------------------------------------------------------------------
//sobrecarga de ostream para el uso de cout
//No se le pone contante al ostream
ostream& operator<<(ostream& os, const String& str)
{
    os << str.p;
    return os;
}

