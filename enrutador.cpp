#include "enrutador.h"

Enrutador::Enrutador()
{

}

bool Enrutador::edit_caracteristic(string car, string data)
{
    bool is_correct = false;
    if(this->tabla_enrutador.find(car)!=this->tabla_enrutador.end()){
        this->tabla_enrutador[car] = data;
        is_correct = true;
    }
    return is_correct;
}

bool Enrutador::add_caracteristic(string car)
{
    bool is_correct = false;
    if(this->tabla_enrutador.find(car)==this->tabla_enrutador.end()){
        this->tabla_enrutador.insert(pair<string,string>(car,""));
        is_correct = true;
    }
    return is_correct;
}

bool Enrutador::delete_caracteristic(string car)
{
    bool is_correct = false;
    if(this->tabla_enrutador.find(car)!=this->tabla_enrutador.end()){
        this->tabla_enrutador.erase(car);
        is_correct = true;
    }
    return is_correct;
}
