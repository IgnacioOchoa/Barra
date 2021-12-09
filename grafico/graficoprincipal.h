#ifndef GRAFICOPRINCIPAL_H
#define GRAFICOPRINCIPAL_H

#include <QGraphicsScene>
#include "grafico/puntografico.h"
#include "datos/parametrosglobales.h"
#include "interfaz/ventanaprincipal.h"

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
    void actualizarPoligonoBarra(int nroPtoVertice, int nroPtoControl, QPointF pos);
    void perfilVariacionAreaCambiado(perfilVariacionArea perf);
    void actualizarLimitesPuntos();

signals:
    void barraModificada(double area1, double area2, double longitud);
    void puntoBarraModificado(int pto, double pos, double area);

private:
    QPointF centroBarra; //Localizacion de la barra que va a estar en el (0,0) del grafico
    QPolygonF* poligonoBarra;
    QGraphicsPolygonItem* grPolBarra;
    QRectF rectBarra;
    QVector<QPointF> bufferVertices;
    QList<PuntoGrafico*> puntosGraficos;
    perfilVariacionArea perfVarArea;
    paramGlob PG;
};

#endif // GRAFICOPRINCIPAL_H
