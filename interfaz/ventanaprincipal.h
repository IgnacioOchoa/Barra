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
#include <QGraphicsView>
#include <QMouseEvent>
#include <QHeaderView>
#include <QCheckBox>
#include <QGraphicsProxyWidget>
#include <QTableWidget>
#include <QStringList>
#include <QString>

#include "interfaz/dialogseleccionmodelo.h"
#include "fisica/modelosfisicos.h"
#include "datos/modeloareasbarra.h"
#include "grafico/puntografico.h"
#include "grafico/graficoprincipal.h"
#include "datos/parametrosglobales.h"

QT_BEGIN_NAMESPACE
namespace Ui {class ventanaPrincipal; }
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

    GraficoPrincipal* escena;

    QPushButton* pbModelo;
    QPushButton* pbDim;
    QPushButton* pbCalcular;

    QGridLayout* gdArea;

    QButtonGroup* btgSimetria;

    QLineEdit* leLongitudBarra;
    QLabel* lbLongitudBarra;

    //Areas
    QLabel* lbValorArea;
    QLineEdit* leValorArea;

    QLabel* lbValorAreaFinal;
    QLineEdit* leValorAreaFinal;

    QComboBox* cbInterpolacion;
    QLabel* lbInterpolacion;

    QCheckBox* chbMostrarPosRelativa;
    QCheckBox* chbMostrarAreaRelativa;

    // Tabla
    QVBoxLayout* vLayTabla;
    QPushButton* pbAgregarLineaTabla;
    QPushButton* pbEliminarLineaTabla;
    QTableView* tvPuntos;

    QTextEdit* teLogMensaje;

    //--- Variables del grafico ---

    QPolygonF* poligonoBarra;

    //-----------------------------

    ModeloAreasBarra* modeloAreasBarra;
    QItemSelectionModel* tvPuntosSelectionModel;

    paramGlob PG;

    void crearMenus();
    void crearFrameModelo();
    void crearIconos();
    void crearBotonesPrincipales();
    void crearFrameDimension();
    void crearPagGeometria();
    void moduloSeleccionado(bool seleccionado);
    void crearPanelMensajes();
    void crearModeloAreas();
    void crearVistaPrincipal();
    void graficarBarra();
    void borrarBarra();
    void centrarBarra();
    void rotarBarra();

public slots:
    void mensajeStatusBar(const QString& msj);
    void mensajeRecibido(const QString& msj, tipoMensaje t);

private slots:
    void lanzarVentanaModelo();
    void seleccionarDimension();
    void modeloCambiado(int nroModelo);
    void cbVariacionAreaCambiado(const QString& s);
    void longitudBarraCambiada();
    void valorAreaCambiada();

protected:
    bool eventFilter(QObject *obj, QEvent *ev) override;
    virtual void mousePressEvent(QMouseEvent *event) override;
};
#endif // MAINWINDOW_H
