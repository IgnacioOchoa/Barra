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

    brNormal = QBrush(QColor("black"));
    brHover = QBrush(QColor("#d46a13"));
    brSelect = QBrush(QColor("red"));

    hovered = false;
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
    if (!hovered)
    {
        p->setBrush(brNormal);
        p->drawEllipse(rectContenedor);
    }
    else
    {
        p->setBrush(brHover);
        p->setPen(QPen(brHover,2));
        p->drawEllipse(rectContenedor);
        p->setBrush(Qt::NoBrush);
        p->drawEllipse(rectContenedor.adjusted(-5,-5,5,5));
    }
}

void PuntoGrafico::hoverEnterEvent(QGraphicsSceneHoverEvent *event)
{
    if (event->type() == QEvent::GraphicsSceneHoverEnter)
    {
        hovered = true;
    }
    QGraphicsItem::hoverEnterEvent(event);
}

void PuntoGrafico::hoverLeaveEvent(QGraphicsSceneHoverEvent *event)
{
    if (event->type() == QEvent::GraphicsSceneHoverLeave)
    {
        hovered = false;
    }
    QGraphicsItem::hoverLeaveEvent(event);
}

QRectF PuntoGrafico::boundingRect() const
{
    return QRectF(rectContenedor.adjusted(-5,-5,5,5));
}
