#ifndef NODO1D_H
#define NODO1D_H

#include "nodoabstracto.h"

class Nodo1D : public NodoAbstracto
{
public:
    Nodo1D();
    Nodo1D(int id);
    Nodo1D(QList<float> coordenada);
    Nodo1D(float x);

    virtual QList<float> getCoordenadas() const override;
    virtual QList<ElementoAbstracto*> getElementosConectados() const override;
    virtual void moverNodo(QList<float> deltas) override;
    virtual void reubicarNodo(QList<float> pos) override;
    virtual void conectarElemento(ElementoAbstracto* el) override;
    virtual void desconectarElemento(ElementoAbstracto* el) override;

    virtual ~Nodo1D() {};
};

#endif // NODO1D_H
