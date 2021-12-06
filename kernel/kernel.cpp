#include "kernel.h"

Kernel::Kernel(QObject *parent) : QObject(parent)
{
    modeloAreasBarra = new ModeloAreasBarra(this);

    connect(modeloAreasBarra, &ModeloAreasBarra::logMensaje, this, &Kernel::mensajeRecibido);
}

void Kernel::setInterfaz(VentanaPrincipal *ventanaPpal)
{
    interfaz = ventanaPpal;
    connect(interfaz, &VentanaPrincipal::sigPerfilAreaCambiado, this, &Kernel::setTipoVariacionArea);
    connect(interfaz, &VentanaPrincipal::sigValorArea1Cambiado, this, &Kernel::setValorArea1);
    connect(interfaz, &VentanaPrincipal::sigValorArea2Cambiado, this, &Kernel::setValorArea2);
    connect(interfaz, &VentanaPrincipal::sigLongitudBarraCambiado, this, &Kernel::setLongitudBarra);
    connect(interfaz, &VentanaPrincipal::sigPuntoCambiado, this, &Kernel::modificarPuntoBarra);
    ventanaPpal->enviarParametrosActuales();
}

ModeloAreasBarra *Kernel::getModeloAreas() const
{
    return modeloAreasBarra;
}

void Kernel::conectarTVAreas(QTableView *tv) const
{
    tv->setModel(modeloAreasBarra);
    connect(modeloAreasBarra, &ModeloAreasBarra::filaCambiada,
            [tv](QModelIndex m){tv->selectionModel()->select(m,QItemSelectionModel::ClearAndSelect);});
}

void Kernel::modificarNroLineasModAreas(int c) const
{
    // c es el numero de lineas que se quiere agregar (c positivo) o quitar (c negativo)
    if (c>0)
    {
        for(int i=0; i<c; i++)
        {
            modeloAreasBarra->insertRows(0,0);
        }
    }
    else if (c<0)
    {
        for(int i=0; i<-c; i++)
        {
            modeloAreasBarra->removeRows(0,0);
        }
    }
}

void Kernel::calcularPuntosBarra(QVector<QPointF>& vertices, QVector<QPointF>& ptosControl) const
{
    if (tipoVariacionAreaActivo == perfilVariacionArea::CONSTANTE) // Uniforme
    {
        vertices.append(QPointF(0,0));
        vertices.append(QPointF(0,-area1));
        vertices.append(QPointF(longitudBarra,-area1));
        ptosControl.append(vertices.last());
        vertices.append(QPointF(longitudBarra,0));
    }
    else if (tipoVariacionAreaActivo == perfilVariacionArea::LINEAL) // Variacion lineal
    {
        vertices.append(QPointF(0,0));
        vertices.append(QPointF(0,-area1));
        ptosControl.append(vertices.last());
        vertices.append(QPointF(longitudBarra,-area2));
        ptosControl.append(vertices.last());
        vertices.append(QPointF(longitudBarra,0));
    }
    else if (tipoVariacionAreaActivo == perfilVariacionArea::CONSTANTEPORTRAMOS) // Constante por tramos
    {
        vertices.append(QPointF(modeloAreasBarra->getPosicion(0),0.0));
        for(int i=0; i<modeloAreasBarra->getNroFilas()-1; i++)
        {
            QPointF p(modeloAreasBarra->getPosicion(i), -modeloAreasBarra->getArea(i));
            QPointF p2(modeloAreasBarra->getPosicion(i+1), -modeloAreasBarra->getArea(i));
            vertices.append(p);
            ptosControl.append(p2);
            vertices.append(p2);
        }
        vertices.append(QPointF(modeloAreasBarra->getPosicion(modeloAreasBarra->getNroFilas()-1),0.0));
    }
    else if (tipoVariacionAreaActivo == perfilVariacionArea::MULTIPUNTO) // Variacion multipunto
    {
        vertices.append(QPointF(modeloAreasBarra->getPosicion(0),0.0));
        for(int i=0; i<modeloAreasBarra->getNroFilas(); i++)
        {
            QPointF p(modeloAreasBarra->getPosicion(i), -modeloAreasBarra->getArea(i));
            vertices.append(p);
            ptosControl.append(p);
        }
        vertices.append(QPointF(modeloAreasBarra->getPosicion(modeloAreasBarra->getNroFilas()-1),0.0));
    }
}

perfilVariacionArea Kernel::getPerfilVariacionArea() const
{
    return tipoVariacionAreaActivo;
}

void Kernel::setTipoVariacionArea(perfilVariacionArea tipo)
{
    tipoVariacionAreaActivo = tipo;
}

void Kernel::setValorArea1(float area)
{
    modeloAreasBarra->areaReferenciaCambiada(area);
    area1 = area;
}

void Kernel::setValorArea2(float area)
{
    area2 = area;
}

void Kernel::setLongitudBarra(float longitud)
{
    modeloAreasBarra->longitudCambiada(longitud);
    longitudBarra = longitud;
}

void Kernel::setPerfilArea(perfilVariacionArea perfil)
{
    modeloAreasBarra->setPerfil(perfil);
}

void Kernel::modificarPuntoBarra(int pto, double pos, double area)
{
    modeloAreasBarra->setData(modeloAreasBarra->index(pto,0), pos);
    modeloAreasBarra->setData(modeloAreasBarra->index(pto,2), area);
}

void Kernel::mensajeRecibido(QString mensaje, tipoMensaje tipo)
{
    interfaz->printMensaje(mensaje, tipo);
}
