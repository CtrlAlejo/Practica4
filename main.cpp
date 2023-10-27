#include <iostream>
#include "red.h"

using namespace std;

int main()
{
    Red red; short seleccion;
    while (true){
        cout << "Seleccione: " << endl <<  "1. Cargar la red desde un archivo" << endl;
        cout << "2. Agregar o remover enrutador" << endl;
        cout << "3. Saber cuanto cuesta enviar un paquete desde un enrutador origen a uno destino." << endl;
        cout << "4. Cual es el camino que debe seguir un paquete para ser enviado de forma eficiente desde un enrutador origen a uno destino." << endl;
        cout << "5. Generar red de forma aleatoria." << endl;
        cin >> seleccion;
        if (seleccion == 1){
            red.cargar_red_archivo(red, "ejemplo.txt");
        }
        if (seleccion == 2){
            red.caminos_optimos();
        }
        if (seleccion == 3){
            red.generar_red_aleatoria();
        }
    }
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
