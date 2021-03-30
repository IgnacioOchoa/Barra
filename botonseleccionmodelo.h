#ifndef BOTONSELECCIONMODELO_H
#define BOTONSELECCIONMODELO_H

#include <QPushButton>

class BotonSeleccionModelo : public QPushButton
{
    Q_OBJECT

public:
    BotonSeleccionModelo(const QPixmap& pxImagen,
                         const QString& nombre,
                         const QString& descrip,
                         QWidget* parent = 0);
    int heightForWidth(int w) const override {return w;}
    const QString& getDescripcion() {return des;}

private:
    void aplicarPropiedades();
    QString des;
    QPixmap pxMap;
    QIcon* icono;
};

#endif // BOTONSELECCIONMODELO_H
