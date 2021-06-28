#include "malla1D.h"



//constructor 1. Genera una malla inicializando la lista de nodos en null
    Malla1D::Malla1D(){
        lista_de_nodos.clear();//iniciar lista en null
    }

//Constructor 2. Inicializa la malla generando lista de nodos equidistantes
    Malla1D::Malla1D(float longuitud_barra, int cantidad_nodos){
        Malla1D::nodos_equidistantes(cantidad_nodos, longuitud_barra);
    }





