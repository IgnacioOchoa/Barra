#ifndef VISTAGRAFICOPRINCIPAL_H
#define VISTAGRAFICOPRINCIPAL_H

#include <QGraphicsView>
#include "graficoprincipal.h"
#include "puntografico.h"
#include <QDebug>
#include <QtGlobal>
#include <QScrollBar>
#include <QWheelEvent>

class VistaGraficoPrincipal : public QGraphicsView
{
public:
    VistaGraficoPrincipal(QWidget* parent = nullptr);

    void maximizarContenido();
    float escalaAmpliacion();
    void centrarContenidos();
    void ajustarViewport();


    virtual void wheelEvent(QWheelEvent *event) override;
    virtual void mouseMoveEvent(QMouseEvent *event) override;
    virtual void mousePressEvent(QMouseEvent *event) override;

private:
    QPointF inicioRueda;
    QPointF centroVista;
    int factorZoom;

    float max_Vh;  //Altura maxima del viewport, en coordenadas de la escena!!
    float max_Vw;  //Ancho maximo del viewport, en coordenadas de la escena!!
    qreal maxScale;

};

#endif // VISTAGRAFICOPRINCIPAL_H
