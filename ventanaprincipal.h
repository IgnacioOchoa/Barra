#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QButtonGroup>
#include <QMenu>
#include <QLabel>
#include <QFrame>
#include <QLineEdit>
#include <QTextEdit>
#include <QRadioButton>
#include <QGroupBox>
#include <QComboBox>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QGraphicsScene>
#include <QGraphicsItem>
#include <QMouseEvent>
#include <QHeaderView>
#include <QCheckBox>
#include <QGraphicsProxyWidget>
#include <QTableWidget>
#include <QStringList>
#include <QString>

#include "dialogseleccionmodelo.h"
#include "modelosfisicos.h"
#include "modeloareasbarra.h"

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

    float longitudBarra;

    QButtonGroup* grBotonesModulos;
    QGraphicsScene* escena;

    QPushButton* pbModelo;
    QPushButton* pbDim;
    QPushButton* pbCalcular;

    QGridLayout* gdArea;

    QButtonGroup* btgSimetria;

    QLineEdit* leLongitudBarra;
    QLabel* lbLongitudBarra;
    QLabel* lbValorArea;
    QLineEdit* leValorArea;

    QPushButton* pbAgregarLineaTabla;
    QPushButton* pbEliminarLineaTabla;

    QLabel* lbCol2;
    QLabel* lbCol3;
    QLabel* lbCol4;

    QLineEdit* leCol2;
    QLineEdit* leCol3;
    QLineEdit* leCol4;

    ModeloAreasBarra* modeloAreasBarra;
    QTableView* twPuntos;

    void crearMenus();
    void crearFrameModelo();
    void crearIconos();
    void crearBotonesPrincipales();
    void crearFrameDimension();
    void crearPagGeometria();
    void moduloSeleccionado(bool seleccionado);
    void crearPanelMensajes();
    void crearModeloAreas();

public slots:
    void mensajeStatusBar(const QString& msj);

private slots:
    void lanzarVentanaModelo();
    void seleccionarDimension();
    void modeloCambiado(int nroModelo);
    void cbVariacionAreaCambiado(const QString& s);
    void longitudBarraCambiada();

protected:
    bool eventFilter(QObject *obj, QEvent *ev) override;
    virtual void mousePressEvent(QMouseEvent *event) override;
};
#endif // MAINWINDOW_H
