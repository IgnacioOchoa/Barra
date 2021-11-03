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

#include "kernel.h"
#include "dialogseleccionmodelo.h"
#include "modelosfisicos.h"
#include "modeloareasbarra.h"
#include "puntografico.h"
#include "graficoprincipal.h"
#include "parametrosglobales.h"

QT_BEGIN_NAMESPACE
namespace Ui {class ventanaPrincipal; }
QT_END_NAMESPACE

class Kernel;
class GraficoPrincipal;

class VentanaPrincipal : public QMainWindow
{
    Q_OBJECT

public:
    VentanaPrincipal(Kernel* k, QWidget *parent = nullptr);
    ~VentanaPrincipal();

    void printMensaje(const QString& msj, tipoMensaje t);
    void enviarParametrosActuales();

signals:

    void sigValorArea1Cambiado(float area);
    void sigValorArea2Cambiado(float area);
    void sigLongitudBarraCambiado(float area);
    void sigPerfilAreaCambiado (perfilVariacionArea perfil);

private:
    Ui::ventanaPrincipal *ui;
    const Kernel* ker;

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

    //Perfil barra
    QComboBox* cbTipoBarra;

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
    paramGlob PG;

    void crearMenus();
    void crearFrameModelo();
    void crearIconos();
    void crearBotonesPrincipales();
    void crearFrameDimension();
    void crearPagGeometria();
    void moduloSeleccionado(bool seleccionado);
    void crearPanelMensajes();
    void crearVistaPrincipal();
    void graficarBarra();
    void borrarBarra();
    void centrarBarra();
    void rotarBarra();

public slots:
    void mensajeStatusBar(const QString& msj);

private slots:
    void lanzarVentanaModelo();
    void seleccionarDimension();
    void modeloCambiado(int nroModelo);
    void cbVariacionAreaCambiado(const QString& s);
    void longitudBarraCambiada();
    void valorAreaCambiado();
    void valorAreaFinalCambiado();

protected:
    bool eventFilter(QObject *obj, QEvent *ev) override;
    virtual void mousePressEvent(QMouseEvent *event) override;
};
#endif // MAINWINDOW_H
