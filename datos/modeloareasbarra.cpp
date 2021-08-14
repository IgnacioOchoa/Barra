#include "modeloareasbarra.h"

ModeloAreasBarra::ModeloAreasBarra(QObject *parent) :
    QAbstractTableModel(parent)
{
    nroFilas = 2;
    nroColumnas = 4;
    longitudBarra = PG.longBarraInicial;
    areaReferencia = PG.areaBarraInicial;

    datos.append(QPair<float,float>(0.0,1.0));
    datos.append(QPair<float,float>(1.0,1.0));
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
                return datos.at(index.row()).first*longitudBarra;
            case 1:
                return datos.at(index.row()).first;
            case 2:
                return datos.at(index.row()).second*areaReferencia;
            case 3:
                return datos.at(index.row()).second;
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
        if(value.toFloat()<=0) return false;
        if(yaExiste(index.row(), index.column(), value.toFloat())) return false;
        switch (index.column()) {
            case 0:
                actualizarValoresLongitud(index.row(),value.toFloat());
                break;
            case 1:
                if(value.toFloat()>1) return false;
                datos[index.row()].first = value.toFloat();
            break;
            case 2:
                datos[index.row()].second = value.toFloat()/areaReferencia;
                break;
            case 3:
                datos[index.row()].second = value.toFloat();
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
                    return PG.cabecerasTablaGeometria[0];
                case 1:
                    return PG.cabecerasTablaGeometria[1];
                case 2:
                    return PG.cabecerasTablaGeometria[2];
                case 3:
                    return PG.cabecerasTablaGeometria[3];
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
    if(index.row()==0 && (index.column()==0 || index.column()==1))
        return QAbstractTableModel::flags(index);
    return Qt::ItemIsEditable | QAbstractTableModel::flags(index);
}

bool ModeloAreasBarra::insertRows(int position, int rows, const QModelIndex &index)
{
    Q_UNUSED(index);
    Q_UNUSED(rows);
    position = nroFilas;
    beginInsertRows(QModelIndex(), position, position);
    nroFilas++;
    if(datos.size()<nroFilas)
    {
        datos.append({1.0,1.0});
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
    return datos.at(indx).first*longitudBarra;
}

float ModeloAreasBarra::getArea(int indx)
{
    if(indx >= nroFilas)
    {
        qInfo() << "ModeloAreasBarra::getArea --> indx: " << indx << " fuera de rango";
        return 0.0f;
    }
    return datos.at(indx).second*areaReferencia;
}

void ModeloAreasBarra::actualizarValoresLongitud(int row, float longitud)
{
    float valor = longitud/longitudBarra;
    datos[row].first = valor;
    bool reordenar = false;
    if(row == 0)
    {
        if(valor>datos[row+1].first) reordenar=true; //Si esto es cierto hay que reordenar
    }
    else if (row == nroFilas-1)
    {
        if(valor<datos[row-1].first) reordenar=true; //Si esto es cierto hay que reordenar
    }
    else
    {
        if(valor<datos[row-1].first || valor>datos[row+1].first) reordenar=true; //Si esto es cierto hay que reordenar
    }
    if (reordenar) //uso la funcion std::sort, se prefiere sobre qSort
    {
        std::sort(datos.begin(),datos.end(),[](QPair<float,float> p1, QPair<float,float> p2)->bool
                  {
                        if(p1.first == p2.first)
                        {
                            return p1.second < p2.second;
                        }
                        return p1.first < p2.first;
                  });
    }
    if (datos[nroFilas-1].first > 1) // Reajuste por si el maximo cambió
    {
        for(int i = 0; i<datos.size(); i++)
            datos[i].first = datos[i].first / datos[nroFilas-1].first;
        longitudBarra = longitud;
        emit nuevaLongMaxima(QString::number(longitudBarra));
    }

}

bool ModeloAreasBarra::yaExiste(int row, int column, float value)
{
    bool existe = false;
    float valorRef = value;
    float posRef;
    float areaRef;
    if (column == 0 || column == 1)
    {
        posRef = (column == 0) ? valorRef/longitudBarra : valorRef;
        areaRef = datos[row].second;
    }
    else if (column == 2 || column == 3)
    {
        areaRef = (column == 2) ? valorRef/areaReferencia : valorRef;
        posRef = datos[row].first;
    }
    QPair<float, float> p(posRef,areaRef);
    qInfo() << "Posicion a buscar = (" << p.first << ","  << p.second << ")";
    if( (std::find(datos.begin(), datos.end(), p)) != datos.end())
    {
        //qInfo() << "El valor que se quiere ingresar ya existe";
        emit logMensaje("El valor que se quiere ingresar ya existe", tipoMensaje::ERROR);
        existe = true;
    }
    return existe;
}
