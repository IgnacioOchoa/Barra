#include "elemento1d.h"

Elemento1D::Elemento1D(){}

Elemento1D::Elemento1D (Nodo1D nodo, Elemento1D elem){
     crearElemento(nodo, elem);
    //revisar esto
}

Nodo1D* Elemento1D::getNodoSiguiente(){
    return nodoSiguiente;
}

Elemento1D* Elemento1D::getElementoSiguiente(){
    return elementoSiguiente;
}

void Elemento1D::crearElemento(Nodo1D nodo, Elemento1D elem){
    nodoSiguiente = &nodo;
    elementoSiguiente = &elem;


}

