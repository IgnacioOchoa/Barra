#include "botonseleccionmodelo.h"

BotonSeleccionModelo::BotonSeleccionModelo(const QPixmap &imagen,
                                           const QString& nombre,
                                           const QString& descrip,
                                           QWidget* parent) :
    QPushButton(parent),
    des(descrip)
{
    this->setObjectName("pbModelo" + nombre);
    pxMap = imagen;
    aplicarPropiedades();
}

void BotonSeleccionModelo::aplicarPropiedades()
{
    icono = new QIcon(pxMap);
    this->setIcon(*icono);
    this->setCursor(Qt::PointingHandCursor);
    this->setCheckable(true);
    this->setIconSize(QSize(200,200));
    QSizePolicy sp(QSizePolicy::Expanding,QSizePolicy::Expanding);
    sp.setHeightForWidth(true);
    this->setSizePolicy(sp);
}

