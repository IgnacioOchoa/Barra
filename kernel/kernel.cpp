#include "kernel.h"

Kernel::Kernel(QObject *parent) : QObject(parent)
{

}

void Kernel::setInterfaz(QMainWindow *ventanaPpal)
{
    interfaz = ventanaPpal;
}


