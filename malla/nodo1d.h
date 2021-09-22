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

    int obtenerID();
    float obtenerCoordX();
    float obtenerCoordY();
    QList<float> obtenerCoordenadas();

    void modificarY(float);
    void modificarX(float);
    void modificarCoordenadas(QList<float>);



private:

    float y;
    int ID;
    float x;
    QList<float> coordenadas;
};

#endif // NODO1D_H
