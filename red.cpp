#include "red.h"
#include <fstream>

int conversion_de_char_a_int(const string cadena)
{
    //Recibe una cadena de caracteres numericos y la convierte a enteros
    int numero = 0, i = 0, signo = 1;
    if (cadena[0] == '-') {
        signo = -1;
        i = 1;
    }
    while(cadena[i] != '\0'){
        if(cadena[i] >= '0' && cadena[i] <= '9'){
            numero = numero * 10 + (cadena[i] - '0');
        }
        else{
            break;
        }
        i++;
    }
    return numero * signo;
}
void Red::enrutadores_archivo(Red &malla, const vector<string>enrutadores, const vector<string>linea)
{
    vector<string>nombres; vector<Enrutador> nodos;
    unsigned cont2 = 0, i = 0; int cont = 0; string nombre; int numero, pos = 1;
    while (cont < 2){
        nombre = linea[cont];
        for (auto it = enrutadores.begin(); it != enrutadores.end(); it++){
            if (nombre == *it) cont2++;
        }
        numero = conversion_de_char_a_int(linea[2]);
        if (cont2 == 1){
            Enrutador enrutador;
            enrutador.add_nombre(nombre);
            enrutador.add_enlace(linea[pos], numero);
            malla.add_enrutador(enrutador);
        } else {
            nodos = malla.getRed();
            nombres = malla.nombres_enrutadores();
            for (auto it = nombres.begin(); it != nombres.end(); it++){
                if (nombre == *it){
                    modificar_enrutacion(i, linea[pos], numero);
                }
                i++;
            }
            i = 0;
        }
        cont++;
        cont2 = 0;
        pos--;
    }
}

vector<Enrutador> Red::privado() const
{
    return enrutadores;
}

vector<string> Red::nombres_enrutadores() const{
    vector<string>nombres;
    for (const Enrutador& objeto : enrutadores){
        nombres.push_back(objeto.getNombre());
    }
    return nombres;
}

const vector<Enrutador> &Red::getRed() const
{
    return enrutadores;
}

Enrutador Red::obtenerEnrutador(size_t posicion){
    if (posicion < enrutadores.size()){
        return enrutadores[posicion];
    } else {
        cout << "Posicion fuera de rango." << endl;
    }
    return enrutadores[posicion];
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

void Red::modificar_enrutacion(size_t posicion, const string &nuevo_enr, int costo){
    if (posicion < enrutadores.size()){
        enrutadores[posicion].add_enlace(nuevo_enr, costo);
    } else {
        cout << "Posicion fuera de rango." << endl;
    }
}

void Red::cargar_red_archivo(string file)
{
    Red red;
    int cont = 0; ifstream archivo; string linea, valor; vector<string> valores; vector<string> aux; size_t pos = 0, espacio = 0;
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
                cont++;
                aux.push_back(valor);
                if (cont < 3){
                    valores.push_back(valor);
                }
                if (cont == 3){
                    cont = 0;
                }
            }
            red.enrutadores_archivo(red, valores, aux);
            aux.clear();
            pos = 0;

            // Ahora, los valores se almacenan en el vector 'valores'
        }
        archivo.close();
    }
}
