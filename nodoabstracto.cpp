#include "nodoabstracto.h"

NodoAbstracto::NodoAbstracto()
{

}

NodoAbstracto::NodoAbstracto(int id)
{
    //chequear si el id ya existe
    if (existeId(id))
    {
        this->id = id;
    }
}

NodoAbstracto::NodoAbstracto(QList<float> coordenadas)
{
    //chequear que las coordenadas esten bien
    this->coordenadas = coordenadas;
}

bool NodoAbstracto::existeId(int id)
{
    return true;
}
