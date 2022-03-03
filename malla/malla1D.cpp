#include "malla1D.h"



//constructor 1. Genera una malla inicializando la lista de nodos en null
Malla1D::Malla1D(){
  listaDeNodos.clear();//iniciar lista en null
}

//Constructor 2. Inicializa la malla generando lista de nodos equidistantes
Malla1D::Malla1D(float longuitudBarra, int cantidadNodos){
  Malla1D::nodosEquidistantes(cantidadNodos, longuitudBarra);
}


//METODOS PUBLICOS

void Malla1D::crearNodo(float coor){
  //crea un nodo y lo agrega al final de la lista de nodos
  listaDeNodos.append(Nodo1D(coor, listaDeNodos.size()+1));
}


//Distribuye los nodos en la barra comenzando en la posición (0,0)
//Barra siempre sobre el eje y=0
void Malla1D::nodosEquidistantes(int cantidadNodos, float longitudBarra){
  listaDeNodos.clear();
  float tramo = longitudBarra /(cantidadNodos -1);
  for(int i = 0; i < cantidadNodos; i++){
    crearNodo(tramo*i);//se agrega a la lista desde método "crearNodo"
  }
}

//imprime la malla por consola
void Malla1D::infoEnConsola(){
  listaDeNodos.begin();
  for (int i = 0; i < listaDeNodos.size();i++){
    Nodo1D nodo = listaDeNodos[i];
    qDebug() << "id:" << nodo.obtenerID() << "  " << "Coordenadas" << nodo.obtenerCoordenadas();
  }
}

void Malla1D::agregarNodo1d(Nodo1D)
{

}

void Malla1D::eliminarNodo1d(Nodo1D)
{

}

void Malla1D::conectarNodos1d(Nodo1D, Nodo1D)
{

}

void Malla1D::conectarNodosConPeso(Nodo1D, Nodo1D, int)
{

}

void Malla1D::desconectarNodos(Nodo1D, Nodo1D)
{

}

bool Malla1D::esAdyacente(Nodo1D, Nodo1D)
{
    return true;

}

bool Malla1D::esVacio()
{
    return true;

}

Nodo1D Malla1D::obtenerNodoPorID(int)
{
    Nodo1D nod= Nodo1D(4.0,2);
    return nod;

}

int Malla1D::elementoDato(Nodo1D, Nodo1D)
{
    return 4;

}

QList<Nodo1D> Malla1D::obtenerListaDeNodos()
{
    return listaDeNodos;

}

QList<Elemento1D> Malla1D::obtenerListaDeAdyacentes(Nodo1D nod)
{
    return nod.obtenerElementosAdyacentes();

}


/*/SECCION DE PRUEBA LISA
 void Malla1D::probando_constructor_nodo(){
        QList<float> l;
        l << 3 << 5;
        Nodo1D miNodo(l, 2);
        qDebug() << "id:" << miNodo.obtenerID() << "  " <<miNodo.obtenerCoordenadas();
    }
//FIN SECCION DE PRUEBA LISA/*/


