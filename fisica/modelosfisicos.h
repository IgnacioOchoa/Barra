#ifndef MODELOSFISICOS_H
#define MODELOSFISICOS_H

#include <QtCore>
#include <QPixmap>

QT_BEGIN_NAMESPACE
namespace Modelos  {
    struct ModeloFisico {
        QString nombre;
        QString descripcion;
        QPixmap imagenIcono;
    };

QList<Modelos::ModeloFisico> getListaModelosFisicos();

}
QT_END_NAMESPACE

#endif // MODELOSFISICOS_H


