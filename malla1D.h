#ifndef MALLA_H
#define MALLA_H
#include <QList>
#include <QMultiMap>
#include "nodo1d.h"
#include "elemento1d.h"
#include <QDebug>

class Malla1D
{

public:
    Malla1D();
    Malla1D(float long_barra, int cant_nodos);

    void crearNodo(float coor);
    void nodos_equidistantes(int cant_nodos, float long_barra);
    void imprimir_en_consola(void);
    void probando_constructor_nodo();

    void infoMalla();

private:
    QList<Nodo1D> lista_de_nodos;



};

#endif // MALLA_H
