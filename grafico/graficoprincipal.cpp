#include "graficoprincipal.h"

GraficoPrincipal::GraficoPrincipal(QObject *parent) :
    QGraphicsScene(parent)
{
     QLinearGradient* gd = new QLinearGradient();
     gd->setCoordinateMode(QGradient::ObjectMode);
     gd->setColorAt(0, "#EAECEE");
     gd->setColorAt(1, "#ABB2B9");

     QBrush br(*gd);
     setBackgroundBrush(br);
     //setForegroundBrush(br);
     connect(static_cast<VentanaPrincipal*>(parent), &VentanaPrincipal::sigPerfilAreaCambiado, this, &GraficoPrincipal::perfilVariacionAreaCambiado);
     connect(this, &GraficoPrincipal::barraModificada,static_cast<VentanaPrincipal*>(parent), &VentanaPrincipal::actualizarBarra);
     connect(this, &GraficoPrincipal::puntoBarraModificado, static_cast<VentanaPrincipal*>(parent), &VentanaPrincipal::actualizarPuntoBarra);
}

void GraficoPrincipal::graficarBarra(QVector<QPointF> verticesBarra, QVector<QPointF> puntosControl,
                                     perfilVariacionArea perfil)
{
    puntosGraficos.clear();
    perfVarArea = perfil;
    poligonoBarra = new QPolygonF(verticesBarra);
    centroBarra.setX(poligonoBarra->boundingRect().width()/2) ;
    centroBarra.setY(poligonoBarra->boundingRect().height()/2) ;
    poligonoBarra->translate(-centroBarra.x(),centroBarra.y());  //Centrar la barra

    QPen p;
    QBrush br(QColor("#59d945"));
    p.setWidth(3);
    p.setCosmetic(true);

    grPolBarra = this->addPolygon(*poligonoBarra,p,br);
    rectBarra = grPolBarra->boundingRect();

    foreach(QPointF pto, puntosControl)
    {
        int indx = verticesBarra.indexOf(pto);
        PuntoGrafico::movimiento m = PuntoGrafico::movimiento::LIBRE;
        if(indx == 1) m = PuntoGrafico::movimiento::VERT; //Restrinjo el movimiento si el punto esta al inicio de la barra
        PuntoGrafico* ptoG = new PuntoGrafico(pto+QPointF(-centroBarra.x(),centroBarra.y()),10, indx, m, centroBarra.y() - PG.areaMin);
        puntosGraficos.append(ptoG);
        this->addItem(ptoG);
        connect(ptoG, &PuntoGrafico::sigPosicionCambiada, this, &GraficoPrincipal::actualizarPoligonoBarra);
        connect(ptoG, &PuntoGrafico::nuevaPosicionAceptada, this, &GraficoPrincipal::actualizarLimitesPuntos);
    }
    actualizarLimitesPuntos();
}

QPointF GraficoPrincipal::centroEscena()
{
    return rectBarra.center();
}

void GraficoPrincipal::actualizarPoligonoBarra(int index, QPointF pos)
{
    (*poligonoBarra)[index] = pos;
    if(perfVarArea == perfilVariacionArea::CONSTANTE)
    {
        (*poligonoBarra)[index-1].setY(pos.y());
        emit barraModificada(-pos.y()+centroBarra.y(),-pos.y()+centroBarra.y(),pos.x()+centroBarra.x());
    }

    else if(perfVarArea == perfilVariacionArea::LINEAL)
    {
        if(index==1)
        {
            (*poligonoBarra)[index-1].setX(pos.x());
        }
        emit barraModificada(-(*poligonoBarra)[1].y()+centroBarra.y(),
                             -(*poligonoBarra)[2].y()+centroBarra.y(),
                              (*poligonoBarra)[2].x()+centroBarra.x());
    }
    else if(perfVarArea == perfilVariacionArea::CONSTANTEPORTRAMOS)
    {
        if(index!=0 && index!=(poligonoBarra->length()-1))
        {
            (*poligonoBarra)[index-1].setY(pos.y());
            (*poligonoBarra)[index+1].setX(pos.x());
        }
        emit puntoBarraModificado(index, (*poligonoBarra)[index].x()+centroBarra.x(),
                                         -(*poligonoBarra)[index].y()+centroBarra.y());
    }
    else if(perfVarArea == perfilVariacionArea::MULTIPUNTO)
    {
        // Nada que implementar, están todos los casos cubiertos
        emit puntoBarraModificado(index, (*poligonoBarra)[index].x()+centroBarra.x(),
                                         -(*poligonoBarra)[index].y()+centroBarra.y());
    }

    if(index==(poligonoBarra->length()-2)) //El ultimo punto arrastra el extremo de la barra
    {
        (*poligonoBarra)[index+1].setX(pos.x());
    }
    grPolBarra->setPolygon(*poligonoBarra);
}

void GraficoPrincipal::perfilVariacionAreaCambiado(perfilVariacionArea perf)
{
    perfVarArea = perf;
}

void GraficoPrincipal::actualizarLimitesPuntos()
{
    int i=0; //Asi uso el valor de i cuando termina el lazo
    if(puntosGraficos.length() == 1) {
        Limites limiteCorriente{true,false,-centroBarra.x()+PG.longMin,0};
        puntosGraficos[0]->setXLims(limiteCorriente);
    }
    else {
        Limites limiteCorriente{true,true,-centroBarra.x()+PG.longMin,puntosGraficos[1]->pos().x()-PG.longMin};
        puntosGraficos[0]->setXLims(limiteCorriente);
        for(i=1; i<puntosGraficos.length()-1; i++) {
            limiteCorriente = {true,true,puntosGraficos[i-1]->pos().x()+PG.longMin,puntosGraficos[i+1]->pos().x()-PG.longMin};
            puntosGraficos[i]->setXLims(limiteCorriente);
        }
        puntosGraficos.last()->setXLims({true,false,puntosGraficos[i-1]->pos().x()+PG.longMin,0});
    }
}
