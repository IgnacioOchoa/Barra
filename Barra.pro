QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++11

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    botonseleccionmodelo.cpp \
    dialogseleccionmodelo.cpp \
    elemento1d.cpp \
    kernel.cpp \
    main.cpp \
    modelo.cpp \
    modeloareasbarra.cpp \
    modelosfisicos.cpp \
    nodo1d.cpp \
    solver.cpp \
    ventanaprincipal.cpp \
    malla1D.cpp

HEADERS += \
    botonseleccionmodelo.h \
    dialogseleccionmodelo.h \
    elemento1d.h \
    kernel.h \
    modelo.h \
    modeloareasbarra.h \
    modelosfisicos.h \
    nodo1d.h \
    solver.h \
    ventanaprincipal.h \
    malla1D.h

FORMS += \
    dialogseleccionmodelo.ui \
    ventanaprincipal.ui

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

RESOURCES += \
    Recursos.qrc
