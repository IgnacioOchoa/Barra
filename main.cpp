#include "interfaz/ventanaprincipal.h"
#include "kernel/kernel.h"

#include <QApplication>
#include <QFile>
#include <QDebug>
#include "malla/malla1D.h"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    QFont fnt= QApplication::font();
    fnt.setPointSize(10);
    a.setFont(fnt);

    QFile file(":/stylesheets/stylesheetGeneral.qss");
        if(file.open(QFile::ReadOnly)) {
           QString StyleSheet = QLatin1String(file.readAll());
           a.setStyleSheet(StyleSheet);
        }

    Kernel* k = new Kernel();
    VentanaPrincipal w(k);
    k->setInterfaz(&w);
    w.setMinimumSize(1400,1000);

    /*/COMIENZO SECCION DE PRUEBA LISA
       qDebug() << 5;
       Malla1D mi_malla;
       mi_malla.nodos_equidistantes(4, 22.00);
       mi_malla.info_en_consola();
       mi_malla.probando_constructor_nodo();
    //FIN SECCION DE PRUEBA LISA/*/

    w.show();
    return a.exec();
}
