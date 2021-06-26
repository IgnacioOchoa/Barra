#include "modeloareasbarra.h"

ModeloAreasBarra::ModeloAreasBarra(float longitud, QObject *parent) :
    QAbstractTableModel(parent)
{
    nroFilas = 2;
    nroColumnas = 4;
    longitudBarra = longitud;
    areaReferencia = 1;

    posiciones << 0.0 << 1.0;
    areas << 1.0 << 1.0;
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
                return posiciones.at(index.row())*longitudBarra;
            case 1:
                return posiciones.at(index.row());
            case 2:
                return areas.at(index.row())*areaReferencia;
            case 3:
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
                posiciones[index.row()] = value.toFloat()/longitudBarra;
                break;
            case 1:
                if(value.toFloat()>1) return false;
                posiciones[index.row()] = value.toFloat();
            break;
            case 2:
                areas[index.row()] = value.toFloat()/areaReferencia;
                break;
            case 3:
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
                    return "Pos";
                case 1:
                    return "Pos rel";
                case 2:
                    return "Area";
                case 3:
                    return "Area rel";
            }
        }

    return QAbstractItemModel::headerData(section, orientation, role);

}

void ModeloAreasBarra::longitudCambiada(float nuevaLongitud)
{
    longitudBarra = nuevaLongitud;
    emit dataChanged(QAbstractItemModel::createIndex(0,0),QAbstractItemModel::createIndex(nroFilas-1,1));
    return;
}

void ModeloAreasBarra::areaReferenciaCambiada(float nuevaArea)
{
    areaReferencia = nuevaArea;
    emit dataChanged(QAbstractItemModel::createIndex(0,2),QAbstractItemModel::createIndex(nroFilas-1,3));
    return;
}

Qt::ItemFlags ModeloAreasBarra::flags(const QModelIndex &index) const
{
    return Qt::ItemIsEditable | QAbstractTableModel::flags(index);
}

bool ModeloAreasBarra::insertRows(int position, int rows, const QModelIndex &index)
{
    Q_UNUSED(index);
    Q_UNUSED(rows);
    position = nroFilas;
    beginInsertRows(QModelIndex(), position, position);
    nroFilas++;
    if(posiciones.size()<nroFilas)
    {
        posiciones.append(1);
        areas.append(1);
    }
    endInsertRows();
    return true;
}

bool ModeloAreasBarra::removeRows(int position, int rows, const QModelIndex &index)
{
    Q_UNUSED(index);
    Q_UNUSED(rows);
    if (nroFilas <= 2) return false;
    position = nroFilas-1;
    beginRemoveRows(QModelIndex(), position, position);
    nroFilas--;
    endRemoveRows();
    return true;
}

float ModeloAreasBarra::getPosicion(int indx)
{
    if(indx >= nroFilas)
    {
        qInfo() << "ModeloAreasBarra::getPosicion --> indx: " << indx << " fuera de rango";
        return 0.0f;
    }
    return posiciones.at(indx)*longitudBarra;
}

float ModeloAreasBarra::getArea(int indx)
{
    if(indx >= nroFilas)
    {
        qInfo() << "ModeloAreasBarra::getArea --> indx: " << indx << " fuera de rango";
        return 0.0f;
    }
    return areas.at(indx)*areaReferencia;
}
