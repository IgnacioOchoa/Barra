#include "malla.h"

Malla::Malla(Malla::tipoMalla m)
{
    malla = m;
}

void Malla::agregarNodo(NodoAbstracto *nodo)
{
    //Chequear antes de agregar nodo
    listaNodos.append(nodo);
}

void Malla::agregarNodo(QList<NodoAbstracto *> nodos)
{
    //Chequear antes de agregar nodos
    listaNodos.append(nodos);
}

void Malla::agregarNodo(double x)  //Te permite agregar un nodo 1D pasando solo la coordenada x
{
    if(malla!=tipoMalla::DIM1) return;  //Checkea que sea la dimension correcta

    //crear nodo y agregarlo a la lista
}

void Malla::agregarNodo(double x, double y) //Te permite agregar un nodo 2D pasando las coordenadas x,y
{
    if(malla!=tipoMalla::DIM2) return;  //Checkea que sea la dimension correcta

    //crear nodo y agregarlo a la lista
}

void Malla::agregarNodo(double x, double y, double z)   //Te permite agregar un nodo 2D pasando las coordenadas x,y,z
{
    if(malla!=tipoMalla::DIM3) return;  //Checkea que sea la dimension correcta

    //crear nodo y agregarlo a la lista
}

void Malla::agregarElemento(ElementoAbstracto *elemento)
{
    //Chequear antes de agregar elemento
    listaElementos.append(elemento);
}

void Malla::agregarElemento(QList<ElementoAbstracto *> elementos)
{
    //Chequear antes de agregar elementos
    listaElementos.append(elementos);
}
