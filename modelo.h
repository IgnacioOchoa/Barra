#ifndef MODELO_H
#define MODELO_H

#include <QObject>
#include "kernel.h"

class Modelo : public QObject
{
    Q_OBJECT
public:
    explicit Modelo(QObject *parent = nullptr);
    Modelo(Kernel* k, QObject *parent = nullptr);


signals:

private:
    Kernel* kern;

};

#endif // MODELO_H
