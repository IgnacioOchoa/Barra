#ifndef NODO1D_H
#define NODO1D_H

#include "nodoabstracto.h"
#include "elemento1d.h"

class Elemento1D;

class Nodo1D : public NodoAbstracto
{
public:
    Nodo1D();
    Nodo1D(int id);
    Nodo1D(QList<float> coordenada);
    Nodo1D(float x);

    virtual QList<float> getCoordenadas() const override;
    virtual QList<ElementoAbstracto*> getElementos() const override;
    virtual void moverNodo(QList<float> deltas) override;
    virtual void reubicarNodo(QList<float> pos) override;
    virtual bool conectarElemento(ElementoAbstracto* el) override;
    virtual bool desconectarElemento(ElementoAbstracto* el) override;

    virtual ~Nodo1D() {};

private:
    QList<Elemento1D*> elementos;

};

#endif // NODO1D_H
