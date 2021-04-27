#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QButtonGroup>
#include <QMenu>
#include <QFrame>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QGraphicsScene>
#include <QGraphicsItem>
#include <QMouseEvent>
#include <QCheckBox>

#include "dialogseleccionmodelo.h"
#include "modelosfisicos.h"

QT_BEGIN_NAMESPACE
namespace Ui { class ventanaPrincipal; }
QT_END_NAMESPACE

class VentanaPrincipal : public QMainWindow
{
    Q_OBJECT

public:
    VentanaPrincipal(QWidget *parent = nullptr);
    ~VentanaPrincipal();

private:
    Ui::ventanaPrincipal *ui;
    QMenu* menuArchivo;
    QMenu* menuProyecto;
    QMenu* menuOpciones;
    QMenu* menuAjustes;
    QMenu* menuAyuda;

    QIcon* iconoDim1D;
    QIcon* iconoDim2D;
    QIcon* iconoDim3D;

    QFrame* frDimension;

    int modeloElegido;

    QButtonGroup* grBotonesModulos;
    QGraphicsScene* escena;

    QPushButton* pbModelo;

    void crearMenus();
    void crearFrameModelo();
    void crearIconos();
    void crearBotonesPrincipales();
    void crearFrameDimension();
    void moduloSeleccionado(bool seleccionado);

private slots:
    void lanzarVentanaModelo();
    void seleccionarDimension();
    void modeloCambiado(int nroModelo);

protected:
    bool eventFilter(QObject *obj, QEvent *ev) override;
    virtual void mousePressEvent(QMouseEvent *event) override;
};
#endif // MAINWINDOW_H
