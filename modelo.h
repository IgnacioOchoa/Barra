#ifndef MODELO_H
#define MODELO_H

#include <QObject>

class Modelo : public QObject
{
    Q_OBJECT
public:
    explicit Modelo(QObject *parent = nullptr);

signals:

};

#endif // MODELO_H
