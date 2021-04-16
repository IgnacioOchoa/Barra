#include "elemento1d.h"

Elemento1D::Elemento1D()
{

}

Elemento1D::Elemento1D(Nodo1D* nodo, Elemento1D* elem)
{
    nodoSiguiente = nodo;
    elementoSiguiente = elem;
}
