#include <iostream>
#include "red.h"

using namespace std;

int main()
{
    Red red; short seleccion;
    while (true){
        cout << "Seleccione: " << endl <<  "1. Cargar la red desde un archivo" << endl;
        cout << "2. Agregar o remover enrutador." << endl;
        cout << "3. Saber cuanto cuesta enviar un paquete desde un enrutador origen a uno destino y su ruta mas eficiente." << endl;
        cout << "4. Generar red de forma aleatoria." << endl;
        cin >> seleccion;
        if (seleccion == 1){
            red.cargar_red_archivo(red, "ejemplo.txt");
        }
        if (seleccion == 2){
            red.agregar_remover_enrutador(red);
        }
        if (seleccion == 3){
            red.print_enrutadores();
            red.caminos_optimos();
        }
        if (seleccion == 4){
            red.generar_red_aleatoria();
        }
    }
    return 0;
}
