#include "vistagraficoprincipal.h"

VistaGraficoPrincipal::VistaGraficoPrincipal(QWidget* parent) :
    QGraphicsView(parent)
{

}

void VistaGraficoPrincipal::maximizarContenido()
{
    GraficoPrincipal* gp = static_cast<GraficoPrincipal*>(this->scene());
    float escala = escalaAmpliacion();

    /*QList<QGraphicsItem *> gItems = gp->items();
    foreach(QGraphicsItem* itm, gItems)
    {
        PuntoGrafico* pto = dynamic_cast<PuntoGrafico*>(itm);
        if(pto)
        {
            pto->escalarDiametro(1.0/escala);
        }
    }*/

    scale(escala, escala);

}

float VistaGraficoPrincipal::escalaAmpliacion()
{
    GraficoPrincipal* gp = static_cast<GraficoPrincipal*>(this->scene());
    QRectF rectItem = gp->itemsBoundingRect();
    QRectF rectViewport = mapToScene(viewport()->rect()).boundingRect();

    qInfo() << "Rect item = " << rectItem;
    qInfo() << "Rect viewport = " << rectViewport;

    float cocienteX = rectViewport.width()/rectItem.width();
    float cocienteY = rectViewport.height()/rectItem.height();

    float escala = qMin(cocienteX,cocienteY);

    return escala;
}
