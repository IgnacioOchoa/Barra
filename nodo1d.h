#ifndef NODO1D_H
#define NODO1D_H
#include <QList>
#include "elemento1d.h"
#include <QList>

class Elemento1D;

class Nodo1D
{
public:

    //*Nuevo: (1 renglón)
    Nodo1D(float coord, int id);
    Nodo1D(QList<float> coord, int id);


    int obtener_id();
    float obtener_coord_x();
    QList<float> obtener_coordenadas();


private:

    //*Nuevo: (1 r)
    float y;
    int ID;
    float x;
    QList<float> coordenadas;




};

#endif // NODO1D_H
