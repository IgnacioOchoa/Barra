#ifndef NODO1D_H
#define NODO1D_H
#include <QList>
#include "elemento1d.h"
#include <QList>

class Elemento1D;

class Nodo1D
{
public:

    Nodo1D(float coord, int id);
    Nodo1D(QList<float> coord, int id);

    int obtener_id();
    float obtener_coord_x();
    float obtener_coord_y();
    QList<float> obtener_coordenadas();

private:

    float y;
    int ID;
    float x;
    QList<float> coordenadas;
};

#endif // NODO1D_H
