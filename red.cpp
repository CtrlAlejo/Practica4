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
    while (cont < 2){//Agrega los enlaces en los dos enritadores
        nombre = linea[cont];

        for (auto it = enrutadores.begin(); it != enrutadores.end(); it++){//Busca la cantidad de veces que esta repetido un nodo en el archivo
            if (nombre == *it) cont2++;
        }

        numero = conversion_de_string_a_int(linea[2]);

        if (cont2 == 1){//Crea el enrutador
            malla.crear_enrutador(malla, nombre, linea, pos, numero);
        } else { //Busca el enrutador y lo modifica
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

void Red::lectura_de_archivo(Red &red, ifstream &archivo){ //Lee el archivo de la red
    int cont = 0; string linea, valor; vector<string> valores; vector<string> aux; size_t pos = 0, espacio = 0;
    while (getline(archivo, linea)) { // Lee línea por línea
        // Busca los valores separados por espacios
        while (pos < linea.length()) {//Lee la linea
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
            if (cont < 3){//Ingresa los nombres de los enrutadores
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
}

void Red::cargar_red_archivo(Red &red, string file) //Carga el archivo
{
    ifstream archivo;
    archivo.open(file, ios::in | ios::binary);
    if (archivo.is_open()){
        red.lectura_de_archivo(red, archivo);
        archivo.close();
    }
}

void Red::generar_red_aleatoria(Red &red1){
    int numero_nodos; double probabilidad; bool verif = true; vector <string> nombres;
    cout << "Ingrese la cantidad de nodos que desea en la red: " << endl;
    cin >> numero_nodos;
    cout << "Ingrese la probabilidad de que un enlace entre dos nodos exista" << endl;
    cin >> probabilidad;

    if(probabilidad < 1 || probabilidad > 100){//Valida que la probabilidad este entre 0 y 100
        verif = false;
    }

    while (verif == false){ //Valida que el usuario ingrese un numero desde 1 hasta 100
        cout << "Ingrese un asiento valido, desde 1 hasta 20: ";
        cin >> probabilidad;
        if(probabilidad >= 1 && probabilidad <= 100){
            verif = true;
        }
    }
    red1.generacion_de_enrutadores(numero_nodos, red1, nombres); //Genera los enrutadores en la red
    red1.definicion_de_enlaces(nombres, probabilidad); //Define los enlaces de cada enrutador con la probabilidad
}

void Red::crear_enrutador(Red &malla, const string nombre, const vector<string>linea, const int pos, const int numero){
    Enrutador enrutador; //Añade el nombre y los enlaces, despues almacena el enrutador en la red
    enrutador.add_nombre(nombre);
    enrutador.add_enlace(linea[pos], numero);
    malla.add_enrutador(enrutador);
}

void Red::crear_enrutador(Red &malla, const string nombre){
    Enrutador enrutador;//Añade solo el nombre del enrutador
    enrutador.add_nombre(nombre);
    malla.add_enrutador(enrutador);
}

void Red::modificar_red(Red &malla, vector<string>nombres, const string nombre, const vector<string>linea, const int pos, const int numero){
    int i = 0; //Modifica los enlaces de la red
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

    for (unsigned i = 0; i < n_enrutadores; i++){//Genera los enrutadores con el valor que ingreso el usuario
        nombre = numero_a_string(i);
        nombres.push_back(nombre);
        red.crear_enrutador(red, nombre);
    }
}

void Red::definicion_de_enlaces(vector <string> nombres, double probabilidad){
//Modifica el enrutamiento en base al enrutador que se procesa en el momento
    for (size_t i = 0; i < nombres.size(); i++){
        for (size_t j = 0; j < nombres.size(); j++){
            if (i == j) continue;
            evaluar_tabla_enr(nombres[j], enrutadores[i], probabilidad);
        }
    }
}



void Red::evaluar_tabla_enr(string nombre, Enrutador &nodo, const double probabilidad)
{ //Verifica que no se dupliquen enlaces
    string nombre2; int costo_a;
    if (nodo.verif_enlace(nombre) == false){
        if (moneda(probabilidad) == true){
            nombre2 = nodo.getNombre();
            costo_a = costo_aleatorio();
            nodo.add_enlace(nombre, costo_a);
            for (size_t i = 0; i < enrutadores.size(); i++){//Añade enlaces de cada enrutador
                if (enrutadores[i].getNombre() == nombre){
                    enrutadores[i].add_enlace(nombre2, costo_a);
                }
            }
        }
    }
}
bool moneda(double probabilidad)
{ //Lanza la moneda con la probabilidad que ingresa el usuario
    probabilidad = probabilidad / 100.0;
    double numeroAleatorio;
    random_device rd;
    mt19937 generador(rd());
    uniform_real_distribution<double> distribucion(0.0, 1.0);

    numeroAleatorio = distribucion(generador);

    return numeroAleatorio < probabilidad;
}
int costo_aleatorio()
{ //Define un costo aleatorio entre 0 y 100
    random_device rd;
    mt19937 generador(rd());
    uniform_real_distribution<double> distribucion(1, 100);
    return int(distribucion(generador));
}

vector<int> dijkstra(const std::vector<std::vector<int>>& grafo, int origen, int destino, int& costoTotal) {
    int numNodos = grafo.size();
    std::vector<int> distancias(numNodos, INT_MAX);
    std::vector<int> ruta(numNodos, -1);
    std::vector<bool> visitados(numNodos, false);
    distancias[origen] = 0;

    for (int i = 0; i < numNodos - 1; i++) {
        int u = -1;
        for (int j = 0; j < numNodos; j++) {
            if (!visitados[j] && (u == -1 || distancias[j] < distancias[u])) {
                u = j;
            }
        }

        visitados[u] = true;

        for (int v = 0; v < numNodos; v++) {
            if (!visitados[v] && grafo[u][v] && distancias[u] != INT_MAX &&
                distancias[u] + grafo[u][v] < distancias[v]) {
                distancias[v] = distancias[u] + grafo[u][v];
                ruta[v] = u;
            }
        }
    }

    // Construir la ruta desde el destino al origen y calcular el costo
    std::vector<int> camino;
    int nodoActual = destino;
    costoTotal = 0;
    while (nodoActual != -1) {
        camino.insert(camino.begin(), nodoActual);
        int nodoAnterior = ruta[nodoActual];
        if (nodoAnterior != -1) {
            costoTotal += grafo[nodoActual][nodoAnterior];
        }
        nodoActual = nodoAnterior;
    }

    return camino;
}

void Red::imprimir_ruta_paquete(vector <int> camino, string nodo1, string nodo2) //Imprime en pantalla la ruta del paquete
{
    vector<string>n_enrutadores;
    n_enrutadores = nombres_enrutadores();
    if (!camino.empty()) {
        cout << "Ruta desde " << nodo1 << " hasta " << nodo2 << ": ";
        for (int nodo : camino) {
            cout << n_enrutadores[nodo] << " -> ";
        }
        cout << "Fin" << endl;
    }
}

void Red::imprimir_costo(int costoTotal)
{
    cout << "Costo total: " << costoTotal << endl;
}

vector <vector<int>> Red::lista_adyacencia(vector<string> &n_enrutadores){ //Crea la lista de adyacencia de la red
    string nombre; vector <vector<int>> grafo; vector <int> aux;
    n_enrutadores = nombres_enrutadores();
    for (size_t i = 0; i < enrutadores.size(); i++){
        for (size_t j = 0; j < n_enrutadores.size(); j++){
            nombre = n_enrutadores[j];
            aux.push_back(enrutadores[i].obtener_costo(nombre));
        }
        grafo.push_back(aux);
        aux.clear();
    }
    return grafo;
}

void Red::caminos_optimos(){ //Contiene los modos y los algoritmos para los caminos mas cortos
    int origen, destino, costoTotal = 0, modo; string nodo1, nodo2; vector<string> n_enrutadores; vector <vector<int>> grafo; vector <int> camino;
    grafo = lista_adyacencia(n_enrutadores);
    cout << "Ingrese 1 si desea conocer el costo de envio del paquete o 2 si desea saber la ruta eficiente de su paquete: ";
    cin >> modo;
    cout << "Ingrese el enrutador origen: ";
    cin >> nodo1;
    origen = posicion_valor(n_enrutadores, nodo1);
    cout << "Ingrese el enrutador de destino: ";
    cin >> nodo2;
    destino = posicion_valor(n_enrutadores, nodo2);
    camino = dijkstra(grafo, origen, destino, costoTotal);
    if (modo == 1){
        imprimir_costo(costoTotal);
    } else if (modo == 2) {
        imprimir_ruta_paquete(camino, nodo1, nodo2);
    }
}

int posicion_valor(vector <string> n_enrutadores, string nombre){ //Define la posicion de un enrutador con un valor
    int cont = 0;
    for (size_t i = 0; i < n_enrutadores.size(); i++){
        cont = i;
        if (n_enrutadores[i] == nombre){
            return cont;
        }
    }
    return cont;
}

void Red::agregar_remover_enrutador(Red &red){ //Agrega y remueve enrutadores actualizando la topologia de la red
    int opc = 0, costo; Enrutador enr; string nombre, enlace;
    cout << "Ingrese 1 si desea agregar un enrutador, ingrese 2 si desea remover un enrutador: ";
    cin >> opc;
    if(opc == 1){
        cout << "Ingrese el nombre del enrutador: ";
        cin >> nombre;
        print_enrutadores();
        cout << "Ingrese a cual enrutador desea enlazarlo: ";
        cin >> enlace;
        cout << "Ingrese el costo: ";
        cin >> costo;
        enr.add_nombre(nombre);
        enr.add_enlace(enlace, costo);
        red.add_enrutador(enr);
        for (size_t i = 0; i < enrutadores.size(); i++){
            if (enrutadores[i].getNombre() == enlace){
                enrutadores[i].add_enlace(nombre, costo);
            }
        }
    }
    else if(opc == 2){
        print_enrutadores();
        cout << "Ingrese el nombre del enrutador que desea remover: ";
        cin >> nombre;
        red.delete_enrutador(nombre);
        for (size_t i = 0; i < enrutadores.size(); i++){
            enrutadores[i].delete_enlace(nombre);
        }
    }
}

void Red::print_enrutadores(){ //Imprime los enrutadores de la red
    cout << "Lista de enrutadores: ";
    for(size_t i = 0; i < enrutadores.size(); i++){
        cout << enrutadores[i].getNombre() << " ";
    }
    cout <<endl;
}







