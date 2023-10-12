#include <iostream>
#include "enrutador.h"

using namespace std;

int main()
{
    Enrutador a;
    a.add_caracteristic("Nombre");
    a.add_caracteristic("Enlace");
    a.add_caracteristic("Costo");
    a.edit_caracteristic("Nombre","A");
    a.edit_caracteristic("Enlace","B");
    a.edit_caracteristic("Costo","0");
    return 0;
}
