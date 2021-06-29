#include "vistagraficoprincipal.h"

VistaGraficoPrincipal::VistaGraficoPrincipal(QWidget* parent) :
    QGraphicsView(parent)
{

}

void VistaGraficoPrincipal::maximizarContenido()
{
    float escala = escalaAmpliacion();
    scale(escala, escala);

}

float VistaGraficoPrincipal::escalaAmpliacion()
{
    GraficoPrincipal* gp = static_cast<GraficoPrincipal*>(this->scene());
    QRectF rectItem = gp->itemsBoundingRect();
    QRectF rectViewport = mapToScene(viewport()->rect()).boundingRect();

    float cocienteX = rectViewport.width()/rectItem.width();
    float cocienteY = rectViewport.height()/rectItem.height();

    float escala = qMin(cocienteX,cocienteY)*0.9;

    return escala;
}
