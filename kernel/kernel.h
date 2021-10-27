#ifndef KERNEL_H
#define KERNEL_H

#include "datos/modeloareasbarra.h"
#include "datos/parametrosglobales.h"
#include "interfaz/ventanaprincipal.h"
#include <QObject>
#include <QMainWindow>
#include <QTableView>

class VentanaPrincipal;

class Kernel : public QObject
{
    Q_OBJECT

public:
    explicit Kernel(QObject *parent = nullptr);
    void setInterfaz(VentanaPrincipal* ventanaPpal);
    ModeloAreasBarra* getModeloAreas() const;
    void conectarTVAreas(QTableView* tv) const;
    void modificarNroLineasModAreas(int c) const;
    void calcularPuntosBarra(QVector<QPointF>& vertices, QVector<QPointF>& ptosControl) const;

public slots:
    void mensajeRecibido(QString mensaje, tipoMensaje tipo);
    void setTipoVariacionArea(perfilVariacionArea tipo);
    void setValorArea1(float area);
    void setValorArea2(float area);
    void setLongitudBarra(float longitud);
    void setPerfilArea(perfilVariacionArea perfil);

private:

    VentanaPrincipal* interfaz;
    ModeloAreasBarra* modeloAreasBarra;
    QItemSelectionModel* tvPuntosSelectionModel;
    paramGlob PG;

    float area1;
    float area2;
    float longitudBarra;
    perfilVariacionArea tipoVariacionAreaActivo;
};

#endif // KERNEL_H
