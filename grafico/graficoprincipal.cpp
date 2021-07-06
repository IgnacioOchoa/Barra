#include "graficoprincipal.h"

GraficoPrincipal::GraficoPrincipal(QObject *parent) :
    QGraphicsScene(parent)
{

}

void GraficoPrincipal::graficarBarra(QVector<QPointF> puntosBarra)
{
    poligonoBarra = new QPolygonF(puntosBarra);

    QPen p;
    QBrush br(QColor("#59d945"));
    p.setWidth(3);
    p.setCosmetic(true);

    grPolBarra = this->addPolygon(*poligonoBarra,p,br);
    rectBarra = grPolBarra->boundingRect();

    QList<PuntoGrafico*> puntosGraficos;
    foreach(QPointF pto, puntosBarra)
    {
        PuntoGrafico* ptoG = new PuntoGrafico(pto,10);
        puntosGraficos.append(ptoG);
        this->addItem(ptoG);
    }
}

QPointF GraficoPrincipal::centroEscena()
{
    return rectBarra.center();
}
