#include "ventanaprincipal.h"
#include "ui_ventanaprincipal.h"

VentanaPrincipal::VentanaPrincipal(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::ventanaPrincipal)
{
    ui->setupUi(this);

    crearMenus();
    crearFrameModelo();
    crearIconos();
    crearFrameDimension();

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

     QPixmap pixmap1D(":/imagenesIconos/Imagenes/icono1D.png");
     QIcon icono1D(pixmap1D);
     QPushButton* pbDim = new QPushButton(pixmap1D, QString(), this);
     pbDim->setIconSize(QSize(200,100));
     pbDim->setCursor(Qt::PointingHandCursor);
     pbDim->setObjectName("pbDim");
     pbDim->setSizePolicy(QSizePolicy::Fixed, QSizePolicy::Fixed);

     modelLayout->addWidget(pbDim);

     QPixmap pixmapProblemaFisico(":/imagenesIconos/Imagenes/iconoProblemaTermico.png");
     QIcon iconoModelo(pixmapProblemaFisico);
     QPushButton* pbModelo = new QPushButton(iconoModelo, QString(), this);
     pbModelo->setIconSize(QSize(100,100));
     pbModelo->setCursor(Qt::PointingHandCursor);
     pbModelo->setObjectName("pbModelo");
     pbModelo->setSizePolicy(QSizePolicy::Fixed, QSizePolicy::Fixed);

     modelLayout->addWidget(pbModelo);
     modelLayout->addItem(labelLayout);

     ui->frameModelo->setLayout(modelLayout);
     connect(pbModelo, &QAbstractButton::clicked, this, &VentanaPrincipal::lanzarVentanaModelo);
     connect(pbDim, &QAbstractButton::clicked, this, &VentanaPrincipal::seleccionarDimension);

}

void VentanaPrincipal::crearIconos()
{
    iconoDim1D = new QIcon(QPixmap(":/imagenesIconos/Imagenes/icono1D.png"));
    iconoDim2D = new QIcon(QPixmap(":/imagenesIconos/Imagenes/icono2D.png"));
    iconoDim3D = new QIcon(QPixmap(":/imagenesIconos/Imagenes/icono3D.png"));
}

void VentanaPrincipal::crearFrameDimension()
{
    qInfo() << "Se intenta ejectuar el frame";
    frDimension = new QFrame(this);
    frDimension->setStyleSheet("QFrame { background-color : white}");
    frDimension->setGeometry(20,170,300,500);
    //frDim->setMinimumSize(QSize(300,500));
    frDimension->setSizePolicy(QSizePolicy::Preferred, QSizePolicy::Preferred);
    //frDimension->setFrameStyle(QFrame::Panel);
    frDimension->setFrameShape(QFrame::Panel);


    QPushButton* bt1 = new QPushButton(*iconoDim1D, QString(), frDimension);
    bt1->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
    bt1->setIconSize(QSize(frDimension->width()-30,frDimension->height()/3));
    bt1->setStyleSheet("QPushButton {background-color : transparent}");
    connect(bt1, &QAbstractButton::pressed, [this](){frDimension->hide();});
    QPushButton* bt2 = new QPushButton(*iconoDim2D, QString(), frDimension);
    bt2->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
    bt2->setIconSize(QSize(frDimension->width()-30,frDimension->height()/3));
    bt2->setStyleSheet("QPushButton {background-color : transparent}");
    connect(bt2, &QAbstractButton::pressed, [this](){frDimension->hide();});
    QPushButton* bt3 = new QPushButton(*iconoDim3D, QString(), frDimension);
    bt3->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
    bt3->setIconSize(QSize(frDimension->width()-30,frDimension->height()/3));
    bt3->setStyleSheet("QPushButton {background-color : transparent}");
    connect(bt3, &QAbstractButton::pressed, [this](){frDimension->hide();});

    QVBoxLayout* vbLay = new QVBoxLayout;
    vbLay->addWidget(bt1);
    vbLay->addWidget(bt2);
    vbLay->addWidget(bt3);

    frDimension->setLayout(vbLay);
    frDimension->hide();
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

void VentanaPrincipal::seleccionarDimension()
{
    frDimension->show();
}
