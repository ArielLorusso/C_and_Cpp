// Ejemplo de sobrecarga
// Jul. 2011


#include <iostream>
#include <cstdlib>
using namespace std;


void funcion(int);
void funcion(char*);

int main(void)
{
    funcion(123);
    cout << "\n";
    funcion("HOLA");
    cout << "\n";

    cout << "\n\n" ;
    system("PAUSE");
}

void funcion(int x)
{
    cout << "\n El argumento es un entero";
}

void funcion(char *s)
{
    cout << "\n El argumento es un string";
}
