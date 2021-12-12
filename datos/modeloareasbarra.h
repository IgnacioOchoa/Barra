#ifndef MODELOAREASBARRA_H
#define MODELOAREASBARRA_H

#include <QObject>
#include <QDebug>
#include <QAbstractTableModel>
#include "parametrosglobales.h"

/*       MODELO AREAS BARRA
 *
 *   COL1   |   COL2   |    COL3    |   COL4   |   COL5   |
 * ------------------------------------------------------
 * nro pto  |  pos abs |   por rel  | area abs | area real
 *  (int)   |  (float) |   (float)  |  (float) |  (float)
 *
 * Nro punto: empieza en 1 y se usa para numerar los puntos donde se definiran las secciones
 * Pos absoluta: posicion absoulta en metros respecto al punto 1 del punto en cuestion
 * Area absoluta: magnitud del area, en metros cuadrados en el punto en cuestion
 *
 * La informacion se guarda en una lista de QPoint<double,double>, donde el primer elemento
 * es la posicion absoulta y el segundo elemento es el area relativa. Para obtener el area
 * absoluta hay que multiplicarla por el area de referencia
 *
 *
 */


class ModeloAreasBarra : public QAbstractTableModel
{
    Q_OBJECT

public:
    ModeloAreasBarra(QObject *parent = nullptr);

    int rowCount(const QModelIndex &parent = QModelIndex()) const override;
    int columnCount(const QModelIndex &parent = QModelIndex()) const override;

    QVariant data(const QModelIndex &index, int role = Qt::DisplayRole) const override;
    bool setData(const QModelIndex &index, const QVariant &value, int role = Qt::EditRole) override;
    QVariant headerData(int section, Qt::Orientation orientation, int role) const override;

    Qt::ItemFlags flags(const QModelIndex &index) const override;

    bool insertRows(int position, int rows, const QModelIndex &index = QModelIndex()) override;
    bool removeRows(int position, int rows, const QModelIndex &index = QModelIndex()) override;

    int getNroEntradas() {return datos.size();}
    int getNroFilas() {return nroFilas;}

    double getPosicion(int indx);
    double getArea(int indx);
    void setPosicion(int indx, double pos);
    void setArea(int indx, double area);

    void setPerfil(perfilVariacionArea p);

public slots:
    void longitudCambiada(double nuevaLongitud);
    void areaReferenciaCambiada(double nuevaArea);

signals:
    void logMensaje(QString mensaje, tipoMensaje t);
    void filaCambiada(QModelIndex);
    void barraModificada();

private:

    const int MIN_ROWS = 3;
    perfilVariacionArea perfilModelo;
    int nroColumnas;
    int nroFilas;
    float longitudBarra;
    float areaReferencia;

    paramGlob PG;

    QList<QPair<double,double>> datos;  // Lista de QPair<posicion,area>

    void actualizarValoresLongitud(int row, double longitud);
    //function para procesar cambios en la lista de posiciones, por ejemplo cuando se necesita
    //un reordenamiento.
    bool puntoYaExiste(QPair<double, double>);
    bool posicionYaExiste(float pos);
    int calcularNroDecimales(double nro) const;
    QPair<double, double> puntoEditado(int row, int column, float value);
};

#endif // MODELOAREASBARRA_H
