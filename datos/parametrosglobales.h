#ifndef PARAMETROSGLOBALES_H
#define PARAMETROSGLOBALES_H

#include <QtCore>

enum class tipoMensaje {ERROR, REPORT};
enum class perfilVariacionArea {CONSTANTE, LINEAL, CONSTANTEPORTRAMOS, MULTIPUNTO};

struct paramGlob
{
    float longBarraInicial = 10.0;
    float areaBarraInicial = 1.0;
    float areaMin = 0.01;

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


#endif // PARAMETROSGLOBALES_H
