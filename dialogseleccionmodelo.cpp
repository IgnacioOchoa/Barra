#include "dialogseleccionmodelo.h"
#include "ui_dialogseleccionmodelo.h"

DialogSeleccionModelo::DialogSeleccionModelo(QWidget *parent, int modeloActivo) :
    QDialog(parent),
    ui(new Ui::DialogSeleccionModelo),
    grupoBotonesModelos(new QButtonGroup(this))
{
    ui->setupUi(this);
    this->setModal(true);
    listaModelos = Modelos::getListaModelosFisicos();

    QHBoxLayout* hlayout = new QHBoxLayout;
    int id = 1;

    foreach(Modelos::ModeloFisico mdl, listaModelos)
    {
            BotonSeleccionModelo* botonModelo =
                    new BotonSeleccionModelo(mdl.imagenIcono, mdl.nombre, mdl.descripcion, this);
            hlayout->addWidget(botonModelo);
            grupoBotonesModelos->addButton(botonModelo);
            grupoBotonesModelos->setId(botonModelo, id++);
    }

    connect(grupoBotonesModelos, SIGNAL(buttonToggled(QAbstractButton*,bool)),
            this, SLOT(botonSeleccionado(QAbstractButton*,bool)));
    ui->frModelos->setLayout(hlayout);

    connect(ui->pbCancelar, &QAbstractButton::clicked, this, &QDialog::close);

    //Este connect usa una funcion lambda para emitir una señal y cerrar el dialogo
    connect(ui->pbSeleccionar, &QAbstractButton::clicked,
            [this](){emit sigModeloCambiado(grupoBotonesModelos->checkedId());
                     this->close();});

    //Si al dialogo le pasaron algo distinto a -1 es que ya habia algun modelo activo, si
    // es -1 selecciono el primer item por default para tener siempre algo seleccionado
    if (modeloActivo==-1)
    {
        grupoBotonesModelos->button(1)->setChecked(true);
    }
    else
    {
        grupoBotonesModelos->button(modeloActivo)->setChecked(true);
    }
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
