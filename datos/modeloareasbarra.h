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
 */


class ModeloAreasBarra : public QAbstractTableModel
{
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

    float getPosicion(int indx);
    float getArea(int indx);

    void actualizarValoresLongitud(int row, float longitud);
    //function para procesar cambios en la lista de posiciones, por ejemplo cuando se necesita
    //un reordenamiento.

public slots:
    void longitudCambiada(float nuevaLongitud);
    void areaReferenciaCambiada(float nuevaArea);

private:
    int nroColumnas;
    int nroFilas;
    float longitudBarra;
    float areaReferencia;

    paramGlob PG;

    QList<QPair<float,float>> datos;  // Lista de QPair<posicion,area>
    //QList<float> posiciones;
    //QList<float> areas;

};

#endif // MODELOAREASBARRA_H
