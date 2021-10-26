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
    x = coordX;
    y = coordY;
    coordenadas[0] = coordX;
    coordenadas[1] = coordY;

}
//constructor 4
Nodo1D::Nodo1D(QList<float> coord)
{
    coordenadas = coord;
    x = coord[0];
    y = coord[1];

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

QList<Elemento1D> Nodo1D::obtenerAdyacentes()
{
    return adyacentes;
}


//Setters
void Nodo1D::modificarCoordenadas(QList<float> l)
{
    coordenadas = l;
    x = l[0];
    y = l[1];


}

void Nodo1D::modificarCoorX(float coordX)
{
    x = coordX;
    coordenadas[0] = coordX;

}

void Nodo1D::modificarCoorY(float coordY)
{
    y = coordY;
    coordenadas[0] = coordY;

}

void Nodo1D::modificarListaAdyacentes(QList<Elemento1D> adyacente)
{

}

void Nodo1D::modificarElementoAdyacente(Elemento1D ady)
{

}






