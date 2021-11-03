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
}

void GraficoPrincipal::graficarBarra(QVector<QPointF> verticesBarra, QVector<QPointF> puntosControl,
                                     perfilVariacionArea perfil)
{
    perfVarArea = perfil;
    poligonoBarra = new QPolygonF(verticesBarra);
    float dx = poligonoBarra->boundingRect().width()/2 ;
    float dy = poligonoBarra->boundingRect().height()/2 ;
    poligonoBarra->translate(-dx,dy);  //Centrar la barra

    QPen p;
    QBrush br(QColor("#59d945"));
    p.setWidth(3);
    p.setCosmetic(true);

    grPolBarra = this->addPolygon(*poligonoBarra,p,br);
    rectBarra = grPolBarra->boundingRect();

    QList<PuntoGrafico*> puntosGraficos;
    foreach(QPointF pto, puntosControl)
    {
        int indx = verticesBarra.indexOf(pto);
        PuntoGrafico* ptoG = new PuntoGrafico(pto+QPointF(-dx,dy),10, indx);
        puntosGraficos.append(ptoG);
        this->addItem(ptoG);
        connect(ptoG, &PuntoGrafico::sigPosicionCambiada, this, &GraficoPrincipal::actualizarPoligonoBarra);
    }
}

QPointF GraficoPrincipal::centroEscena()
{
    return rectBarra.center();
}

void GraficoPrincipal::actualizarPoligonoBarra(int index, QPointF pos)
{
    (*poligonoBarra)[index] = pos;
    grPolBarra->setPolygon(*poligonoBarra);

    if(perfVarArea == perfilVariacionArea::CONSTANTE)
    {
        (*poligonoBarra)[index-1].setY(pos.y());
        (*poligonoBarra)[index+1].setX(pos.x());
    }

    else if(perfVarArea == perfilVariacionArea::LINEAL)
    {
        if(index==1)
        {
            (*poligonoBarra)[index-1].setX(pos.x());
        }
        if(index==2)
        {
            (*poligonoBarra)[index+1].setX(pos.x());
        }
    }
}

void GraficoPrincipal::perfilVariacionAreaCambiado(perfilVariacionArea perf)
{
    perfVarArea = perf;
}
