#ifndef RED_H
#define RED_H
#include "enrutador.h"
#include <vector>

bool verif_de_enrutadores(string enrutador, const vector<string> valores);

class Red {
private:
    vector<Enrutador> enrutadores;
public:
    void cargar_red_archivo(string file);
    void add_enrutador(Enrutador enr);
    void delete_enrutador(string enr);


};


#endif // RED_H
