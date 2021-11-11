#include "puntografico.h"

PuntoGrafico::PuntoGrafico(const QPointF& centro, const float diametro, int index,
                           movimiento mov, float ylim, QGraphicsItem *parent) :
    QGraphicsObject(parent),
    centroPunto(centro),
    diametroPunto(diametro),
    numeroOrden(index),
    yLim(ylim),
    movim(mov)
{
    setPos(centroPunto);
    rectContenedor = QRect(-diametro/2,-diametro/2,diametro,diametro);

    setFlag(QGraphicsItem::ItemIgnoresTransformations);
    setFlag(QGraphicsItem::ItemIsMovable);
    setFlag(QGraphicsItem::ItemSendsGeometryChanges);

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

QVariant PuntoGrafico::itemChange(QGraphicsItem::GraphicsItemChange change, const QVariant &value)
{
    if (change == ItemPositionChange && scene()) {
        // Avisar al kernel que el punto ha sido movido
        QPointF nuevaPos = value.toPointF();
        if (movim == movimiento::VERT) {
            nuevaPos.setX(pos().x());
        }
        if (nuevaPos.y()>yLim)
        {
            nuevaPos.setY(yLim);
        }
        emit sigPosicionCambiada(numeroOrden, nuevaPos);
        return nuevaPos;
    }
    return QGraphicsItem::itemChange(change, value);
}

void PuntoGrafico::mousePressEvent(QGraphicsSceneMouseEvent *event)
{

    QGraphicsItem::mousePressEvent(event);
}

void PuntoGrafico::mouseReleaseEvent(QGraphicsSceneMouseEvent *event)
{
    QGraphicsItem::mouseReleaseEvent(event);
}

QRectF PuntoGrafico::boundingRect() const
{
    return QRectF(rectContenedor.adjusted(-5,-5,5,5));
}
