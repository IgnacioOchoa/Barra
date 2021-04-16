#ifndef MALLA_H
#define MALLA_H
#include <QList>
#include <QMultiMap>
#include "nodoabstracto.h"
#include "elementoabstracto.h"
#include "nodo1d.h"

class Malla
{

    enum tipoMalla {DIM1, DIM2, DIM3};

public:
    Malla(tipoMalla);

    bool crearMalla(tipoMalla tipo, float longitud);
    bool agregarNodo(QList<float> coord);


private:
    bool agregarNodo1D(QList<float> lista);


    QList<NodoAbstracto*> listaNodos;
    QList<ElementoAbstracto*> listaElementos;
    QMultiMap<int,NodoAbstracto*> mapaConectividad;
    tipoMalla malla;
    float longitudBarra;

};

#endif // MALLA_H
