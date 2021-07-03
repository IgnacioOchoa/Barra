#include "puntografico.h"

PuntoGrafico::PuntoGrafico(const QPointF& centro, const float diametro, QGraphicsItem *parent) :
    QGraphicsEllipseItem(parent)
{
    centroPunto = centro;
    setPos(centroPunto);
    diametroPunto = diametro;
    QRect rect(-diametro/2,-diametro/2,diametro,diametro);
    setRect(rect);
    QBrush br(QColor("black"));
    setBrush(br);
    setFlag(QGraphicsItem::ItemIgnoresTransformations);
}

void PuntoGrafico::setDiametro(const float diametro)
{
    QRect rect(-diametro/2,-diametro/2,diametro,diametro);
    setRect(rect);
}

void PuntoGrafico::escalarDiametro(const float escala)
{
    QRect rect(-diametroPunto*escala/2,-diametroPunto*escala/2,
               diametroPunto*escala,diametroPunto*escala);
    setRect(rect);
}
