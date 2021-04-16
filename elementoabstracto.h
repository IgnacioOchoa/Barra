#ifndef ELEMENTOABSTRACTO_H
#define ELEMENTOABSTRACTO_H

#include <QtCore>

class NodoAbstracto;

class ElementoAbstracto
{
public:

    virtual QList<NodoAbstracto*> getNodos() = 0;
    virtual bool setNodos(QList<NodoAbstracto*>) const = 0;

protected:
    QList<NodoAbstracto*> nodos;

};

#endif // ELEMENTOABSTRACTO_H
