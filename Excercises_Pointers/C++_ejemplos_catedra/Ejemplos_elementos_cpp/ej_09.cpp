// Ejemplo de sobrecarga
// Jul 2011

#include <iostream>
#include <cstdlib>
using namespace std;

char* funcion(int);
char* funcion(char*);

int main(void)
{
    cout << funcion(123) << "\n";
    cout << funcion("HOLA") << "\n";

    cout << "\n\n" ;
    system("PAUSE");
}

char* funcion(int x)
{
    char *s={"El argumento es un entero"};
    return(s);
}

char* funcion(char *s)
{
    char *r={"El argumento es un string"};
    return(r);
}
