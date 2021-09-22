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
int Nodo1D::obtenerID(){
    return ID;
}

float Nodo1D::obtenerCoordX(){
    return x;
}

float Nodo1D::obtenerCoordY(){
    return y;
}

QList<float> Nodo1D::obtenerCoordenadas(){
    return coordenadas;
}

void Nodo1D::modificarY(float)
{

}

void Nodo1D::modificarX(float)
{

}

void Nodo1D::modificarCoordenadas(QList<float>)
{

}



