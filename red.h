#ifndef RED_H
#define RED_H
#include "enrutador.h"
#include <vector>

int conversion_de_string_a_int(const char *cadena);
string numero_a_string(int numero);
bool moneda(double probabilidad);
int costo_aleatorio();

class Red {
private:
    vector<Enrutador> enrutadores;
public:
    void crear_enrutador(Red &malla, const string nombre, const vector<string>linea, const int pos, const int numero);

    void crear_enrutador(Red &malla, const string nombre);

    void cargar_red_archivo(string file);

    void modificar_red(Red &malla, vector<string>nombres, const string nombre, const vector<string>linea, const int pos, const int numero);

    void add_enrutador(Enrutador enr);

    void delete_enrutador(string enr);

    void modificar_enrutacion (size_t posicion, const string& nuevo_enr, int costo);

    void enrutadores_archivo(Red &malla, const vector<string>enrutadores, const vector<string>linea);

    void generar_red_aleatoria();

    void generacion_de_enrutadores(const unsigned n_enrutadores, Red &red, vector <string> &nombres);

    vector <Enrutador> privado() const;

    void recorrer_enrutadores();

    vector <string> nombres_enrutadores() const;

    const vector <Enrutador>& getRed() const;

    Enrutador obtenerEnrutador(size_t posicion);

    void generacion_de_red(Red &red, unsigned n_enrutadores);

    void definicion_de_enlaces(vector <string> nombres, double probabilidad);

    void evaluar_tabla_enr(string nombre, Enrutador &nodo, const double probabilidad);
};


#endif // RED_H
