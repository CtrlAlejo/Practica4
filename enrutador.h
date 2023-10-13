#ifndef ENRUTADOR_H
#define ENRUTADOR_H
#include <iostream>
#include <string>
#include <map>
using namespace std;

class Enrutador{
private:
    string nombre;
    map <string,int> tabla_enlaces;
public:
    Enrutador();
    void add_nombre(string nombre);
    void add_enlace(string enlace, int costo);
    void edit_costo(string enlace, int costo);
    void delete_enlace(string enlace);
    void print_tabla_enlaces();
};

#endif // ENRUTADOR_H
