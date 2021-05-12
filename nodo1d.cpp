#include "nodo1d.h"


Nodo1D::Nodo1D()
{

}

Nodo1D::Nodo1D(int id)
{

}

Nodo1D::Nodo1D(QList<float> coordenada)
{

}

Nodo1D::Nodo1D(float x)
{

}

QList<float> getCoordenadas(){}

void setCoordenadas(QList<float> coord){
    QList<float>::iterator i;
    for (i = coord.begin(); i != coord.end(); ++i)
          qDebug() << *i;

}
QList<Elemento1D> Nodo1D::getElementos(){
    return elementos;
}

bool esElemento(Nodo1D nodo){
    bool res = false;
   // Nodo1D nodoAdy = QList::begin();
    //while ((!nodo == nodoAdy) && ()){
    //if (nodo == nodoAdy){
    //    res = true;}
    return res;
    }

Elemento1D Nodo1D::obtenerElemento(){
    return Elemento1D();
}

/*/
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
/*/
