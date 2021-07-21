#include "graficoprincipal.h"

GraficoPrincipal::GraficoPrincipal(QObject *parent) :
    QGraphicsScene(parent)
{

}

void GraficoPrincipal::graficarBarra(QVector<QPointF> puntosBarra)
{
    poligonoBarra = new QPolygonF(puntosBarra);
    float dx = poligonoBarra->boundingRect().width()/2 ;
    float dy = poligonoBarra->boundingRect().height()/2 ;
    poligonoBarra->translate(-dx,dy);

    QPen p;
    QBrush br(QColor("#59d945"));
    p.setWidth(3);
    p.setCosmetic(true);

    grPolBarra = this->addPolygon(*poligonoBarra,p,br);
    rectBarra = grPolBarra->boundingRect();

    QList<PuntoGrafico*> puntosGraficos;
    foreach(QPointF pto, puntosBarra)
    {
        PuntoGrafico* ptoG = new PuntoGrafico(pto+QPointF(-dx,dy),10);
        puntosGraficos.append(ptoG);
        this->addItem(ptoG);
    }
}

QPointF GraficoPrincipal::centroEscena()
{
    return rectBarra.center();
}
