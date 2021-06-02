#include "nodo1d.h"

Nodo1D::Nodo1D(QList<float> coord, int id){
    crearNodo(coord, int id);
}

void Nodo1D::crearNodo(QList<float> coord, int id){
    coordenadas = coord;
    ID = id;



}


