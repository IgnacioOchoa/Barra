#include "modeloareasbarra.h"

ModeloAreasBarra::ModeloAreasBarra(QObject *parent) :
    QAbstractTableModel(parent)
{
    nroFilas = 1;
    nroColumnas = 2;

    posiciones.append(1.0);
    areas.append(1.0);
}

ModeloAreasBarra::ModeloAreasBarra(int nroFil, QObject *parent) :
    QAbstractTableModel(parent)
{
    nroColumnas = 2;
    nroFilas = nroFil;

    for (int i=0; i<nroFil; i++)
    {
        posiciones.append(1.0);
        areas.append(1.0);
    }
}

int ModeloAreasBarra::rowCount(const QModelIndex &parent) const
{
    Q_UNUSED(parent);
    return nroFilas;
}

int ModeloAreasBarra::columnCount(const QModelIndex &parent) const
{
    Q_UNUSED(parent);
    return nroColumnas;
}

QVariant ModeloAreasBarra::data(const QModelIndex &index, int role) const
{
    if (!index.isValid())
        return QVariant();

    if (index.row() >= nroFilas || index.row() < 0)
        return QVariant();

    if (role == Qt::DisplayRole) {
        switch (index.column()) {
            case 0:
                return posiciones.at(index.row());
            case 1:
                return areas.at(index.row());
            default:
                break;
        }
    }

    if (role == Qt::TextAlignmentRole)
    {
        return Qt::AlignCenter;
    }

    return QVariant();
}

bool ModeloAreasBarra::setData(const QModelIndex &index, const QVariant &value, int role)
{
    if (index.isValid() && role == Qt::EditRole) {
        switch (index.column()) {
            case 0:
                posiciones[index.row()] = value.toFloat();
                break;
            case 1:
                areas[index.row()] = value.toFloat();
                break;
            default:
                return false;
        }
        emit dataChanged(index, index, {Qt::DisplayRole, Qt::EditRole});
        return true;
    }

    return false;
}

QVariant ModeloAreasBarra::headerData(int section, Qt::Orientation orientation, int role) const
{
    if (role != Qt::DisplayRole)
        return QVariant();

    if (orientation == Qt::Horizontal) {
            switch (section) {
                case 0:
                    return "Posicion";
                case 1:
                    return "Area";
            }
        }

    return QAbstractItemModel::headerData(section, orientation, role);

}

Qt::ItemFlags ModeloAreasBarra::flags(const QModelIndex &index) const
{
    return Qt::ItemIsEditable | QAbstractTableModel::flags(index);
}

bool ModeloAreasBarra::insertRows(int position, int rows, const QModelIndex &index)
{
    return true;
}

bool ModeloAreasBarra::removeRows(int position, int rows, const QModelIndex &index)
{
    return true;
}
