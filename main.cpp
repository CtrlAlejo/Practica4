#include <iostream>
#include "enrutador.h"
#include "red.h"

using namespace std;

int main()
{
    Red red;
    red.cargar_red_archivo("ejemplo.txt");
    red.generar_red_aleatoria();
/*
    Enrutador A;
    A.add_nombre("A");
    A.add_enlace("B", 5);
    A.add_enlace("C", 10);

    Enrutador B;
    B.add_nombre("B");
    B.add_enlace("C", 7);
    B.add_enlace("E", 12);

    A.print_tabla_enlaces();
    cout << endl;
    A.add_enlace("D", 7);
    A.edit_costo("B", 2);
    A.delete_enlace("C");
    A.print_tabla_enlaces();

    Red malla;
    malla.add_enrutador(A);
    malla.add_enrutador(B);
    malla.delete_enrutador("A");
*/


    return 0;
}
