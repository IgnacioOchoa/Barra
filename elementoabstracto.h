#ifndef ELEMENTOABSTRACTO_H
#define ELEMENTOABSTRACTO_H

#include <QtCore>

class NodoAbstracto;

class ElementoAbstracto
{
public:
    ElementoAbstracto();
    ElementoAbstracto(QList<NodoAbstracto*> nodos);

    virtual QList<NodoAbstracto*> getNodos() {return nodos;}
    virtual bool setNodos(QList<NodoAbstracto*>) const = 0;

private:
    QList<NodoAbstracto*> nodos;

};

#endif // ELEMENTOABSTRACTO_H
