#ifndef VISTAGRAFICOPRINCIPAL_H
#define VISTAGRAFICOPRINCIPAL_H

#include <QGraphicsView>
#include "graficoprincipal.h"
#include "puntografico.h"
#include <QDebug>

class VistaGraficoPrincipal : public QGraphicsView
{
public:
    VistaGraficoPrincipal(QWidget* parent = nullptr);

    void maximizarContenido();
    float escalaAmpliacion();
};

#endif // VISTAGRAFICOPRINCIPAL_H
