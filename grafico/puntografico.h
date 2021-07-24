#ifndef PUNTOGRAFICO_H
#define PUNTOGRAFICO_H

#include <QGraphicsEllipseItem>
#include <QGraphicsScene>
#include <QPen>
#include <QBrush>
#include <QDebug>
#include <QGraphicsSceneHoverEvent>
#include <QPainter>
#include <QtCore>

class PuntoGrafico : public QGraphicsItem
{
public:
    enum {Type = UserType + 1};
    PuntoGrafico(const QPointF& centro, const float diametro, QGraphicsItem *parent = nullptr);
    void setDiametro(const float diametro);
    void escalarDiametro(const float escala);
    void virtual paint(QPainter* p, const QStyleOptionGraphicsItem* option, QWidget* w) override;
    void virtual hoverMoveEvent(QGraphicsSceneHoverEvent* event) override;
    QRectF virtual boundingRect() const override;
    int type() const override {return Type;};

private:
    QPointF centroPunto;
    QRect rectContenedor;
    float diametroPunto;
};

#endif // PUNTOGRAFICO_H
