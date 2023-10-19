# include "red.h"

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
























