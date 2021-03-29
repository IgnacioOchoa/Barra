#include "botonseleccionmodelo.h"

BotonSeleccionModelo::BotonSeleccionModelo(QWidget* parent) :
    QPushButton(parent)
{
    aplicarPropiedades();
}

BotonSeleccionModelo::BotonSeleccionModelo(const QPixmap &imagen, const QString& nombre, QWidget* parent) :
    QPushButton(parent)

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

