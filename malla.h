#ifndef MALLA_H
#define MALLA_H
#include <QList>
#include <QMultiMap>
#include "nodoabstracto.h"
#include "elementoabstracto.h"

class Malla
{

    enum tipoMalla {DIM1, DIM2, DIM3};

public:
    Malla(tipoMalla);

    void agregarNodo(NodoAbstracto* nodo);
    void agregarNodo(QList<NodoAbstracto*> nodos);
    void agregarNodo(double x);
    void agregarNodo(double x, double y);
    void agregarNodo(double x, double y, double z);
    void agregarElemento(ElementoAbstracto* elemento);
    void agregarElemento(QList<ElementoAbstracto*> elementos);

private:
    QList<NodoAbstracto*> listaNodos;
    QList<ElementoAbstracto*> listaElementos;
    QMultiMap<int,NodoAbstracto*> mapaConectividad;
    tipoMalla malla;

};

#endif // MALLA_H
