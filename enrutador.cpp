#include "enrutador.h"

Enrutador::Enrutador(){}

void Enrutador::add_nombre(string nombre)
{
    this->nombre = nombre;
}

void Enrutador::add_enlace(string enlace, int costo)
{
    if(this->tabla_enlaces.find(enlace)==this->tabla_enlaces.end()){
        this->tabla_enlaces.insert(pair<string,int>(enlace,costo));
    }
}

void Enrutador::edit_costo(string enlace, int costo)
{
    if(this->tabla_enlaces.find(enlace)!=this->tabla_enlaces.end()){
        this->tabla_enlaces[enlace] = costo;
    }
}

void Enrutador::delete_enlace(string enlace)
{
    if(this->tabla_enlaces.find(enlace)!=this->tabla_enlaces.end()){
        this->tabla_enlaces.erase(enlace);
    }
}

void Enrutador::print_tabla_enlaces()
{
    for(map<string, int>::iterator it = tabla_enlaces.begin(); it != tabla_enlaces.end(); it++){
        cout <<endl << nombre << "\t" << it->first << "\t" << it->second << endl;

    }
}


















