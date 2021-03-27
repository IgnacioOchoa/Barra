#include "modelosfisicos.h"

QList<Modelos::ModeloFisico> Modelos::getListaModelosFisicos()
{
    Modelos::ModeloFisico mfTermico = {
        "Termico",
        "Modelo que representa problemas de transferencia térmica",
        QPixmap(":/imagenesIconos/Imagenes/iconoProblemaTermico.png")
    };

    Modelos::ModeloFisico mfElectrico = {
        "Electrico",
        "Modelo que representa problemas de potencial y corriente eléctrica",
        QPixmap(":/imagenesIconos/Imagenes/iconoProblemaElectrico.png")
    };

    Modelos::ModeloFisico mfEstructural = {
        "Estructural",
        "Modelo que representa problemas de tensiones y deformaciones en sólidos",
        QPixmap(":/imagenesIconos/Imagenes/iconoProblemaEstructural.png")
    };

    return QList<Modelos::ModeloFisico>{
                mfTermico,
                mfElectrico,
                mfEstructural
           };
}
