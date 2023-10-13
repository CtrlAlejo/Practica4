#ifndef RED_H
#define RED_H
#include "enrutador.h"

class Red {
private:
    map <Enrutador, Enrutador> red;
public:
    void cargar_red_archivo();
    void add_enrutador();
    void delete_enrutador();

};


#endif // RED_H
