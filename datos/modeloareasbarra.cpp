#include "modeloareasbarra.h"

ModeloAreasBarra::ModeloAreasBarra(QObject *parent) :
    QAbstractTableModel(parent)
{
    nroFilas = MIN_ROWS;
    nroColumnas = 4;
    longitudBarra = PG.longBarraInicial;
    areaReferencia = PG.areaBarraInicial;

    datos.append(QPair<float,float>(0.0,1.0));
    datos.append(QPair<float,float>(longitudBarra/2,1.0));
    datos.append(QPair<float,float>(longitudBarra,1.0));

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
                return datos.at(index.row()).first;
            case 1:
                return datos.at(index.row()).first/longitudBarra;
            case 2:
                if (perfilModelo == perfilVariacionArea::CONSTANTE && (index.row()==nroFilas-1)) return "-";
                return datos.at(index.row()).second*areaReferencia;
            case 3:
                if (perfilModelo == perfilVariacionArea::CONSTANTE && (index.row()==nroFilas-1)) return "-";
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

bool ModeloAreasBarra::setData(const QModelIndex &mIndex, const QVariant &value, int role)
{
    if (mIndex.isValid() && role == Qt::EditRole) {
        if(value.toFloat()<=0) return false;
        QPair<float,float> p = puntoEditado(mIndex.row(), mIndex.column(), value.toFloat());
        switch (mIndex.column()) {
            case 0:
                if(posicionYaExiste(value.toFloat())) return false;
                actualizarValoresLongitud(mIndex.row(),value.toFloat());
                break;
            case 1:
                if(posicionYaExiste(value.toFloat()*longitudBarra)) return false;
                actualizarValoresLongitud(mIndex.row(),value.toFloat()*longitudBarra);
                break;
            case 2:
                datos[mIndex.row()].second = value.toFloat()/areaReferencia;
                break;
            case 3:
                datos[mIndex.row()].second = value.toFloat();
                break;
            default:
                return false;
        }
        emit dataChanged(mIndex, mIndex, {Qt::DisplayRole, Qt::EditRole});
        if (datos.indexOf(p) != mIndex.row()) // Significa que esa linea se cambio de lugar
        {
            emit filaCambiada(index(datos.indexOf(p),mIndex.column()));
        }
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
    if(index.row()==0 && (index.column()==0 || index.column()==1)) //No se puede editar la posicion 0
        return QAbstractTableModel::flags(index);
    else if (perfilModelo == perfilVariacionArea::CONSTANTE &&
             (index.row() == nroFilas-1) &&
             ((index.column() == nroColumnas-1) || index.column() == nroColumnas-2))
    {
        return QAbstractTableModel::flags(index);
    }

    return Qt::ItemIsEditable | QAbstractTableModel::flags(index);
}

bool ModeloAreasBarra::insertRows(int position, int rows, const QModelIndex &index)
{
    Q_UNUSED(index);
    Q_UNUSED(rows);
    position = nroFilas;
    beginInsertRows(QModelIndex(), position, position);
    nroFilas++;
    datos.append({longitudBarra+1,1.0});
    longitudCambiada(longitudBarra+1);
    endInsertRows();
    return true;
}

bool ModeloAreasBarra::removeRows(int position, int rows, const QModelIndex &index)
{
    Q_UNUSED(index);
    Q_UNUSED(rows);
    if (nroFilas <= MIN_ROWS) return false;
    position = nroFilas-1;
    beginRemoveRows(QModelIndex(), position, position);
    nroFilas--;
    datos.removeLast();
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
    return datos.at(indx).first;
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

void ModeloAreasBarra::setPerfil(perfilVariacionArea p)
{
    perfilModelo = p;
    emit dataChanged(QAbstractItemModel::createIndex(nroFilas-1,0),
                     QAbstractItemModel::createIndex(nroFilas-1,nroColumnas-1));
}

void ModeloAreasBarra::actualizarValoresLongitud(int row, float posRelativa)
{
    datos[row].first = posRelativa;
    bool reordenar = false;
    if(row == 0)
    {
        if(posRelativa>datos[row+1].first) reordenar=true; //Si esto es cierto hay que reordenar
    }
    else if (row == nroFilas-1)
    {
        if(posRelativa<datos[row-1].first) reordenar=true; //Si esto es cierto hay que reordenar
    }
    else
    {
        if(posRelativa<datos[row-1].first || posRelativa>datos[row+1].first) reordenar=true; //Si esto es cierto hay que reordenar
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

    longitudCambiada(datos[nroFilas-1].first);
}

bool ModeloAreasBarra::puntoYaExiste(QPair<float, float> p)
{
    if( (std::find(datos.begin(), datos.end(), p)) != datos.end())
    {
        emit logMensaje("El valor que se quiere ingresar ya existe", tipoMensaje::ERROR);
        return true;
    }
    return false;
}

bool ModeloAreasBarra::posicionYaExiste(float pos)
{
    for (int i=0; i<datos.length(); i++)
    {
        if(datos[i].first == pos)
        {
            emit logMensaje("Pos = " + QString::number(pos) + " : La posición que se quiere ingresar ya existe", tipoMensaje::ERROR);
            return true;
        }
    }
    return false;
}

QPair<float, float> ModeloAreasBarra::puntoEditado(int row, int column, float value)
{
    float valorRef = value;
    float posRef;
    float areaRef;
    if (column == 0 || column == 1)
    {
        posRef = (column == 0) ? valorRef : valorRef/longitudBarra;
        areaRef = datos[row].second;
    }
    else if (column == 2 || column == 3)
    {
        areaRef = (column == 2) ? valorRef/areaReferencia : valorRef;
        posRef = datos[row].first;
    }
    QPair<float, float> p(posRef,areaRef);
    return p;
}
