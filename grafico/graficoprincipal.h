#ifndef GRAFICOPRINCIPAL_H
#define GRAFICOPRINCIPAL_H

#include <QGraphicsScene>
#include "puntografico.h"
#include "parametrosglobales.h"
#include "ventanaprincipal.h"

class GraficoPrincipal : public QGraphicsScene
{
    Q_OBJECT
public:
    GraficoPrincipal(QObject *parent = nullptr);
    void graficarBarra(QVector<QPointF> verticesBarra, QVector<QPointF> puntosControl,
                       perfilVariacionArea perfil);
    QRectF getRectBarra() {return rectBarra;};
    QPointF centroEscena();

public slots:
    void actualizarPoligonoBarra(int index, QPointF pos);
    void perfilVariacionAreaCambiado(perfilVariacionArea perf);

private:
    QPolygonF* poligonoBarra;
    QGraphicsPolygonItem* grPolBarra;
    QRectF rectBarra;
    QVector<QPointF> bufferVertices;
    QVector<QPointF> bufferPtosControl;
    perfilVariacionArea perfVarArea;
};

#endif // GRAFICOPRINCIPAL_H
