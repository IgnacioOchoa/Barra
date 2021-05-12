#ifndef ELEMENTO1D_H
#define ELEMENTO1D_H

#include "nodo1d.h"
class Nodo1D;

class Elemento1D
{
public:
    Elemento1D();
   // Elemento1D(Nodo1D* nodo, Elemento1D* elem);
    Nodo1D* nodoApuntado();
private:
    Nodo1D* nodoSiguiente;
    Elemento1D* elementoSiguiente;
};

#endif // ELEMENTO1D_H
