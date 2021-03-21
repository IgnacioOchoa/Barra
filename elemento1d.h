#ifndef ELEMENTO1D_H
#define ELEMENTO1D_H

#include "elementoabstracto.h"

class Elemento1D : public ElementoAbstracto
{
public:
    Elemento1D();
    Elemento1D(QList<NodoAbstracto*> nodos);

    virtual bool setNodos(QList<NodoAbstracto*>) const override;
};

#endif // ELEMENTO1D_H
