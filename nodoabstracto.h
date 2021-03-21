#ifndef NODOABSTRACTO_H
#define NODOABSTRACTO_H

#include<QtCore>

class ElementoAbstracto;

class NodoAbstracto
{
public:
    NodoAbstracto();
    NodoAbstracto(int id);
    NodoAbstracto(QList<float> coordenadas);
    int getId() const {return id;}
    virtual QList<float> getCoordenadas() const = 0;
    virtual QList<ElementoAbstracto*> getElementosConectados() const = 0;
    virtual void moverNodo(QList<float> deltas) = 0;
    virtual void reubicarNodo(QList<float> pos) = 0;
    virtual void conectarElemento(ElementoAbstracto* el) = 0;
    virtual void desconectarElemento(ElementoAbstracto* el) = 0;

    virtual ~NodoAbstracto() {};

protected:
    bool existeId(int id);

private:
    int id;
    struct valor;
    QList<float> coordenadas;
    QList<ElementoAbstracto*> elementosConectados;
};

#endif // NODOABSTRACTO_H
