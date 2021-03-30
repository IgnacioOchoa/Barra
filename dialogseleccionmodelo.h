#ifndef DIALOGSELECCIONMODELO_H
#define DIALOGSELECCIONMODELO_H

#include <QDialog>
#include <QtCore>
#include <QPushButton>
#include <QButtonGroup>
#include <QDebug>
#include "modelosfisicos.h"
#include "botonseleccionmodelo.h"

namespace Ui {
class DialogSeleccionModelo;
}

class DialogSeleccionModelo : public QDialog
{
    Q_OBJECT

public:
    explicit DialogSeleccionModelo(QWidget *parent = nullptr);
    ~DialogSeleccionModelo();

private slots:
    void botonSeleccionado(QAbstractButton* absBut, bool checked);

private:
    Ui::DialogSeleccionModelo *ui;
    QList<Modelos::ModeloFisico> listaModelos;
    QButtonGroup* grupoBotonesModelos;
};

#endif // DIALOGSELECCIONMODELO_H
