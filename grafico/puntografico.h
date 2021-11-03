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

class PuntoGrafico : public QGraphicsObject
{
    Q_OBJECT
public:
    enum {Type = UserType + 1};
    PuntoGrafico(const QPointF& centro, const float diametro, int index, QGraphicsItem *parent = nullptr);
    void setDiametro(const float diametro);
    void escalarDiametro(const float escala);
    void virtual paint(QPainter* p, const QStyleOptionGraphicsItem* option, QWidget* w) override;
    void virtual hoverEnterEvent(QGraphicsSceneHoverEvent* event) override;
    void virtual hoverLeaveEvent(QGraphicsSceneHoverEvent* event) override;
    QVariant virtual itemChange(GraphicsItemChange change, const QVariant &value) override;
    void virtual mousePressEvent(QGraphicsSceneMouseEvent *event) override;
    void virtual mouseReleaseEvent(QGraphicsSceneMouseEvent *event) override;
    QRectF virtual boundingRect() const override;
    int type() const override {return Type;};

signals:
    void sigPosicionCambiada(int index, QPointF nuevaPos);

private:
    QPointF centroPunto;
    QRect rectContenedor;
    float diametroPunto;

    QBrush brNormal;
    QBrush brHover;
    QBrush brSelect;

    bool hovered;
    int numeroOrden;
};

#endif // PUNTOGRAFICO_H
