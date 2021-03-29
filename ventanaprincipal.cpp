#include "ventanaprincipal.h"
#include "ui_ventanaprincipal.h"

VentanaPrincipal::VentanaPrincipal(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::ventanaPrincipal)
{
    ui->setupUi(this);

    crearMenus();
    crearFrameModelo();

    escena = new QGraphicsScene(this);
    ui->vistaGeometria->setScene(escena);

    grBotonesModulos = new QButtonGroup;

    QList<QPushButton*> listaBotones = {ui->pbGeometria, ui->pbMalla, ui->pbFisica, ui->pbCondBorde,
                                       ui->pbSalida, ui->pbSimulacion};

    for(int i=0; i < listaBotones.length(); i++)
    {
        grBotonesModulos->addButton(listaBotones[i],i);
        listaBotones[i]->setCheckable(true);
        connect(listaBotones[i], &QAbstractButton::clicked, this, &VentanaPrincipal::moduloSeleccionado);
    }

    grBotonesModulos->setExclusive(true);
    listaBotones[0]->setChecked(true);

    ui->textEdit->setText("Aca van a aparecer mensajes copados");

}

VentanaPrincipal::~VentanaPrincipal()
{
    delete ui;
}

void VentanaPrincipal::crearMenus()
{
    menuArchivo = menuBar()->addMenu("Archivo");
    menuProyecto = menuBar()->addMenu("Proyecto");
    menuOpciones = menuBar()->addMenu("Opciones");
    menuAjustes = menuBar()->addMenu("Ajustes");
    menuAyuda = menuBar()->addMenu("Ayuda");
}

void VentanaPrincipal::crearFrameModelo()
{
     QLabel* modelo = new QLabel("Transferencia térmica", this);
     QLabel* estado = new QLabel("Estado estacionario", this);
     QLabel* incognita = new QLabel("Incógnita: temperatura", this);

     QVBoxLayout* labelLayout = new QVBoxLayout;
     labelLayout->addWidget(modelo);
     labelLayout->addWidget(estado);
     labelLayout->addWidget(incognita);

     QHBoxLayout* modelLayout = new QHBoxLayout;

     QPixmap pixmapProblemaFisico(":/imagenesIconos/Imagenes/iconoProblemaTermico.png");
     QIcon iconoModelo(pixmapProblemaFisico);
     QPushButton* pbModelo = new QPushButton(iconoModelo, QString(), this);
     pbModelo->setIconSize(QSize(100,100));
     pbModelo->setCursor(Qt::PointingHandCursor);
     pbModelo->setObjectName("pbModelo");

     QLabel* imageLabel = new QLabel;
     imageLabel->setPixmap(pixmapProblemaFisico);

     modelLayout->addWidget(pbModelo);
     modelLayout->addItem(labelLayout);

     ui->frameModelo->setLayout(modelLayout);
     connect(pbModelo, &QAbstractButton::clicked, this, &VentanaPrincipal::lanzarVentanaModelo);

}

void VentanaPrincipal::moduloSeleccionado(bool seleccionado)
{
    if(seleccionado) ui->stackedWidget->setCurrentIndex(grBotonesModulos->checkedId());
}

void VentanaPrincipal::lanzarVentanaModelo()
{
    DialogSeleccionModelo* dlg = new DialogSeleccionModelo();

    dlg->show();

}
