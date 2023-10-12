#ifndef ENRUTADOR_H
#define ENRUTADOR_H
#include <string>
#include <map>
using namespace std;

class Enrutador{
private:
    map <string,string> tabla_enrutador;
public:
    Enrutador();
    bool edit_caracteristic(string nombre, string costo);
    bool add_caracteristic(string nombre);
    bool delete_caracteristic(string nombre);
};

#endif // ENRUTADOR_H
