#include <iostream>
#include "red.h"

using namespace std;

int main()
{
    Red red; short seleccion; vector <Enrutador> verif; string file;
    while (true){
        cout << "Seleccione: " << endl <<  "1. Cargar la red desde un archivo" << endl;
        cout << "2. Agregar o remover enrutador." << endl;
        cout << "3. Saber cuanto cuesta enviar un paquete desde un enrutador origen a uno destino y su ruta mas eficiente." << endl;
        cout << "4. Generar red de forma aleatoria." << endl;
        cout << "5. Salir del programa." << endl;
        cin >> seleccion;
        if (seleccion == 1){
            cout << "Ingrese el nombre del archivo: ";
            cin >> file;
            red.cargar_red_archivo(red, file);
            cout << "Red cargada con exito!" << endl;
        }
        if (seleccion == 2){
            verif = red.getRed();
            if (verif.empty()){
                cout << "No hay ninguna red cargada" << endl;
            } else {
                red.agregar_remover_enrutador(red);
            }
        }
        if (seleccion == 3){
            verif = red.getRed();
            if (verif.empty()){
                cout << "No hay ninguna red cargada" << endl;
            } else {
                red.print_enrutadores();
                red.caminos_optimos();
            }
        }
        if (seleccion == 4){
            red.generar_red_aleatoria(red);
        }
        if (seleccion == 5){
            break;
        }
    }
    return 0;
}
