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

  void agregarNodo1d(Nodo1D);
  void eliminarNodo1d(Nodo1D);
  void conectarNodos1d(Nodo1D, Nodo1D);
  void conectarNodosConPeso(Nodo1D, Nodo1D, int);
  void desconectarNodos(Nodo1D, Nodo1D);
  bool esAdyacente(Nodo1D, Nodo1D);
  bool esVacio();
  Nodo1D obtenerNodoPorID(int);
  int elementoDato(Nodo1D, Nodo1D);
  QList<Nodo1D> obtenerListaDeNodos();
  QList<Elemento1D> obtenerListaDeAdyacentes(Nodo1D);


  /*/comienzo Prueba lisa
  void probandoConstructorNodo();
  //fin prueba lisa/*/

private:
  QList<Nodo1D> listaDeNodos;

};

#endif // MALLA_H
