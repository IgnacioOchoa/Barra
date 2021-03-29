#ifndef BOTONSELECCIONMODELO_H
#define BOTONSELECCIONMODELO_H

#include <QPushButton>

class BotonSeleccionModelo : public QPushButton
{
public:
    BotonSeleccionModelo(QWidget* parent = 0);
    BotonSeleccionModelo(const QPixmap& pxImagen, const QString& nombre,  QWidget* parent = 0);
    int heightForWidth(int w) const override {return w;}

private:
    void aplicarPropiedades();
    QPixmap pxMap;
    QIcon* icono;
};

#endif // BOTONSELECCIONMODELO_H
