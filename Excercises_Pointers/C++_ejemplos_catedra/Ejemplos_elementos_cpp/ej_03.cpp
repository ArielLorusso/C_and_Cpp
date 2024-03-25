// Macro con operador "in line"
// Octubre 2007 (rev. Ago 2011)


#include <iostream>
#include <cstdlib>
using namespace std;

inline float cubo(float l)
{
    return(l*l*l);
}

int main(void)
{
    cout << "Ingrese largo:\t";
    float largo;
    cin >> largo;
    cout << "\nEl volumen es:\t" << cubo(largo);
    cout << "\n\n";

    system("PAUSE");
}
