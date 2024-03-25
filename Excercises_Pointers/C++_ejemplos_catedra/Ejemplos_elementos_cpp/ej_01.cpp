// Scope de variables locales y globales
// con el operador "::"
// Rev. Ago 2011

#include <iostream>
#include <cstdio>
#include <cstdlib>
using namespace std;

int a;

int main(void)
{
    int a;
    a=5;
    ::a=10;

    system("CLS");
    cout<< "\n a local vale \t " << a;
    cout<< "\n a global vale\t " << ::a;
    cout<< "\n\n";

    system("PAUSE");
}
