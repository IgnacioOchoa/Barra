#include "modelo.h"

Modelo::Modelo(QObject *parent) : QObject(parent)
{

}

Modelo::Modelo(Kernel *k, QObject *parent) :
    QObject(parent),
    kern(k)
{

}
