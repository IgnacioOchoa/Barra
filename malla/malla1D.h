#ifndef MALLA_H
#define MALLA_H
#include <QList>
#include <QMultiMap>
#include "malla/nodo1d.h"
#include "malla/elemento1d.h"
#include <QDebug>

class Malla1D
{

public:
  Malla1D();
  Malla1D(float longitudBarra, int cantidadNodos);

  void crearNodo(float coor);
  void nodosEquidistantes(int cantidadNodos, float longitudBarra);
  void infoEnConsola(void);

  /*/comienzo Prueba lisa
  void probandoConstructorNodo();
  //fin prueba lisa/*/

private:
  QList<Nodo1D> listaDeNodos;

};

#endif // MALLA_H
