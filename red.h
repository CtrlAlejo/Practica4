#ifndef RED_H
#define RED_H
#include "enrutador.h"
#include <vector>

int conversion_de_char_a_int(const char *cadena);

class Red {
private:
    vector<Enrutador> enrutadores;
public:
    void cargar_red_archivo(string file);
    void add_enrutador(Enrutador enr);
    void delete_enrutador(string enr);
    void modificar_enrutacion (size_t posicion, const string& nuevo_enr, int costo);
    void enrutadores_archivo(Red &malla, const vector<string>enrutadores, const vector<string>linea);
    vector <Enrutador> privado() const;
    void recorrer_enrutadores();
    vector <string> nombres_enrutadores() const;
    const vector <Enrutador>& getRed() const;
    Enrutador obtenerEnrutador(size_t posicion);
};


#endif // RED_H
