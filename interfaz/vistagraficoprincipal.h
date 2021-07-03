#ifndef VISTAGRAFICOPRINCIPAL_H
#define VISTAGRAFICOPRINCIPAL_H

#include <QGraphicsView>
#include "grafico/graficoprincipal.h"
#include "grafico/puntografico.h"
#include <QDebug>

class VistaGraficoPrincipal : public QGraphicsView
{
public:
    VistaGraficoPrincipal(QWidget* parent = nullptr);

    void maximizarContenido();
    float escalaAmpliacion();
};

#endif // VISTAGRAFICOPRINCIPAL_H
