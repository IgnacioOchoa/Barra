#include "elementoabstracto.h"

ElementoAbstracto::ElementoAbstracto()
{

}

ElementoAbstracto::ElementoAbstracto(QList<NodoAbstracto *> nodos)
{
    this->nodos = nodos;
}
