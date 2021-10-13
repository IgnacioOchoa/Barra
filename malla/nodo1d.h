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
    Nodo1D(float coordX, float coordY);
    Nodo1D(QList<float> coord);

    //Geters
    int obtenerID() const;
    float obtenerCoordX();
    float obtenerCoordY();
    QList<float> obtenerCoordenadas();
    QList<Elemento1D> obtenerAdyacentes();
    bool operator==(const Nodo1D) const;

    //Seters

    void modificarCoordenadas(QList<float> l);
    void modificarCoorX (float x);
    void modificarCoorY (float y);
    void modificarListaAdyacentes(QList<Elemento1D> adyacente);
    void modificarElementoAdyacente(Elemento1D ady);

    void modificarY(float);
    void modificarX(float);



private:

    float y;
    int ID;
    float x;
    QList<float> coordenadas;
    QList<Elemento1D> adyacentes;
};

#endif // NODO1D_H
