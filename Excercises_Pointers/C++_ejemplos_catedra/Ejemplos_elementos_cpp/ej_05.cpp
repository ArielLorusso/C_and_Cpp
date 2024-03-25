// Comparacion entre las tres tecnicas de llamada a funcion
// Llamada por valor, por referencia (con puntero) y por referencia directa
// Septiembre 2007  (Rev Jul. 2011)

#include <iostream>
#include <cstdlib>
#include <cmath>
using namespace std;

void f1(int);
void f2(int *);
void f3(int &);

int main(void)
{
    int x1=2, x2=5, x3=10;

    f1(x1);		//Llamada por valor
    f2(&x2);    //Llamada por referencia (mediante un puntero)
    f3(x3);		//Llamada por referencia (mediante operador &)

    cout << "\nx1 = " << x1 << "\nx2 = " << x2 << "\nx3 = " << x3 << "\n";

    cout << "\n\n" ;
    system("PAUSE");
}

void f1(int valor)
{
    valor+=2;
}

void f2(int *punt)
{
    *punt+=2;
}

void f3(int &ref)
{
    ref+=2;
}
