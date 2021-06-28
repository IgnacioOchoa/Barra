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
  Malla1D(float longitud_barra, int cantidad_nodos);

  void crearNodo(float coor);
  void nodos_equidistantes(int cantidad_nodos, float longitud_barra);
  void info_en_consola(void);

  /*/comienzo Prueba lisa
  void probando_constructor_nodo();
  //fin prueba lisa/*/

private:
  QList<Nodo1D> lista_de_nodos;

};

#endif // MALLA_H
