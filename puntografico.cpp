#include "puntografico.h"

PuntoGrafico::PuntoGrafico(const QPointF& centro, const float diametro, QGraphicsItem *parent) :
    QGraphicsEllipseItem(parent)
{
    QRect rect(centro.x()-diametro/2,centro.y()-diametro/2,diametro,diametro);
    setRect(rect);
    QBrush br(QColor("black"));
    setBrush(br);
}
