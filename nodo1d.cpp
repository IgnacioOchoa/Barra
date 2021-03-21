#include "nodo1d.h"

Nodo1D::Nodo1D() :
   NodoAbstracto()
{

}

Nodo1D::Nodo1D(int id) :
   NodoAbstracto(id)
{

}

Nodo1D::Nodo1D(QList<float> coordenada) :
   NodoAbstracto(coordenada)
{

}

Nodo1D::Nodo1D(float x)
{

}

QList<float> Nodo1D::getCoordenadas() const
{
    return QList<float>();
}

QList<ElementoAbstracto *> Nodo1D::getElementosConectados() const
{
    return QList<ElementoAbstracto*>();
}

void Nodo1D::moverNodo(QList<float> deltas)
{

}

void Nodo1D::reubicarNodo(QList<float> pos)
{

}

void Nodo1D::conectarElemento(ElementoAbstracto *el)
{

}

void Nodo1D::desconectarElemento(ElementoAbstracto *el)
{

}
