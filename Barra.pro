QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++11

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

INCLUDEPATH += C:\Users\Ignacio\Proyectos\Barra\datos \
               C:\Users\Ignacio\Proyectos\Barra\fisica \
               C:\Users\Ignacio\Proyectos\Barra\grafico \
               C:\Users\Ignacio\Proyectos\Barra\interfaz \
               C:\Users\Ignacio\Proyectos\Barra\kernel \
               C:\Users\Ignacio\Proyectos\Barra\malla \
               C:\Users\Ignacio\Proyectos\Barra\solver

DEPENDPATH += C:\Users\Ignacio\Proyectos\Barra\datos

SOURCES += \
    datos/modeloareasbarra.cpp \
    fisica/modelo.cpp \
    fisica/modelosfisicos.cpp \
    grafico/graficoprincipal.cpp \
    grafico/puntografico.cpp \
    interfaz/botonseleccionmodelo.cpp \
    interfaz/dialogseleccionmodelo.cpp \
    interfaz/ventanaprincipal.cpp \
    interfaz/vistagraficoprincipal.cpp \
    kernel/kernel.cpp \
    main.cpp \
    malla/elemento1d.cpp \
    malla/malla1D.cpp \
    malla/nodo1d.cpp \
    solver/solver.cpp

HEADERS += \
    datos/modeloareasbarra.h \
    datos/parametrosglobales.h \
    fisica/modelo.h \
    fisica/modelosfisicos.h \
    grafico/graficoprincipal.h \
    grafico/puntografico.h \
    interfaz/botonseleccionmodelo.h \
    interfaz/dialogseleccionmodelo.h \
    interfaz/ventanaprincipal.h \
    interfaz/vistagraficoprincipal.h \
    kernel/kernel.h \
    malla/elemento1d.h \
    malla/malla1D.h \
    malla/nodo1d.h \
    solver/solver.h

FORMS += \
    interfaz/dialogseleccionmodelo.ui \
    interfaz/ventanaprincipal.ui

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

RESOURCES += \
    Recursos.qrc
