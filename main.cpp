#include "ventanaprincipal.h"
#include "kernel.h"

#include <QApplication>
#include <QFile>
#include <QDebug>
#include "malla1D.h"

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

    VentanaPrincipal w;
    Kernel k;
    k.setInterfaz(&w);
    w.setMinimumSize(1400,1000);

    w.show();
    return a.exec();
}
