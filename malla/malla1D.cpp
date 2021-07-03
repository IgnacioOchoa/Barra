#include "malla1D.h"



//constructor 1. Genera una malla inicializando la lista de nodos en null
Malla1D::Malla1D(){
  lista_de_nodos.clear();//iniciar lista en null
}

//Constructor 2. Inicializa la malla generando lista de nodos equidistantes
Malla1D::Malla1D(float longuitud_barra, int cantidad_nodos){
  Malla1D::nodos_equidistantes(cantidad_nodos, longuitud_barra);
}

//Métodos públicos

void Malla1D::crearNodo(float coor){
  //crea un nodo y lo agrega al final de la lista de nodos
  lista_de_nodos.append(Nodo1D(coor, lista_de_nodos.size()+1));
}
//Distribuye los nodos en la barra comenzando en la posición (0,0)
//Barra siempre sobre el eje y=0
void Malla1D::nodos_equidistantes(int cantidad_nodos, float longitud_barra){
  lista_de_nodos.clear();
  float tramo = longitud_barra /(cantidad_nodos -1);
  for(int i = 0; i < cantidad_nodos; i++){
    crearNodo(tramo*i);//se agrega a la lista desde método "crearNodo"
  }
}

//imprime la malla por consola
void Malla1D::info_en_consola(){
  lista_de_nodos.begin();
  for (int i = 0; i < lista_de_nodos.size();i++){
    Nodo1D nodo = lista_de_nodos[i];
    qDebug() << "id:" << nodo.obtener_id() << "  " << "Coordenadas" << nodo.obtener_coordenadas();
    }
}

/*/SECCION DE PRUEBA LISA
 void Malla1D::probando_constructor_nodo(){
        QList<float> l;
        l << 3 << 5;
        Nodo1D mi_nodo(l, 2);
        qDebug() << "id:" << mi_nodo.obtener_id() << "  " <<mi_nodo.obtener_coordenadas();
    }
//FIN SECCION DE PRUEBA LISA/*/


