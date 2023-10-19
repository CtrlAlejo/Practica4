#include "red.h"
#include <fstream>

bool verif_de_enrutadores(string enrutador, const vector<string> valores){
    for (auto it = valores.begin(); it != valores.end(); it++){
        if (enrutador != *it){
            return true;
        }
        else {
            return false;
        }
    }
    return false;
}

void Red::add_enrutador(Enrutador enr)
{
    enrutadores.push_back(enr);
}

void Red::delete_enrutador(string enr)
{
    for(size_t i = 0; i < enrutadores.size(); i++){
        if(enrutadores[i].getNombre() == enr)
            enrutadores.erase(enrutadores.begin() + i);
    }
}

void Red::cargar_red_archivo(string file){
    bool check; ifstream archivo; string linea, valor; vector<string> valores; size_t pos = 0, espacio = 0;// Abre el archivo
    archivo.open(file, ios::in | ios::binary);
    if (archivo.is_open()){
        while (getline(archivo, linea)) { // Lee la primera línea
            // Busca los valores separados por espacios
            while (pos < linea.length()) {
                espacio = linea.find(' ', pos);
                if (espacio != string::npos) {
                    valor = linea.substr(pos, espacio - pos);
                    pos = espacio + 1;
                } else {
                    valor = linea.substr(pos);
                    pos = linea.length();
                }
                valores.push_back(valor);
            }
            check = verif_de_enrutadores(valor, valores);
            if (check == false){
            }
            // Ahora, los valores se almacenan en el vector 'valores'
            cout << endl;
        } if(!getline(archivo, linea)) {
            cerr << "El archivo está vacío." << endl;
        }
        archivo.close();
    }
}























