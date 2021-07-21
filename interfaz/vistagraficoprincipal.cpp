#include "vistagraficoprincipal.h"

VistaGraficoPrincipal::VistaGraficoPrincipal(QWidget* parent) :
    QGraphicsView(parent)
{
    setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    setRenderHints(QPainter::Antialiasing | QPainter::SmoothPixmapTransform);

    factorZoom = 10;  //Cuanto mas chico puede ser la barra que el viewport = maximo zoomout
    max_Vh = -1;
    max_Vw = -1;

}

void VistaGraficoPrincipal::maximizarContenido()
{
    float escala = escalaAmpliacion();
    scale(escala, escala);
    centrarContenidos();
}

float VistaGraficoPrincipal::escalaAmpliacion()
{
    GraficoPrincipal* gp = static_cast<GraficoPrincipal*>(this->scene());
    QRectF rectItem = gp->getRectBarra();
    QRectF rectViewport = mapToScene(viewport()->rect()).boundingRect();

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

void VistaGraficoPrincipal::ajustarViewport()
{
    GraficoPrincipal* gp = dynamic_cast<GraficoPrincipal*>(this->scene());
    QRectF rectBarra = gp->getRectBarra();
    float Br = rectBarra.height()/rectBarra.width();

    QRectF rectViewport = viewport()->rect();
    float Vr = rectViewport.height()/rectViewport.width();

    if (Br > Vr)
    {
        max_Vh = rectBarra.height()*factorZoom;
        max_Vw = max_Vh/Vr;
    }
    else
    {
        max_Vw = rectBarra.width()*factorZoom;
        max_Vh = max_Vw*Vr;
    }

    QPointF topLeftCorner = {-(rectBarra.width()/2+max_Vw), -(rectBarra.height()/2+max_Vh)};
    QPointF botRightCorner = {(rectBarra.width()/2+max_Vw), (rectBarra.height()/2+max_Vh)};
    gp->setSceneRect(QRectF(topLeftCorner,botRightCorner));

    gp->addRect(gp->sceneRect(), QPen(5));

}

void VistaGraficoPrincipal::wheelEvent(QWheelEvent *event)
{
    QPointF p = event->angleDelta();
    QRectF viewportInScene = mapToScene(viewport()->rect()).boundingRect();

    maxScale = qMin(max_Vh/viewportInScene.height(), max_Vw/viewportInScene.width());

    qreal finalScale = 1+p.y()/1000.0;

    finalScale = finalScale > 1/maxScale ? finalScale : 1/maxScale;

    QPointF ptoInicioEscena = mapToScene(event->pos());

    scale(finalScale,finalScale);

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
