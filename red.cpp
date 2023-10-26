#include "red.h"
#include <fstream>
#include <random>
int conversion_de_string_a_int(const string cadena)
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
    vector<string>nombres;
    unsigned cont2 = 0; int cont = 0; string nombre; int numero, pos = 1;
    while (cont < 2){
        nombre = linea[cont];

        for (auto it = enrutadores.begin(); it != enrutadores.end(); it++){
            if (nombre == *it) cont2++;
        }

        numero = conversion_de_string_a_int(linea[2]);

        if (cont2 == 1){
            malla.crear_enrutador(malla, nombre, linea, pos, numero);
        } else {
            malla.modificar_red(malla, nombres, nombre, linea, pos, numero);
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
        while (getline(archivo, linea)) { // Lee línea por línea
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
        }
        archivo.close();
    }
}

void Red::generar_red_aleatoria(){
    int numero_nodos; double probabilidad; bool verif = true; vector <string> nombres;
    Red red1;
    cout << "Ingrese la cantidad de nodos que desea en la red: " << endl;
    cin >> numero_nodos;
    cout << "Ingrese la probabilidad de que un enlace entre dos nodos exista" << endl;
    cin >> probabilidad;

    if(probabilidad < 1 || probabilidad > 100){
        verif = false;
    }

    while (verif == false){ //Valida que el usuario ingrese un numero desde 1 hasta 100
        cout << "Ingrese un asiento valido, desde 1 hasta 20: ";
        cin >> probabilidad;
        if(probabilidad >= 1 && probabilidad <= 100){
            verif = true;
        }
    }
    red1.generacion_de_enrutadores(numero_nodos, red1, nombres);
    red1.definicion_de_enlaces(nombres, probabilidad);
}

void Red::crear_enrutador(Red &malla, const string nombre, const vector<string>linea, const int pos, const int numero){
    Enrutador enrutador;
    enrutador.add_nombre(nombre);
    enrutador.add_enlace(linea[pos], numero);
    malla.add_enrutador(enrutador);
}

void Red::crear_enrutador(Red &malla, const string nombre){
    Enrutador enrutador;
    enrutador.add_nombre(nombre);
    malla.add_enrutador(enrutador);
}

void Red::modificar_red(Red &malla, vector<string>nombres, const string nombre, const vector<string>linea, const int pos, const int numero){
    int i = 0;
    nombres = malla.nombres_enrutadores();

    for (auto it = nombres.begin(); it != nombres.end(); it++){
        if (nombre == *it){
            malla.modificar_enrutacion(i, linea[pos], numero);
        }
        i++;
    }
}

string numero_a_string(const int numero)
{
    string snumero;
    snumero = to_string(numero);
    return snumero;
}

void Red::generacion_de_enrutadores(const unsigned n_enrutadores, Red &red, vector <string> &nombres){
    string nombre;

    for (unsigned i = 0; i < n_enrutadores; i++){
        nombre = numero_a_string(i);
        nombres.push_back(nombre);
        red.crear_enrutador(red, nombre);
    }
}

void Red::definicion_de_enlaces(vector <string> nombres, double probabilidad){

    for (size_t i = 0; i < nombres.size(); i++){
        for (size_t j = 0; j < nombres.size(); j++){
            if (i == j) continue;
            evaluar_tabla_enr(nombres[j], enrutadores[i], probabilidad);
        }
    }
}



void Red::evaluar_tabla_enr(string nombre, Enrutador &nodo, const double probabilidad)
{
    string nombre2; int costo_a;
    if (nodo.verif_enlace(nombre) == true){
        if (moneda(probabilidad) == true){
            nombre2 = nodo.getNombre();
            costo_a = costo_aleatorio();
            nodo.add_enlace(nombre, costo_a);
            for (size_t i = 0; i < enrutadores.size(); i++){
                if (enrutadores[i].getNombre() == nombre){
                    enrutadores[i].add_enlace(nombre2, costo_a);
                }
            }
        }
    }
}
bool moneda(double probabilidad)
{
    probabilidad = probabilidad / 100.0;
    double numeroAleatorio;
    random_device rd;
    mt19937 generador(rd());
    uniform_real_distribution<double> distribucion(0.0, 1.0);

    numeroAleatorio = distribucion(generador);

    return numeroAleatorio < probabilidad;
}
int costo_aleatorio()
{
    random_device rd;
    mt19937 generador(rd());
    uniform_real_distribution<double> distribucion(1, 100);
    return int(distribucion(generador));
}
