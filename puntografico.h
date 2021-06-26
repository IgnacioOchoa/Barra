#ifndef PUNTOGRAFICO_H
#define PUNTOGRAFICO_H

#include <QGraphicsEllipseItem>
#include <QPen>
#include <QBrush>

class PuntoGrafico : public QGraphicsEllipseItem
{
public:
    PuntoGrafico(const QPointF& centro, const float diametro, QGraphicsItem *parent = nullptr);
};

#endif // PUNTOGRAFICO_H
