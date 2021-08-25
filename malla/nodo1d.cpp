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
//constructor 3
Nodo1D::Nodo1D(float coordX, float coordY)
{

}
//constructor 4
Nodo1D::Nodo1D(QList<float> coord)
{

}


//métodos públicos
int Nodo1D::obtenerID() const{
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

//Setters
void Nodo1D::modificarCoordenadas(QList<float> l)
{

}

void Nodo1D::modificarCoorX(float x)
{

}

void Nodo1D::modificarCoorY(float y)
{

}

void Nodo1D::modificarListaAdyacentes(QList<Elemento1D> adyacente)
{

}

void Nodo1D::modificarElementoAdyacente(Elemento1D ady)
{

}






