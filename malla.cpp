#include "malla.h"

Malla::Malla(Malla::tipoMalla m)
{
    malla = m;
}

bool Malla::agregarNodo(QList<float> lista)  //Te permite agregar un nodo 1D pasando solo la coordenada x
{
    switch(malla)
    {
    case tipoMalla::DIM1:
    {
        if(lista.size()!=1) return false;
        agregarNodo1D(lista);
        break;
    }
    case tipoMalla::DIM2:
    {
        if(lista.size()!=2) return false;
        break;
    }
    case tipoMalla::DIM3:
    {
        if(lista.size()!=3) return false;
        break;
    }
    default: return false;
        break;
    }

    //hacer cosas con nodo
    return true;
}

bool Malla::agregarNodo1D(QList<float> lista)
{
        return true;
}
