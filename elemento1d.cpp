#include "elemento1d.h"

Elemento1D::Elemento1D()
{

}

Elemento1D::Elemento1D(QList<NodoAbstracto *> nodos) :
    ElementoAbstracto(nodos)
{

}

bool Elemento1D::setNodos(QList<NodoAbstracto *>) const
{
    return true;
}
