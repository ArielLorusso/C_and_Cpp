/*Clase string. Manejo de memoria dinámica. Constructores por default, parametrizado
y de copia. Destructor. Sobrecarga de operador de asignación.
rev 2015
*/

#include <QCoreApplication>
#include <iostream>
#include <cstdlib>
#include "ClassString.h"

using namespace std;

int main(int argc, char *argv[])
{
    QCoreApplication app(argc, argv);

    String s1("a"),s2("b"),s3("c");

    String s4 = s1+s2+s3;
    cout<<s4<<endl;
    s1=s2=s3;
    cout<<s1<<endl;
    cout<<s2<<endl;
    cout<<s3<<endl;
/*
    String s5;
    String *s6;
    s6 = new String;

    *s6 = "hola";
    s4 = *s6;
    delete s6;
    cout<<s4<<endl;
    cin.get();
    s4[1] = 'j';
    cout<<s4<<endl;
    cin.get();
    if(s4 == s4)
        cout << "Son iguales";
    if(s4 != s4)
        cout << "Son distintos";
*/
    return app.exec();
}

