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

QList<ElementoAbstracto *> Nodo1D::getElementos() const
{
    QList<ElementoAbstracto*> lista;
    foreach(Elemento1D* el, elementos) {lista.append(el);}
    return lista;
}

void Nodo1D::moverNodo(QList<float> deltas)
{

}

void Nodo1D::reubicarNodo(QList<float> pos)
{

}

bool Nodo1D::conectarElemento(ElementoAbstracto *el)
{
    Elemento1D* el1d = dynamic_cast<Elemento1D*>(el);
    if(!el1d)
    {
        //Habria que tirar un mensaje de error
        return false;
    }
    // Hacer lo que hay que hacer
    return true;
}

bool Nodo1D::desconectarElemento(ElementoAbstracto *el)
{
    Elemento1D* el1d = dynamic_cast<Elemento1D*>(el);
    if(!el1d)
    {
        //Habria que tirar un mensaje de error
        return false;
    }
    // Hacer lo que hay que hacer
    return elementos.removeOne(el1d);
}
