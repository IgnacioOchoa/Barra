#ifndef GRAFICOPRINCIPAL_H
#define GRAFICOPRINCIPAL_H

#include <QGraphicsScene>
#include "puntografico.h"

class GraficoPrincipal : public QGraphicsScene
{
public:
    GraficoPrincipal(QObject *parent = nullptr);
    void graficarBarra(QVector<QPointF>);
    QRectF getRectBarra() {return rectBarra;};
    QPointF centroEscena();

private:
    QPolygonF* poligonoBarra;
    QGraphicsPolygonItem* grPolBarra;
    QRectF rectBarra;
};

#endif // GRAFICOPRINCIPAL_H
