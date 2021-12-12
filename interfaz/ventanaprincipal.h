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

#include "kernel/kernel.h"
#include "interfaz/dialogseleccionmodelo.h"
#include "fisica/modelosfisicos.h"
#include "datos/modeloareasbarra.h"
#include "grafico/puntografico.h"
#include "grafico/graficoprincipal.h"
#include "datos/parametrosglobales.h"

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
    void graficarBarra();
    void actualizarDibujoBarra();

signals:
    void sigValorArea1Cambiado(double area);
    void sigValorArea2Cambiado(double area);
    void sigLongitudBarraCambiado(double area);
    void sigPerfilAreaCambiado (perfilVariacionArea perfil);
    void sigPuntoCambiado(int pto, double pos, double area);

public slots:
    void mensajeStatusBar(const QString& msj);
    void actualizarBarra(double area1, double area2, double longitud);
    void actualizarPuntoBarra(int pto, double pos, double area);

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
    QLabel* lbValorArea1;
    QLineEdit* leValorArea1;
    QLabel* lbValorArea2;
    QLineEdit* leValorArea2;
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

    //--- Flags utiles ---
    bool barraYaGraficada;

    void crearMenus();
    void crearFrameModelo();
    void crearIconos();
    void crearBotonesPrincipales();
    void crearFrameDimension();
    void crearPagGeometria();
    void moduloSeleccionado(bool seleccionado);
    void crearPanelMensajes();
    void crearVistaPrincipal();
    void borrarBarra();
    void centrarBarra();
    void rotarBarra();

};
#endif // MAINWINDOW_H
