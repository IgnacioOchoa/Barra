#ifndef PARAMETROSGLOBALES_H
#define PARAMETROSGLOBALES_H

#include <QtCore>

enum class tipoMensaje {ERROR, REPORT};
enum class perfilVariacionArea {CONSTANTE, LINEAL, CONSTANTEPORTRAMOS, MULTIPUNTO};

struct paramGlob
{
    float longBarraInicial = 10.0;
    float area1BarraInicial = 1.0;
    float area2BarraInicial = 1.0;
    perfilVariacionArea perfilInicial = perfilVariacionArea::CONSTANTE;
    double areaMin = 0.01;
    double longMin = 0.05;

    QString gbDimensiones = "Dimensiones";
    QStringList cabecerasTablaGeometria = {"Pos", "Pos rel", "Area", "Area rel"};
    QString lbPerfilBarra = "Perfil transversal de la barra";
    QStringList geometriaPerfilBarra = {"Uniforme", "Variación lineal", "Constante por tramos", "Variación multipunto"};
    QString lbLongitudBarra = "Longitud de la barra";
    QString gbAreaTransversal = "Area transversal";
    QStringList geometriaSimetria = {"Simetrica","Unilateral"};
    QString lbAreaUnica = "Area";
    QStringList lbAreaDual = {"Area inicial","Area final"};
    QStringList cbInterpolacion = {"Lineal", "Polinomial", "Splines cúbicos"};
    QString lbInterpolacion = "Método de interpolación";
    QString lbCoord = "Posición del origen";
    QStringList cbPosCoord = {"Inicio de la barra","Centro de la barra","Final de la barra", "Otro punto"};
    QString pbAgregarLineaTabla = "Agregar fila";
    QString pbEliminarLineaTabla = "Borrar fila";
    QString chbMostrarPosRelativa = "Posición relativa";
    QString chbMostrarAreaRelativa = "Area relativa";
};

struct Limites
{
    bool limMinOn;
    bool limMaxOn;
    double limMin;
    double limMax;
    QString print() {return "Limite inf: " + QString((limMinOn ? "ON" : "OFF")) +
                ", Limite sup: " + QString(limMaxOn ? "ON" : "OFF" ) + " || "
                + QString::number(limMin) + " - " + QString::number(limMax);}
};

#endif // PARAMETROSGLOBALES_H
