#ifndef NODO1D_H
#define NODO1D_H
#include <QList>
#include "elemento1d.h"

class Elemento1D;

class Nodo1D
{
public:
    Nodo1D(QList<float> coord, int id);

private:

    QList<float> coordenadas;
    int ID;

    void crearNodo(QList<float> coord, int id);

};

#endif // NODO1D_H
