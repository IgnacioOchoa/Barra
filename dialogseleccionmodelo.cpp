#include "dialogseleccionmodelo.h"
#include "ui_dialogseleccionmodelo.h"

DialogSeleccionModelo::DialogSeleccionModelo(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::DialogSeleccionModelo)
{
    ui->setupUi(this);

    listaModelos = Modelos::getListaModelosFisicos();

    QHBoxLayout* hlayout = new QHBoxLayout;
    QButtonGroup* grupoBotonesModelos = new QButtonGroup(this);

    foreach(Modelos::ModeloFisico mdl, listaModelos)
    {
            BotonSeleccionModelo* botonModelo = new BotonSeleccionModelo(mdl.imagenIcono, mdl.nombre,this);
            hlayout->addWidget(botonModelo);
            grupoBotonesModelos->addButton(botonModelo);
    }
    ui->frModelos->setLayout(hlayout);
}

DialogSeleccionModelo::~DialogSeleccionModelo()
{
    delete ui;
}
