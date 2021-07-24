#include "puntografico.h"

PuntoGrafico::PuntoGrafico(const QPointF& centro, const float diametro, QGraphicsItem *parent) :
    QGraphicsItem(parent)
{

    centroPunto = centro;
    setPos(centroPunto);
    diametroPunto = diametro;
    rectContenedor = QRect(-diametro/2,-diametro/2,diametro,diametro);

    setFlag(QGraphicsItem::ItemIgnoresTransformations);
    setFlag(QGraphicsItem::ItemIsMovable);

    setAcceptHoverEvents(true);
}

void PuntoGrafico::setDiametro(const float diametro)
{
    rectContenedor = QRect(-diametro/2,-diametro/2,diametro,diametro);
}

void PuntoGrafico::escalarDiametro(const float escala)
{
    rectContenedor = QRect(-diametroPunto*escala/2,-diametroPunto*escala/2,
               diametroPunto*escala,diametroPunto*escala);
}

void PuntoGrafico::paint(QPainter *p, const QStyleOptionGraphicsItem *option, QWidget *w)
{
    QBrush br(QColor("black"));
    p->setBrush(br);
    p->drawEllipse(rectContenedor);
    p->setBrush(Qt::NoBrush);
    p->setPen(QPen(2));
    p->drawEllipse(rectContenedor.adjusted(-5,-5,5,5));
}

void PuntoGrafico::hoverMoveEvent(QGraphicsSceneHoverEvent *event)
{
    if (event->type() == QEvent::GraphicsSceneHoverEnter)
    {

    }
    else if (event->type() == QEvent::GraphicsSceneHoverLeave)
    {

    }
    else if (event->type() == QEvent::GraphicsSceneHoverMove)
    {

    }
    QGraphicsItem::hoverMoveEvent(event);
}

QRectF PuntoGrafico::boundingRect() const
{
    return QRectF(rectContenedor.adjusted(-5,-5,5,5));
}
