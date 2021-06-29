#ifndef PUNTOGRAFICO_H
#define PUNTOGRAFICO_H

#include <QGraphicsEllipseItem>
#include <QPen>
#include <QBrush>
#include <QDebug>

class PuntoGrafico : public QGraphicsEllipseItem
{
public:
    PuntoGrafico(const QPointF& centro, const float diametro, QGraphicsItem *parent = nullptr);
    void setDiametro(const float diametro);
    void escalarDiametro(const float escala);

private:
    QPointF centroPunto;
    float diametroPunto;
};

#endif // PUNTOGRAFICO_H
