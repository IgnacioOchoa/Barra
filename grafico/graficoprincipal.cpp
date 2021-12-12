#include "graficoprincipal.h"

GraficoPrincipal::GraficoPrincipal(QObject *parent) :
    QGraphicsScene(parent)
{
     setColorFondo(colorFondo::GEOMETRIA);
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

    int indxPtoCtrl = 0;
    foreach(QPointF pto, puntosControl)
    {
        int indxPtoVertice = verticesBarra.indexOf(pto);
        PuntoGrafico::movimiento m = PuntoGrafico::movimiento::LIBRE;
        if(indxPtoVertice == 1) m = PuntoGrafico::movimiento::VERT; //Restrinjo el movimiento si el punto esta al inicio de la barra
        PuntoGrafico* ptoG = new PuntoGrafico(pto+QPointF(-centroBarra.x(),centroBarra.y()),10, indxPtoVertice,
                                              indxPtoCtrl, m, centroBarra.y() - PG.areaMin);
        puntosGraficos.append(ptoG);
        this->addItem(ptoG);
        indxPtoCtrl++;
        connect(ptoG, &PuntoGrafico::sigPosicionCambiada, this, &GraficoPrincipal::actualizarPoligonoBarra);
        connect(ptoG, &PuntoGrafico::nuevaPosicionAceptada, this, &GraficoPrincipal::actualizarLimitesPuntos);
    }
    actualizarLimitesPuntos();
}

QPointF GraficoPrincipal::centroEscena()
{
    return rectBarra.center();
}

void GraficoPrincipal::actualizarPoligonoBarra(int nroPtoVertice, int nroPtoControl, QPointF pos)
{
    (*poligonoBarra)[nroPtoVertice] = pos;
    if(perfVarArea == perfilVariacionArea::CONSTANTE)
    {
        (*poligonoBarra)[nroPtoVertice-1].setY(pos.y());
        emit barraModificada(-pos.y()+centroBarra.y(),-pos.y()+centroBarra.y(),pos.x()+centroBarra.x());
    }

    else if(perfVarArea == perfilVariacionArea::LINEAL)
    {
        if(nroPtoVertice==1)
        {
            (*poligonoBarra)[nroPtoVertice-1].setX(pos.x());
        }
        emit barraModificada(-(*poligonoBarra)[1].y()+centroBarra.y(),
                             -(*poligonoBarra)[2].y()+centroBarra.y(),
                              (*poligonoBarra)[2].x()+centroBarra.x());
    }
    else if(perfVarArea == perfilVariacionArea::CONSTANTEPORTRAMOS)
    {
        if(nroPtoVertice!=0 && nroPtoVertice!=(poligonoBarra->length()-1))
        {
            (*poligonoBarra)[nroPtoVertice-1].setY(pos.y());
            (*poligonoBarra)[nroPtoVertice+1].setX(pos.x());
        }


        emit puntoBarraModificado(nroPtoControl, (*poligonoBarra)[nroPtoVertice].x()+centroBarra.x(),
                                         -(*poligonoBarra)[nroPtoVertice].y()+centroBarra.y());
    }
    else if(perfVarArea == perfilVariacionArea::MULTIPUNTO)
    {
        // Nada que implementar, están todos los casos cubiertos
        emit puntoBarraModificado(nroPtoControl, (*poligonoBarra)[nroPtoVertice].x()+centroBarra.x(),
                                         -(*poligonoBarra)[nroPtoVertice].y()+centroBarra.y());
    }

    if(nroPtoVertice==(poligonoBarra->length()-2)) //El ultimo punto arrastra el extremo de la barra
    {
        (*poligonoBarra)[nroPtoVertice+1].setX(pos.x());
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

void GraficoPrincipal::setColorFondo(colorFondo color)
{
    QLinearGradient* gd = new QLinearGradient();
    gd->setCoordinateMode(QGradient::ObjectMode);
    if (color == colorFondo::GEOMETRIA)
    {
        gd->setColorAt(0, "#EAECEE");
        gd->setColorAt(1, "#ABB2B9");
    }
    else if (color == colorFondo::MALLA)
    {
        gd->setColorAt(0, "#FFF7E6");
        gd->setColorAt(1, "#FFCC66");
    }
    QBrush br(*gd);
    setBackgroundBrush(br);

}
