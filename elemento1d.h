#ifndef ELEMENTO1D_H
#define ELEMENTO1D_H

#include "elementoabstracto.h"
#include "nodo1d.h"

class Elemento1D : public ElementoAbstracto
{
public:
    Elemento1D();
    Elemento1D(Nodo1D* nodo, Elemento1D* elem);

private:
    Nodo1D* nodoSiguiente;
    Elemento1D* elementoSiguiente;
};

#endif // ELEMENTO1D_H
