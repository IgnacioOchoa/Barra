#include "dialogseleccionmodelo.h"
#include "ui_dialogseleccionmodelo.h"

DialogSeleccionModelo::DialogSeleccionModelo(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::DialogSeleccionModelo),
    grupoBotonesModelos(new QButtonGroup(this))
{
    ui->setupUi(this);

    listaModelos = Modelos::getListaModelosFisicos();

    QHBoxLayout* hlayout = new QHBoxLayout;

    foreach(Modelos::ModeloFisico mdl, listaModelos)
    {
            BotonSeleccionModelo* botonModelo =
                    new BotonSeleccionModelo(mdl.imagenIcono, mdl.nombre, mdl.descripcion, this);
            hlayout->addWidget(botonModelo);
            grupoBotonesModelos->addButton(botonModelo);
    }
    connect(grupoBotonesModelos, SIGNAL(buttonToggled(QAbstractButton*,bool)),
            this, SLOT(botonSeleccionado(QAbstractButton*,bool)));
    ui->frModelos->setLayout(hlayout);
}

DialogSeleccionModelo::~DialogSeleccionModelo()
{
    delete ui;
}

void DialogSeleccionModelo::botonSeleccionado(QAbstractButton* absBut, bool checked)
{
    if(checked)
    {
        BotonSeleccionModelo* bot = qobject_cast<BotonSeleccionModelo*>(absBut);
        if(bot)
        {
            ui->teDescripcion->clear();
            ui->teDescripcion->appendPlainText(bot->getDescripcion());
        }
    }
}
