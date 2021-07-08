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
    centroVista = gp->centroEscena();
}

void VistaGraficoPrincipal::wheelEvent(QWheelEvent *event)
{
    QPointF ptoInicioEscena = mapToScene(event->pos());

    QPoint p = event->angleDelta();
    scale(1+p.y()/1000.0,1+p.y()/1000.0);

    QPointF ptoFinalEscena = mapToScene(event->pos());

    QPointF desplazamiento = ptoInicioEscena - ptoFinalEscena;
    centroVista += desplazamiento;
    centerOn(centroVista);
}

void VistaGraficoPrincipal::mouseMoveEvent(QMouseEvent *event)
{
    if (event->buttons() == Qt::MidButton)
    {
        QPointF movimiento = mapToScene(event->pos())-inicioRueda;
        centroVista -= movimiento;
        centerOn(centroVista);
        inicioRueda = mapToScene(event->pos());
    } 
}

void VistaGraficoPrincipal::mousePressEvent(QMouseEvent *event)
{
    if (event->buttons() == Qt::MidButton)
    {
        inicioRueda = mapToScene(event->pos());
    }
    QGraphicsView::mousePressEvent(event);
}
