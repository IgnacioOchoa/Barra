#ifndef PARAMETROSGLOBALES_H
#define PARAMETROSGLOBALES_H

#include <QtCore>

struct paramGlob
{
    float longBarraInicial = 10.0;
    float areaBarraInicial = 1.0;

    QStringList cabecerasTablaGeometria = {"Pos", "Pos rel", "Area", "Area rel"};
};


#endif // PARAMETROSGLOBALES_H
