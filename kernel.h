#ifndef KERNEL_H
#define KERNEL_H

#include <QObject>
#include <QMainWindow>

class Kernel : public QObject
{
    Q_OBJECT
public:
    explicit Kernel(QObject *parent = nullptr);
    void setInterfaz(QMainWindow* ventanaPpal) {interfaz = ventanaPpal;}

signals:

private:

    QMainWindow* interfaz;

};

#endif // KERNEL_H
