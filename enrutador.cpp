#include "enrutador.h"

Enrutador::Enrutador(){}

string Enrutador::getNombre() const
{
    return nombre;
}

map<string, int> Enrutador::getTabla_enlaces() const
{
    return tabla_enlaces;
}

void Enrutador::setTabla_enlaces(const map<string, int> &newTabla_enlaces)
{
    tabla_enlaces = newTabla_enlaces;
}

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

bool Enrutador::verif_enlace(string enlace)
{
    if(this->tabla_enlaces.find(enlace)==this->tabla_enlaces.end()){
        return false;
    }
    return true;
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

int Enrutador::obtener_costo(string clave)
{
    int costo = 0;
    if(this->tabla_enlaces.find(clave)!=this->tabla_enlaces.end()){
        costo = tabla_enlaces[clave];
    }
    return costo;
}
