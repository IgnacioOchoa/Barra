#ifndef VISTAGRAFICOPRINCIPAL_H
#define VISTAGRAFICOPRINCIPAL_H

#include <QGraphicsView>
#include "grafico/graficoprincipal.h"
#include "grafico/puntografico.h"
#include <QDebug>
#include <QScrollBar>
#include <QWheelEvent>

class VistaGraficoPrincipal : public QGraphicsView
{
public:
    VistaGraficoPrincipal(QWidget* parent = nullptr);

    void maximizarContenido();
    float escalaAmpliacion();
    void centrarContenidos();


    virtual void wheelEvent(QWheelEvent *event) override;
    virtual void mouseMoveEvent(QMouseEvent *event) override;
    virtual void mousePressEvent(QMouseEvent *event) override;

private:
    QPointF inicioRueda;
    QPointF centroVista;

};

#endif // VISTAGRAFICOPRINCIPAL_H
