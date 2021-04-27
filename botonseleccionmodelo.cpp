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
    qInfo() << "Object name: " << this->objectName();
}

void BotonSeleccionModelo::aplicarPropiedades()
{
    icono = new QIcon(pxMap);
    this->setIcon(*icono);
    this->setCursor(Qt::PointingHandCursor);
    this->setCheckable(true);
    this->setIconSize(QSize(200,200));
    QSizePolicy sp(QSizePolicy::Fixed,QSizePolicy::Fixed);
    //QSizePolicy sp = this->sizePolicy();
    sp.setHeightForWidth(true);
    this->setSizePolicy(sp);
    //this->setStyleSheet("QPushButton {background-color:red; margin = 22px;padding : 6px}");
}

