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
    void enrutadores_archivo(const vector<string>enrutadores, const vector<string>linea);
    vector <Enrutador> privado() const;
};


#endif // RED_H
