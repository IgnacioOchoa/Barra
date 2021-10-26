#ifndef NODO1D_H
#define NODO1D_H
#include <QList>
#include "elemento1d.h"

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
    QList<Elemento1D> obtenerElementosAdyacentes();
    //QList<Elemento1D> obtenerAdyacentes();
    bool operator==(const Nodo1D) const;

    //Seters

    void modificarCoordenadas(QList<float> l);
    void modificarCoorX (float coordX);
    void modificarCoorY (float coordY);

    void modificarElementos();
    /*/void modificarListaAdyacentes(QList<Elemento1D> adyacente);
    void modificarElementoAdyacente(Elemento1D ady);/*/

    void modificarY(float);
    void modificarX(float);



private:

    float y;
    int ID;
    float x;
    QList<float> coordenadas;
    Elemento1D* elementoAnterior;
    Elemento1D* elementoSiguiente;
};

#endif // NODO1D_H
