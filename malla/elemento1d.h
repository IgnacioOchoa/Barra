#ifndef ELEMENTO1D_H
#define ELEMENTO1D_H

#include "nodo1d.h"
class Nodo1D;

class Elemento1D
{
public:
    Elemento1D();
    Elemento1D(Nodo1D nodo, Elemento1D elem);
    Nodo1D* getNodoSiguiente();
    Nodo1D* getNodoAnterior();
    //void crearElemento(Nodo1D nodo, Elemento1D elem);




private:
    float distanciaTramo;
    Nodo1D* nodoAnterior;
    Nodo1D* nodoSiguiente;

};

#endif // ELEMENTO1D_H
