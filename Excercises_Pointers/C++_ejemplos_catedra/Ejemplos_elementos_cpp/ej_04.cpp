// LLamada por referencia
// Septiembre 2007  (rev Jul 2011)

#include <iostream>
#include <cstdlib>
#include <cmath>
using namespace std;

float sup_circ(float &);

int main(void)
{
    cout << "Ingrese el radio:\t";
    float radio;
    cin>>radio;

    float sup;
    sup=sup_circ(radio);
    cout << "La superficie es:\t" << sup;

    cout << "\n\n";
    system("PAUSE");
}

float sup_circ(float &R)
{
    return(M_PI*R*R);
}
