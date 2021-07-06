#include "vistagraficoprincipal.h"

VistaGraficoPrincipal::VistaGraficoPrincipal(QWidget* parent) :
    QGraphicsView(parent)
{
    setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
}

void VistaGraficoPrincipal::maximizarContenido()
{
    float escala = escalaAmpliacion();
    qInfo() << "Escala: " << escala;
    scale(escala, escala);
    centrarContenidos();

}

float VistaGraficoPrincipal::escalaAmpliacion()
{
    GraficoPrincipal* gp = static_cast<GraficoPrincipal*>(this->scene());
    QRectF rectItem = gp->getRectBarra();
    QRectF rectViewport = mapToScene(viewport()->rect()).boundingRect();

    qInfo() << "itemsBoundingRect: " << rectItem;
    qInfo() << "rectViewport: " << rectViewport;
    qInfo() << "sceneRect: " << gp->sceneRect();

    float cocienteX = rectViewport.width()/rectItem.width();
    float cocienteY = rectViewport.height()/rectItem.height();

    float escala = qMin(cocienteX,cocienteY);

    return escala;
}

void VistaGraficoPrincipal::centrarContenidos()
{
    GraficoPrincipal* gp = dynamic_cast<GraficoPrincipal*>(this->scene());
    this->centerOn(gp->centroEscena());
}
