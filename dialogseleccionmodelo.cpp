#include "dialogseleccionmodelo.h"
#include "ui_dialogseleccionmodelo.h"

DialogSeleccionModelo::DialogSeleccionModelo(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::DialogSeleccionModelo)
{
    ui->setupUi(this);

    listaModelos = Modelos::getListaModelosFisicos();

    QHBoxLayout* hlayout = new QHBoxLayout;

    foreach(Modelos::ModeloFisico mdl, listaModelos)
    {
            qInfo() << "Length lista modelos: " << listaModelos.length();
            qInfo() << "QIcon: " << mdl.imagenIcono;
            QPushButton* pb = new QPushButton(QIcon(mdl.imagenIcono), QString(),this);
            pb->setObjectName("pbModelo" + mdl.nombre);
            pb->setCheckable(true);
            pb->setCursor(Qt::PointingHandCursor);
            pb->setIconSize(QSize(100,100));
            hlayout->addWidget(pb);

    }
    ui->frModelos->setLayout(hlayout);
}

DialogSeleccionModelo::~DialogSeleccionModelo()
{
    delete ui;
}
