#ifndef DIALOGSELECCIONMODELO_H
#define DIALOGSELECCIONMODELO_H

#include <QDialog>
#include <QtCore>
#include <QPushButton>
#include <QButtonGroup>
#include <QDebug>
#include "fisica/modelosfisicos.h"
#include "botonseleccionmodelo.h"

namespace Ui {
class DialogSeleccionModelo;
}

class DialogSeleccionModelo : public QDialog
{
    Q_OBJECT

public:
    explicit DialogSeleccionModelo(QWidget *parent = nullptr, int modeloActivo = -1);
    ~DialogSeleccionModelo();

private slots:
    void botonSeleccionado(QAbstractButton* absBut, bool checked);

signals:
    void sigModeloCambiado(int mod);

private:
    void modeloAceptado();
    Ui::DialogSeleccionModelo *ui;
    QList<Modelos::ModeloFisico> listaModelos;
    QButtonGroup* grupoBotonesModelos;
};

#endif // DIALOGSELECCIONMODELO_H
