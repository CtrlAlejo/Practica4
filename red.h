#ifndef RED_H
#define RED_H
#include "enrutador.h"
#include <vector>

class Red {
private:
    vector<Enrutador> enrutadores;
public:
    void cargar_red_archivo();
    void add_enrutador(Enrutador enr);
    void delete_enrutador(string enr);


};


#endif // RED_H
