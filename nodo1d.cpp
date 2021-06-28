#include "nodo1d.h"

//constructor 1
Nodo1D::Nodo1D(float coord, int id){
    //Nuevo*: (2 renglones)
    x = coord;
    y = 0;
    ID = id;
    coordenadas << x << y;
}

//constructor 2
Nodo1D::Nodo1D(QList<float> coord, int id){
    ID = id;
    coordenadas = coord;
    x = coordenadas[0];
    y = coordenadas[1];
}

//métodos públicos
int Nodo1D::obtener_id(){
    return ID;
}

float Nodo1D::obtener_coord_x(){
    return x;
}

QList<float> Nodo1D::obtener_coordenadas(){
    return coordenadas;
}


